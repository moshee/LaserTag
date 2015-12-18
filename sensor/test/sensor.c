#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#include "light_ws2812.h"

struct cRGB rgb[2] = {
	{
		.r = 0,
		.g = 40,
		.b = 80
	},
	{
		.r = 80,
		.g = 120,
		.b = 80
	}
};

struct dir {
	int8_t r;
	int8_t g;
	int8_t b;
};

struct dir dirs[2] = {
	{
		.r = 1,
		.g = 1,
		.b = 1
	},
	{
		.r = 1,
		.g = -1,
		.b = -1
	}
};

int main(void) {
	DDRB |= _BV(PB1);

	TCCR1A = 0;
	TCCR1B = _BV(WGM12) | _BV(CS11);
	TIMSK1 = _BV(OCIE1A);
	OCR1A = 0x411A;
	sei();
	/*
	   for (;;) {
	   rgb[0].r = 128; rgb[0].g = 0;   rgb[0].b = 0;
	   rgb[1].r = 0;   rgb[1].g = 128; rgb[1].b = 0;
	   ws2812_setleds(rgb, 2);
	   _delay_ms(500);

	   rgb[0].r = 0;   rgb[0].g = 128; rgb[0].b = 0;
	   rgb[1].r = 128; rgb[1].g = 0;   rgb[1].b = 0;
	   ws2812_setleds(rgb, 2);
	   _delay_ms(500);

	   rgb[0].r = 0;   rgb[0].g = 0;   rgb[0].b = 128;
	   rgb[1].r = 128; rgb[1].g = 128; rgb[1].b = 0;
	   ws2812_setleds(rgb, 2);
	   _delay_ms(500);
	   }
	   */

	for (;;) {

	}

	return 0;
}

ISR(TIMER1_COMPA_vect) {
	uint8_t i = 0;

	for (i = 0; i < 2; i++) {
		if (rgb[i].r == 0) {
			dirs[i].r = 1;
		} else if (rgb[i].r == 120) {
			dirs[i].r = -1;
		}
		rgb[i].r += dirs[i].r;
		if (rgb[i].g == 0) {
			dirs[i].g = 1;
		} else if (rgb[i].g == 120) {
			dirs[i].g = -1;
		}
		rgb[i].g += dirs[i].g;
		if (rgb[i].b == 0) {
			dirs[i].b = 1;
		} else if (rgb[i].b == 120) {
			dirs[i].b = -1;
		}
		rgb[i].b += dirs[i].b;
	}

	ws2812_setleds(rgb, 2);
}
