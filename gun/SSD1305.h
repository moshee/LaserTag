/*
 * Driver for SSD1305 OLED controller, used in Crystalfontz 128x64 OLED module
 */

#ifndef _SSD1305_H_
#define _SSD1305_H_

#include <Arduino.h>
#include <stdint.h>

#define SET_CONTRAST 0b10000001 // then 8 bits
#define SET_MUX      0b10101000 // then 6 bits
#define SET_ALL_ON   0b10100101
#define SET_ALL_OFF  0b10100100
#define SET_DISP_ON  0b10101111
#define SET_DISP_OFF 0b10101110

typedef struct {
	const uint8_t* base;
	uint8_t width;
	uint8_t offset;
} font_t;

extern font_t font_normal, font_small;

class SSD1305 : public Print {
public:
	void init(void);
	void clear(void);
	void clearArea(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
	void fillArea(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t c);
	void setContrast(uint8_t c);
	void setCursor(uint8_t x, uint8_t y);
	void invert(bool on);
	void draw(const void* bmp, uint8_t len);
	void setFont(font_t* f);

	void on(void);
	void off(void);

	void command(void); // enter command mode
	void data(void); // enter data mode

	virtual size_t write(uint8_t c); // write a character from the font
	void begin(void);
	void end(void);
	inline void send(uint8_t b); // send a byte of data or command

private:
	uint8_t flags = 0;
	uint8_t x;
	uint8_t y;
	uint8_t buf[5];
	font_t* font;
};

#endif /* _SSD1305_H_ */
