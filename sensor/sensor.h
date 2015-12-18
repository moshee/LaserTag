#include <stdint.h>

#include "light_ws2812.h"

#define TIMER_ARM     0
#define TIMER_EXPIRED 1

extern volatile uint8_t TFLAG;

struct timer {
	uint16_t cnt;
	uint8_t  arm;
	uint8_t  mask;
	//void     (*f)(void);
};

// pulse one of the RGB LEDs five times in quick succession
void pulse_led(struct cRGB* leds, uint8_t len, uint8_t i, uint8_t r, uint8_t g, uint8_t b);

void timer_init(volatile struct timer* t, uint8_t len);
void timer_arm(uint8_t i, uint16_t delta);
void timer_disarm(uint8_t i);
