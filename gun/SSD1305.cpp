#include <Arduino.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <SPI.h>

#include "SSD1305.h"
#include "font.h"

font_t font_normal = {
	.base = font,
	.width = 5,
	.offset = 0
};

font_t font_small = {
	.base = font2,
	.width = 4,
	.offset = 32
};

#define FLAG_SLEEP		_BV(0)
#define FLAG_INVERT		_BV(1)
#define PAGES 			8
#define COLUMNS 		128
#define TOTAL_COLUMNS	132
#define RST 			PC2
#define CS  			PC1
#define DC  			PC0
#define DDR             DDRC
#define PORT            PORTC

void SSD1305::init(void) {
	bitSet(DDR, RST);
	bitSet(DDR, CS);
	bitSet(DDR, DC);
	bitSet(PORT, CS);

	// 1. Power on VDD, VDDIO
	// 2. Pulse RESET LOW for at least 3 µs and then HIGH
	bitClear(PORT, RST);
	_delay_us(3);
	bitSet(PORT, RST);

	// 3. turn on VCC at least 3 µs after RESET LOW
	// 4. send command 0xAF for display on. SEG/COM will be on after 100 ms
	this->begin();
	this->on();
	this->end();
	delay(100);

	this->begin();
	this->send(0x20); // horizontal addressing mode
	this->send(0x00);
	this->send(0xC8); // remapped scan mode

	this->clear();
	this->end();
}

void SSD1305::clear(void) {
	uint16_t i;
	this->data();
	for (i = 0; i < PAGES*TOTAL_COLUMNS; i++) {
		this->send(0x00);
	}
}

void SSD1305::clearArea(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2) {
	this->fillArea(x1, y1, x2, y2, 0x00);
}

void SSD1305::fillArea(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t c) {
	uint8_t x, y;

	if (x1 > x2) {
		x = x1;
		x1 = x2;
		x2 = x;
	}

	if (y1 > y2) {
		y = y1;
		y1 = y2;
		y2 = y;
	}

	for (y = y1; y <= y2; y++) {
		this->setCursor(x1, y);
		this->data();
		for (x = x1; x <= x2; x++) {
			this->send(c);
		}
	}
}

void SSD1305::setContrast(uint8_t c) {
	this->command();
	this->send(0x81); // set contrast control register
	this->send(c);
}

size_t SSD1305::write(uint8_t c) {
	if (c == '\n') {
		this->setCursor(0, (this->y + 1) % 8);
		return 1;
	}
	uint8_t i;
	const uint8_t* base = this->font->base + ((c - this->font->offset) * this->font->width);

	this->data();

	if ((this->flags & FLAG_INVERT) != 0) {
		for (i = 0; i < this->font->width; i++) {
			this->send(~pgm_read_byte(base + i));
		}
		this->send(0xFF);
	} else {
		for (i = 0; i < this->font->width; i++) {
			this->send(pgm_read_byte(base + i));
		}
		this->send(0x00);
	}
	return 1;
}

void SSD1305::draw(const void* bmp, uint8_t len) {
	uint8_t i;
	this->data();

	if ((this->flags & FLAG_INVERT) != 0) {
		for (i = 0; i < len; i++) {
			this->send(~pgm_read_byte(bmp + i));
		}
	} else {
		for (i = 0; i < len; i++) {
			this->send(pgm_read_byte(bmp + i));
		}
	}
}

void SSD1305::setFont(font_t* f) {
	this->font = f;
}

void SSD1305::setCursor(uint8_t x, uint8_t y) {
	this->x = x;
	this->y = y;
	this->command();
	this->send(x & 0x0F); // set column address lower nibble
	this->send(0x10 | (x >> 4)); // set column address upper nibble
	this->send(0xB0 | (y & 0x0F)); // set page address
}

void SSD1305::invert(bool on) {
	if (on) {
		this->flags |= FLAG_INVERT;
	} else {
		this->flags &= ~FLAG_INVERT;
	}
}

void SSD1305::begin(void) {
	SPI.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0));
	bitClear(PORT, CS);
	cli();
}

void SSD1305::end(void) {
	sei();
	bitSet(PORT, CS);
	SPI.endTransaction();
}

inline void SSD1305::send(uint8_t b) {
	SPI.transfer(b);
}

void SSD1305::command(void) {
	PORT &= ~_BV(DC);
}

void SSD1305::data(void) {
	PORT |= _BV(DC);
}

void SSD1305::on(void) {
	this->command();
	this->send(0xAF);
}

void SSD1305::off(void) {
	this->command();
	this->send(0xAE);
}
