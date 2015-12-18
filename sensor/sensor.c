#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "sensor.h"

void pulse_led(struct cRGB* leds, uint8_t len, uint8_t i, uint8_t r, uint8_t g, uint8_t b) {
	if (i > len) {
		return;
	}

	uint8_t j;

	for (j = 0; j < len; j++) {
		leds[j].r = 0;
		leds[j].g = 0;
		leds[j].b = 0;
	}

	for (j = 0; j < 5; j++) {
		leds[i].r = r;
		leds[i].g = g;
		leds[i].b = b;
		ws2812_setleds(leds, len);
		_delay_ms(20);

		leds[i].r = 0;
		leds[i].g = 0;
		leds[i].b = 0;
		ws2812_setleds(leds, len);
		_delay_ms(20);
	}
}

uint8_t                _timer_len;
volatile struct timer* _timers;
volatile uint8_t       TFLAG = 0;

void timer_init(volatile struct timer* t, uint8_t len) {
	_timers    = t;
	_timer_len = len;
	// set up TCNT2 to tick every millisecond
	TCCR2A = _BV(WGM21); // CTC
	TCCR2B = _BV(CS22); // /64
	TIMSK2 = _BV(OCIE2A);
	OCR2A  = 0x7C;
}

void timer_arm(uint8_t i, uint16_t delta) {
	cli();
	_timers[i].cnt = delta;
	_timers[i].arm = 1;
	sei();
}

void timer_disarm(uint8_t i) {
	_timers[i].arm = 0;
}

ISR(TIMER2_COMPA_vect) {
	uint8_t i;

	for (i = 0; i < _timer_len; i++) {
		if (_timers[i].arm) {
			if (_timers[i].cnt == 0) {
				PORTD |= _BV(PD7);
				_timers[i].arm = 0;
				//timers[i].f();
				TFLAG |= _timers[i].mask;
				PORTD &= ~_BV(PD7);
			} else {
				_timers[i].cnt--;
			}
		}
	}
}
