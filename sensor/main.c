#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include <stdint.h>

#include "light_ws2812.h"
#include "sensor.h"

// number of installed sensor modules
#define NUM_MODULES 8

/*
 * Pins
 * PB0
 * PB1  --> ONEWIRE_DOUT
 * PB2
 * PB3  --> (MOSI)
 * PB4  <-- (MISO)
 * PB5  --> (SCK)
 * PC0  --> MCOM
 * PC1  --> IRSEL0
 * PC2  --> IRSEL1
 * PC3  --> IRSEL2
 * PC4  <-> (SDA)
 * PC5  --> (SCL)
 * ADC6
 * ADC7
 * PD0  <-- (RX)
 * PD1  --> (TX)
 * PD2  --> MSEL2
 * PD3  --> MSEL1
 * PD4  --> MSEL0
 * PD5
 * PD6  <-- IRCOM
 * PD7
 */

#define DO_ONEWIRE PB1
#define DO_MCOM    PC0
#define DO_IRSEL0  PC1
#define DO_IRSEL1  PC2
#define DO_IRSEL2  PC3
#define IRSEL_MASK (_BV(PC1) | _BV(PC2) | _BV(PC3))
#define DO_MSEL2   PD2
#define DO_MSEL1   PD3
#define DO_MSEL0   PD4
#define MSEL_MASK  (_BV(PD2) | _BV(PD3) | _BV(PD4))
#define DI_IR      PD6

/*
 * Pos	IR #	LED #
 * 0	2		7
 * 1	1		6 (2)
 * 2	0		5
 * 3	3		4
 * 4	5		3 (1)
 * 5	7		2
 * 6	6		1
 * 7	4		0 (0)
 */

// 0 1 3 2 6 7 5 4
// 2 1 3 0 6 4 7 5
// 7 6 4 5 1 0 2 3
//   2       0   1

/* Mux selection mappings to physical connector order */
/*                                    0  1  2  3  4  5  6  7 */
/* const uint8_t ir_map[NUM_MODULES]    = { 2<<1, 1<<1, 0<<1, 3<<1, 5<<1, 7<<1, 6<<1, 4<<1 }; */
/* gray code: 000 001 011 010 110 111 101 100 */
const uint8_t ir_map[NUM_MODULES]    = { 0, 1<<1, 3<<1, 2<<1, 6<<1, 7<<1, 5<<1, 4<<1 };
// 1, 5, 4 << 1
// 0x02, 0x0A, 0x08
/* since the data is shifted through, I think the order is backwards (last LED
 * is first in line)
 */
/* const uint8_t led_map[NUM_MODULES]   = { 2, 0, 1 }; */
/* const uint8_t led_map[NUM_MODULES]   = { 0xFF, 0, 0xFF, 0xFF, 0xFF, 0xFF, 1, 2 }; */
/* const uint8_t led_map[NUM_MODULES]   = { 5, 6, 4, 7, 1, 2, 3, 0 }; */
const uint8_t led_map[NUM_MODULES]   = { 0, 3, 2, 1, 7, 4, 6, 5 };
/* Unfortunately the mux addresses on the motors are wired backwards */
/* uint8_t motor_map[NUM_MODULES] = { 4, 6, 7, 5, 3, 0, 1, 2 }; */
/* const uint8_t motor_map[NUM_MODULES] = { 6, 3, 2 }; */

volatile uint8_t sel          = 0; /* current mux selection */
volatile uint8_t pulses       = 0; /* count pulses in current period */
volatile uint8_t do_pulse     = 0; /* flag, true = blink/vibrate */
volatile uint8_t trigger_sel  = 0; /* which IR channel triggered the blink */
volatile uint8_t data_byte    = 0; /* register to hold received bits */
volatile uint8_t symbol_count = 0; /* counting how many symbols are received */
volatile struct cRGB cc;

volatile uint8_t do_test = 0;

#define STATE_WAIT         0
#define STATE_WAIT_START   1
#define STATE_START_MARK   2
#define STATE_START_SPACE  3
#define STATE_VALID_PACKET 4
#define STATE_MID_SYMBOL   5
#define STATE_NEXT_SYMBOL  6
#define STATE_END          7

volatile uint8_t state = STATE_WAIT;

inline void set_state(uint8_t st) {
	//D5 D7 B0
	//PORTD = (PORTD & 0x5F) | ((st & 0x01) << 7) | ((st & 0x02) << 4);
	//PORTB = (PORTB & 0xFE) | ((st & 0x04) >> 2);
	state = st;
}

void reset_state(void);

#define TRECVTIMEOUT 0

volatile struct timer timers[] = {
	{ 0, 0, _BV(TRECVTIMEOUT) }
};

int main(void) {
	uint8_t i, j;
	struct cRGB leds[NUM_MODULES] = {{ 0 }};
	/* struct cRGB my_color = { */
	/* 	.r = 0x68, */
	/* 	.g = 0x28, */
	/* 	.b = 0x00 */
	/* }; */

	wdt_reset();

	cli();

	PRR   =  _BV(PRADC);
	DDRB  =  _BV(DO_ONEWIRE) | _BV(PB0);
	DDRC  =  _BV(DO_MCOM) | IRSEL_MASK;
	DDRD  =  MSEL_MASK | _BV(PD5) | _BV(PD7);
	PORTB =  _BV(PB2);

	PORTB = 0;
	PORTC = 0;
	PORTD = _BV(PD5);

	// CTC, /256 divider for 640 µs tick
	// The transmission starts with 24 alternating edges about 630 µs apart.
	// Since the pulse period is closely matched to the tick period, we are
	// basically guaranteed at least one edge to lock onto in every tick
	// period, most likely two.
	// Since we are sending more edges than we need (12 pulses but only 8
	// sensor modules total) we are also guaranteed that we can lock onto the
	// signal within one full cycle when not already busy for more than half of
	// a message time.
	// After that the state machine can suck in the data, ignoring any leading pulses.
	TCCR0A = _BV(WGM01);
	TCCR0B = _BV(CS02);
	TIMSK0 = _BV(OCIE0A);
	OCR0A  = 0x13;

	// same 38 KHz timer as transmitter for timing pulses
	TCCR1A = _BV(WGM11);
	TCCR1B = _BV(WGM13) | _BV(CS10);
	TIMSK1 = _BV(TOIE1);
	ICR1   = 0x0068;
	OCR1A  = 0x0046;

	// pin change interrupt on PCINT22 (PD6) to detect incoming IR data edges
	PCICR  = _BV(PCIE2);
	PCMSK2 = _BV(PCINT22);

	timer_init(timers, 1);

	PORTD &= ~_BV(PD5);
	sei();

	for (i = 0; i < NUM_MODULES; i++) {
		for (j = 0; j < NUM_MODULES; j++) {
			if (j <= i) {
				leds[j].r = 0xFF;
			} else {
				leds[j].r = 0x00;
			}
		}
		ws2812_setleds(leds, NUM_MODULES);
		_delay_ms(50);
	}

	_delay_ms(300);

	for (i = 0xFF; i > 0; i--) {
		for (j = 0; j < NUM_MODULES; j++) {
			leds[j].r = i - 1;
		}
		ws2812_setleds(leds, NUM_MODULES);
		_delay_ms(1);
	}

	//timer_arm(&timers[1], 1000);

	for (;;) {
		if (bit_is_set(TFLAG, TRECVTIMEOUT)) {
			cli();
			TFLAG &= ~_BV(TRECVTIMEOUT);
			//aaaaaa = 0;
			PRR &= ~_BV(PRTIM0);
			set_state(STATE_WAIT);
			sei();
		}
		if (do_pulse) {
			//uint8_t sreg = SREG;
			//cli();
			do_pulse = 0;
			//msel   = motor_map[trigger_sel];
			//SREG = sreg;
			if (data_byte == 0x1B) {
				pulse_led(leds, NUM_MODULES, led_map[trigger_sel], 20, 255, 160);
			}/* else {
				pulse_led(leds, NUM_MODULES, ledsel, (struct cRGB*)&cc);
			}*/

			// select corresponding motor
			//PORTD = (PORTD & ~MSEL_MASK) | ((msel << 2) & MSEL_MASK);

			//PORTC |= _BV(DO_MCOM);
			//_delay_ms(800);
			//PORTC &= ~_BV(DO_MCOM);
		}
		/*
		if (do_test) {
			do_test = 0;
			for (i = 0; i < 3; i++) {
				leds[i].r = 0;
				leds[i].g = 0;
				leds[i].b = 0xFF;
			}
			ws2812_setleds(leds, 3);
			_delay_ms(20);
			for (i = 0; i < 3; i++) {
				leds[i].r = 0;
				leds[i].g = 0;
				leds[i].b = 0;
			}
			ws2812_setleds(leds, 3);
			timer_arm(&timers[1], 1000);
		}
		*/
	}

	return 0;
}

void reset_state(void) {
	timer_disarm(0);
	PRR &= ~_BV(PRTIM0);
	set_state(STATE_WAIT);
}

// cycle IR input mux selection
ISR(TIMER0_COMPA_vect) {
	uint8_t irsel, portc;
	// stop scanning when we're receiving something
	if (state == STATE_WAIT) {
		sel++;
		if (sel >= NUM_MODULES) {
			sel = 0;
		}

		irsel = ir_map[sel];
		/* irsel = sel << 1; */
		portc = PORTC & ~IRSEL_MASK;
		portc |= irsel;
		PORTC = portc;
	}
}

ISR(TIMER1_OVF_vect) {
	if (state != STATE_WAIT) {
		pulses++;
	}
}

#define ACCEPT(have, want) ((have) > ((want)-6) && (have) < ((want)+6))
#define MARK bit_is_clear(PIND, DI_IR)
#define SPACE bit_is_set(PIND, DI_IR)

/*
 * IR receive state machine
 * The structure is as follows:
 * - Packet begin: 30-pulse mark + 20-pulse space
 * - Data byte: four 12-pulse mark/variable-pulse space symbols giving 2 bits
 *   each symbol
 * - Packet end: 12-pulse mark (this is kind of arbitrary though, just need any mark)
 * Give ±2 pulse tolerance for robustness
 *      1            0            1      0      1       0      1       0     1
 * ___________|||||||||||||||__________||||||___...___||||||___...___||||||_______...
 *            ^             ^          ^    ^         ^    ^         ^    ^
 *     STATE_START_MARK     |          |    |         |    |  STATE_END  STATE_WAIT
 *                STATE_START_SPACE    |    |         |   STATE_MID_SYMBOL
 *                      STATE_VALID_PACKET  |  STATE_NEXT_SYMBOL
 *                                  STATE_MID_SYMBOL  
 */
ISR(PCINT2_vect) {
	PRR |= _BV(PRTIM0);

	switch (state) {
	case STATE_WAIT:
		if (MARK) {
			set_state(STATE_START_MARK);
		} else {
			set_state(STATE_WAIT_START);
		}
		break;

	case STATE_WAIT_START:
		if (MARK) {
			set_state(STATE_START_MARK);
		} else {
			// if we just saw a 12-pulse mark, it was probably in the sync
			// pulse train. Keep looking for a mark.
			if (!ACCEPT(pulses, 12)) {
				reset_state();
			}
		}
		break;

	case STATE_START_MARK:
		if (SPACE) {
			if (ACCEPT(pulses, 30)) {
				set_state(STATE_START_SPACE);
			} else {
				// we just had a 12-pulse mark
				// loop back until we get a valid start condition
				set_state(STATE_WAIT_START);
			}
		} else {
			reset_state();
		}
		break;

	case STATE_START_SPACE:
		if (MARK && ACCEPT(pulses, 20)) {
			set_state(STATE_VALID_PACKET);
		} else {
			reset_state();
		}
		break;

	case STATE_VALID_PACKET:
		data_byte = 0;
		symbol_count = 0;

	case STATE_NEXT_SYMBOL:
		if (SPACE) {
			if (ACCEPT(pulses, 12)) {
				set_state(STATE_MID_SYMBOL);
			} else {
				reset_state();
			}
		} else {
			reset_state();
		}
		break;

	case STATE_MID_SYMBOL:
		if (MARK) {
			if (ACCEPT(pulses, 20)) {
				data_byte <<= 2;
			} else if (ACCEPT(pulses, 32)) {
				data_byte = (data_byte<<2) | 0x01;
			} else if (ACCEPT(pulses, 44)) {
				data_byte = (data_byte<<2) | 0x02;
			} else if (ACCEPT(pulses, 56)) {
				data_byte = (data_byte<<2) | 0x03;
			} else {
				reset_state();
				break;
			}
			symbol_count++;

			if (symbol_count >= 4) {
				set_state(STATE_END);
			} else {
				set_state(STATE_NEXT_SYMBOL);
			}
			break;
		} else {
			reset_state();
		}
		break;

	case STATE_END:
		if (SPACE) {
			trigger_sel = sel;
			do_pulse    = 1;
			//reset_state();
			set_state(STATE_WAIT_START);
		}
		// maybe at the end, if we don't see any more marks within 12 pulse
		// times then we consider the transmission over. Then we can continue
		// with the previous behavior of sending the same message multiple
		// times. Each subsequent decode would overwrite the previous.
		break;

	default:
		reset_state();
		break;
	}

	// the longest possible state is 56 pulses or ~1.4 ms, so time out if we
	// see nothing else in 10 or so
	timer_arm(0, 3);
	pulses = 0;
}
