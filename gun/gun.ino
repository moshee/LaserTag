#include <SPI.h>
#include <Wire.h>
#include <avr/eeprom.h>

#include "font.h"
#include "SSD1305.h"
#include "STC3100.h"

/*
   PB0      VIBE
   PB1/OC1A IR
   PB2
   PB3      (MOSI)
   PB4      (MISO)
   PB5      (SCK)
   PC0      D/~C
   PC1      ~CS
   PC2      ~RES
   PC3
   PC4      (SDA)
   PC5      (SCL)
   ADC6
   ADC7
   PD0      (RX)
   PD1      (TX)
   PD2/INT0 ~TRIG
   PD3
   PD4
   PD5
   PD6
   PD7
   */

#define PIN_VIBE PB0
#define PIN_IR   PB1
#define PIN_TRIG PD2

SSD1305 oled = SSD1305();
STC3100 battery = STC3100();

volatile uint8_t flags = 0;
#define FLAG_AMMO    0
#define FLAG_BATTERY 1
#define FLAG_TRIGGER 2
#define FLAG_TX      3

struct state {
	uint8_t ammo;
	uint8_t battery;
};

struct player {
	uint8_t id;
};

struct state g_state = {
	.ammo = 24,
	.battery = 50
};

struct player g_player;

static const uint8_t bmp_ammo_left[]   PROGMEM = { 0x7E, 0x81 };
static const uint8_t bmp_ammo_right[]  PROGMEM = { 0x81, 0x7E };
static const uint8_t bmp_ammo_glyph[]  PROGMEM = { 0xBE, 0xFF, 0xBE, 0x00 };
static const uint8_t bmp_batt_cap[]    PROGMEM = { 0x18, 0x3C };
static const uint8_t bmp_batt_full[]   PROGMEM = { 0x3C };
static const uint8_t bmp_batt_empty[]  PROGMEM = { 0x24 };
static const uint8_t bmp_batt_charge[] PROGMEM = { 0x08, 0x19, 0x3E, 0x7C, 0x98, 0x10 };

#define CONNECT_OC1A    TCCR1A |= (_BV(COM1A0) | _BV(COM1A1))
#define DISCONNECT_OC1A TCCR1A &= ~(_BV(COM1A0) | _BV(COM1A1))

void setup(void) {
	DDRB |= _BV(PIN_VIBE) | _BV(PIN_IR);
	PORTB &= ~(_BV(PIN_VIBE) | _BV(PIN_IR));
	bitClear(MCUCR, PUD);
	PORTB |= _BV(PB2);
	PORTC |= _BV(PC3);
	PORTD |= _BV(PD2) | _BV(PD3) | _BV(PD4) | _BV(PD5) | _BV(PD6) | _BV(PD7);

	// trigger switch falling edge interrupt
	EICRA = _BV(ISC01);
	EIMSK = _BV(INT0);

	// set up timer1 to produce 38KHz wave
	// phase-correct PWM, /1 prescaler
	TCCR1A = _BV(WGM11);
	TCCR1B = _BV(WGM13) | _BV(CS10);
	ICR1   = 0x0068;
	OCR1A  = 0x0046;

	// set up timer2 for general purpose ticking
	// ...

	eeprom_read_block(&g_player, (void*)0, sizeof g_player);
	if (g_player.id == 0xFF) {
		g_player.id = 0x00;
	}

	Serial.begin(57600);
	SPI.begin();
	Wire.begin();

	battery.init(650*3.7, 50);

	oled.init();
	oled.setFont(&font_small);

	oled.begin();
	oled.setCursor(12, 1);
	oled.draw(bmp_ammo_left, sizeof bmp_ammo_left);
	oled.setCursor(113, 1);
	oled.draw(bmp_ammo_right, sizeof bmp_ammo_right);
	oled.end();

	update_ammo(&g_state, oled);
	update_battery(&g_state, oled);
	update_id(&g_player, oled);
}

void loop(void) {
	uint8_t i;
	char    c, buf[64];

	if (Serial.available() > 0) {
		c = Serial.read();
		switch (c) {
		case 'I': 
			i = (uint8_t)Serial.parseInt();
			g_player.id = i;
			eeprom_update_block(&g_player, (void*)0, sizeof g_player);
			
			Serial.print(F("ID set to "));
			Serial.println(g_player.id);
			break;
		default:
			Serial.print(F("error: unknown command: "));
			Serial.println(c);
			break;
		}
		Serial.readBytesUntil('\n', buf, sizeof buf);
		Serial.flush();
	}

	if (bitRead(flags, FLAG_TRIGGER)) {
		bitClear(flags, FLAG_TRIGGER);
		// send IR bytes
		// use the sync word 0x40. This is chosen to give a lot of marks (zero in
		// this case; the receiver puts out a LOW signal when a valid pulse train
		// is detected) to grab onto during the multiplexer scan on the receiver
		// side, while still acting as a sync word.
		// Data words must be masked in 0x1F.
		// When receiving, shift in bits until the current byte equals 0xBF to
		// capture the sync word, then read in 8 more bits for the data word.

		// DEBUG
		if (g_state.ammo == 0) {
			g_state.ammo = 24;
		}

		if (g_state.ammo > 0) {
			bitSet(flags, FLAG_TX);
			bitSet(PORTB, PIN_VIBE);
			g_state.ammo--;
			update_ammo(&g_state, oled);
			send_byte(g_player.id);
			send_byte(g_player.id);
			send_byte(g_player.id);
			bitClear(PORTB, PIN_VIBE);
			bitClear(flags, FLAG_TX);
		}
	}

	if (bitRead(flags, FLAG_BATTERY)) {
		bitClear(flags, FLAG_BATTERY);
		update_battery(&g_state, oled);
	}
}

void send_byte(uint8_t x) {
	// Rough emulation of Philips RC-MM protocol here. Not following the spec
	// exactly but same general idea with the header and symbols

	// use TIMSK1[OCIE1A] to enable interrupts during a mark to count out pulses
	// use TCCR1A[COM1A0] to connect (mark) and disconnect (space) OC1A
	uint8_t i;

	mark(30);
	space(20);

	for (i = 0; i < 4; i++, x >>= 2) {
		mark(12);
		switch (x & 0x03) {
		case 0x00:
			space(20);
			break;
		case 0x01:
			space(32);
			break;
		case 0x02:
			space(44);
			break;
		case 0x03:
			space(56);
			break;
		}
	}

	mark(12);
	DISCONNECT_OC1A;
	delay(1);
}

void mark(uint8_t n) {
	CONNECT_OC1A;
	wait_pulse(n);
}

void space(uint8_t n) {
	DISCONNECT_OC1A;
	wait_pulse(n);
}

void wait_pulse(uint8_t n) {
	uint8_t i;

	for (i = 0; i < n; i++) {
		// YES, IT'S AWFUL, but writing the asynchronous code seems more
		// awful given that we don't have DMA or anything on the AVR.
		while (!bitRead(TIFR1, TOV1)) {
			asm volatile("nop");
		}
		bitSet(TIFR1, TOV1);
	}
}

void update_ammo(struct state* state, SSD1305& oled) {
	uint8_t i;

	oled.begin();
	oled.clearArea(16, 1, 112, 1);

	if (state->ammo == 0) {
		oled.setCursor((128-42)/2, 1);
		oled.print("NO AMMO");
	} else {
		oled.setCursor(16, 1);
		for (i = 0; i < state->ammo; i++) {
			oled.draw(bmp_ammo_glyph, sizeof bmp_ammo_glyph);
		}
	}
	oled.end();
}

void update_battery(struct state* state, SSD1305& oled) {
	//state->battery = battery.get_soc();
	uint8_t level = 8 - (state->battery >> 5);
	uint8_t i;

	oled.begin();
	oled.setCursor(128 - 12, 0);
	oled.draw(bmp_batt_cap, sizeof bmp_batt_cap);
	
	for (i = 0; i < 8; i++) {
		if (i < level) {
			oled.draw(bmp_batt_empty, 1);
		} else {
			oled.draw(bmp_batt_full, 1);
		}
	}
	oled.draw(bmp_batt_full, 1);
	oled.end();
}

void update_id(struct player* player, SSD1305& oled) {
	oled.begin();
	oled.clearArea(0, 5, 128, 5);
	oled.setCursor(0, 5);
	oled.print(F("My ID: "));
	oled.print(player->id);
	oled.end();
}

// gun fired
ISR(INT0_vect) {
	if (!bitRead(flags, FLAG_TX)) {
		bitSet(flags, FLAG_TRIGGER);
	}
}
