#ifndef _FONT_H_
#define _FONT_H_

#include <stdint.h>
#include <avr/pgmspace.h>

static const uint8_t font[] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3E, 0x1C, 0x08, 
	0x7F, 0x61, 0x61, 0x62, 0x7C, 0x08, 0x6C, 0x3E, 0x1B, 0x08, 
	0x7E, 0x43, 0x42, 0x43, 0x7E, 0x7E, 0x63, 0x62, 0x63, 0x7E, 
	0x7E, 0x73, 0x72, 0x73, 0x7E, 0x7E, 0x7B, 0x7A, 0x7B, 0x7E, 
	0x7E, 0x7F, 0x7E, 0x7F, 0x7E, 0xFC, 0x20, 0x20, 0x1C, 0x20, 
	0x07, 0x04, 0xF4, 0x50, 0x10, 0x63, 0x77, 0x5D, 0x49, 0x63, 
	0x26, 0x29, 0x79, 0x29, 0x26, 0x40, 0x7F, 0x05, 0x05, 0x07, 
	0x40, 0x7F, 0x05, 0x25, 0x3F, 0x5A, 0x3C, 0xE7, 0x3C, 0x5A, 
	0x7F, 0x3E, 0x1C, 0x1C, 0x08, 0x08, 0x1C, 0x1C, 0x3E, 0x7F, 
	0x14, 0x22, 0x7F, 0x22, 0x14, 0x5F, 0x5F, 0x00, 0x5F, 0x5F, 
	0x06, 0x09, 0x7F, 0x01, 0x7F, 0x00, 0x66, 0x89, 0x95, 0x6A, 
	0x60, 0x60, 0x60, 0x60, 0x60, 0x94, 0xA2, 0xFF, 0xA2, 0x94, 
	0x08, 0x04, 0x7E, 0x04, 0x08, 0x10, 0x20, 0x7E, 0x20, 0x10, 
	0x08, 0x08, 0x2A, 0x1C, 0x08, 0x08, 0x1C, 0x2A, 0x08, 0x08, 
	0x1E, 0x10, 0x10, 0x10, 0x10, 0x0C, 0x1E, 0x0C, 0x1E, 0x0C, 
	0x30, 0x38, 0x3E, 0x38, 0x30, 0x06, 0x0E, 0x3E, 0x0E, 0x06, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5F, 0x00, 0x00, 
	0x00, 0x07, 0x00, 0x07, 0x00, 0x14, 0x7F, 0x14, 0x7F, 0x14, 
	0x24, 0x2A, 0x7F, 0x2A, 0x12, 0x23, 0x13, 0x08, 0x64, 0x62, 
	0x36, 0x49, 0x56, 0x20, 0x50, 0x00, 0x08, 0x07, 0x03, 0x00, 
	0x00, 0x1C, 0x22, 0x41, 0x00, 0x00, 0x41, 0x22, 0x1C, 0x00, 
	0x2A, 0x1C, 0x7F, 0x1C, 0x2A, 0x08, 0x08, 0x3E, 0x08, 0x08, 
	0x00, 0x80, 0x70, 0x30, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 
	0x00, 0x00, 0x60, 0x60, 0x00, 0x20, 0x10, 0x08, 0x04, 0x02, 
	0x3E, 0x51, 0x49, 0x45, 0x3E, 0x00, 0x02, 0x7F, 0x00, 0x00, 
	0x42, 0x61, 0x51, 0x49, 0x46, 0x22, 0x41, 0x49, 0x49, 0x36, 
	0x0F, 0x08, 0x08, 0x7F, 0x08, 0x27, 0x45, 0x45, 0x45, 0x39, 
	0x3E, 0x49, 0x49, 0x49, 0x32, 0x01, 0x41, 0x31, 0x0D, 0x03, 
	0x36, 0x49, 0x49, 0x49, 0x36, 0x26, 0x49, 0x49, 0x49, 0x3E, 
	0x00, 0x00, 0x36, 0x36, 0x00, 0x00, 0x80, 0x76, 0x36, 0x00, 
	0x00, 0x08, 0x14, 0x22, 0x41, 0x14, 0x14, 0x14, 0x14, 0x14, 
	0x00, 0x41, 0x22, 0x14, 0x08, 0x02, 0x01, 0x51, 0x09, 0x06, 
	0x3E, 0x41, 0x5D, 0x59, 0x4E, 0x7C, 0x12, 0x11, 0x12, 0x7C, 
	0x7F, 0x49, 0x49, 0x49, 0x36, 0x3E, 0x41, 0x41, 0x41, 0x22, 
	0x7F, 0x41, 0x41, 0x41, 0x3E, 0x7F, 0x49, 0x49, 0x49, 0x41, 
	0x7F, 0x09, 0x09, 0x09, 0x01, 0x3E, 0x41, 0x41, 0x51, 0x72, 
	0x7F, 0x08, 0x08, 0x08, 0x7F, 0x00, 0x41, 0x7F, 0x41, 0x00, 
	0x20, 0x40, 0x41, 0x3F, 0x01, 0x7F, 0x08, 0x14, 0x22, 0x41, 
	0x7F, 0x40, 0x40, 0x40, 0x40, 0x7F, 0x02, 0x1C, 0x02, 0x7F, 
	0x7F, 0x04, 0x08, 0x10, 0x7F, 0x3E, 0x41, 0x41, 0x41, 0x3E, 
	0x7F, 0x09, 0x09, 0x09, 0x06, 0x3E, 0x41, 0x51, 0x21, 0x5E, 
	0x7F, 0x09, 0x19, 0x29, 0x46, 0x26, 0x49, 0x49, 0x49, 0x32, 
	0x01, 0x01, 0x7F, 0x01, 0x01, 0x3F, 0x40, 0x40, 0x40, 0x3F, 
	0x0F, 0x30, 0x40, 0x30, 0x0F, 0x3F, 0x40, 0x38, 0x40, 0x3F, 
	0x63, 0x14, 0x08, 0x14, 0x63, 0x03, 0x0C, 0x70, 0x0C, 0x03, 
	0x61, 0x51, 0x49, 0x45, 0x43, 0x00, 0x7F, 0x41, 0x41, 0x00, 
	0x02, 0x04, 0x08, 0x10, 0x20, 0x00, 0x00, 0x41, 0x41, 0x7F, 
	0x04, 0x02, 0x01, 0x02, 0x04, 0x40, 0x40, 0x40, 0x40, 0x40, 
	0x00, 0x08, 0x07, 0x03, 0x00, 0x20, 0x54, 0x54, 0x78, 0x40, 
	0x7F, 0x28, 0x44, 0x44, 0x38, 0x38, 0x44, 0x44, 0x44, 0x28, 
	0x38, 0x44, 0x44, 0x28, 0x7F, 0x38, 0x54, 0x54, 0x54, 0x18, 
	0x00, 0x08, 0x7E, 0x09, 0x0A, 0x18, 0xA4, 0xA4, 0xA4, 0x78, 
	0x7F, 0x08, 0x04, 0x04, 0x78, 0x00, 0x44, 0x7D, 0x40, 0x00, 
	0x20, 0x40, 0x40, 0x3D, 0x00, 0x7F, 0x10, 0x28, 0x44, 0x00, 
	0x00, 0x41, 0x7F, 0x40, 0x00, 0x7C, 0x04, 0x78, 0x04, 0x78, 
	0x7C, 0x08, 0x04, 0x04, 0x78, 0x38, 0x44, 0x44, 0x44, 0x38, 
	0xFC, 0x18, 0x24, 0x24, 0x18, 0x18, 0x24, 0x24, 0x18, 0xFC, 
	0x7C, 0x08, 0x04, 0x04, 0x08, 0x48, 0x54, 0x54, 0x54, 0x24, 
	0x04, 0x3F, 0x44, 0x24, 0x00, 0x3C, 0x40, 0x40, 0x20, 0x7C, 
	0x0C, 0x30, 0x40, 0x30, 0x0C, 0x3C, 0x40, 0x30, 0x40, 0x3C, 
	0x44, 0x28, 0x10, 0x28, 0x44, 0x4C, 0x90, 0x90, 0x90, 0x7C, 
	0x44, 0x64, 0x54, 0x4C, 0x44, 0x00, 0x08, 0x36, 0x41, 0x00, 
	0x00, 0x00, 0x77, 0x00, 0x00, 0x00, 0x41, 0x36, 0x08, 0x00, 
	0x02, 0x01, 0x02, 0x04, 0x02, 0x3C, 0x26, 0x23, 0x26, 0x3C, 
	0x1E, 0xA1, 0xA1, 0x61, 0x12, 0x70, 0x50, 0x70, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x1F, 0x01, 0x40, 0x40, 0x7C, 0x00, 0x00, 
	0x00, 0x20, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 
	0x88, 0x68, 0x08, 0x18, 0x00, 0x20, 0xE0, 0x10, 0x08, 0x00, 
	0x30, 0x90, 0x98, 0x90, 0x70, 0x90, 0x90, 0xF0, 0x90, 0x90, 
	0x90, 0x50, 0x30, 0xF8, 0x10, 0x10, 0xF8, 0x10, 0x30, 0x00, 
	0x90, 0x90, 0xF0, 0x80, 0x00, 0xA8, 0xA8, 0xA8, 0xF8, 0x00, 
	0x18, 0x80, 0x98, 0x40, 0x30, 0x08, 0x08, 0x08, 0x08, 0x08, 
	0x41, 0x21, 0x1D, 0x01, 0x03, 0x04, 0x04, 0x7C, 0x02, 0x01, 
	0x06, 0x42, 0x43, 0x22, 0x1E, 0x42, 0x42, 0x7E, 0x42, 0x42, 
	0x44, 0x34, 0x0C, 0x7F, 0x04, 0x44, 0x3F, 0x04, 0x44, 0x7C, 
	0x14, 0x14, 0x7F, 0x14, 0x14, 0x04, 0x43, 0x42, 0x22, 0x1E, 
	0x04, 0x43, 0x22, 0x1E, 0x02, 0x44, 0x44, 0x44, 0x44, 0x7C, 
	0x04, 0x0E, 0x44, 0x3E, 0x04, 0x0A, 0x4A, 0x40, 0x20, 0x1C, 
	0x42, 0x22, 0x12, 0x2A, 0x46, 0x04, 0x3E, 0x44, 0x44, 0x4C, 
	0x00, 0x46, 0x40, 0x20, 0x1C, 0x44, 0x47, 0x2A, 0x12, 0x0E, 
	0x0A, 0x4A, 0x3E, 0x09, 0x09, 0x06, 0x40, 0x46, 0x20, 0x1C, 
	0x04, 0x45, 0x3D, 0x05, 0x04, 0x00, 0x00, 0x7F, 0x04, 0x08, 
	0x04, 0x44, 0x3F, 0x04, 0x04, 0x20, 0x24, 0x24, 0x24, 0x20, 
	0x40, 0x52, 0x22, 0x52, 0x0E, 0x22, 0x12, 0x7B, 0x16, 0x22, 
	0x40, 0x40, 0x20, 0x10, 0x0E, 0x40, 0x3C, 0x00, 0x3C, 0x40, 
	0x3E, 0x48, 0x48, 0x44, 0x00, 0x02, 0x42, 0x42, 0x22, 0x1E, 
	0x08, 0x04, 0x08, 0x10, 0x20, 0x34, 0x04, 0x7E, 0x04, 0x34, 
	0x04, 0x14, 0x24, 0x54, 0x0C, 0x00, 0x54, 0x54, 0x54, 0x2A, 
	0x30, 0x28, 0x24, 0x32, 0x60, 0x40, 0x28, 0x10, 0x28, 0x06, 
	0x0A, 0x3E, 0x4A, 0x4A, 0x4A, 0x04, 0x7F, 0x04, 0x14, 0x0C, 
	0x44, 0x44, 0x44, 0x7C, 0x40, 0x54, 0x54, 0x54, 0x54, 0x7C, 
	0x04, 0x45, 0x45, 0x25, 0x1C, 0x0F, 0x40, 0x40, 0x20, 0x1F, 
	0x7C, 0x00, 0x7E, 0x40, 0x20, 0x7F, 0x40, 0x20, 0x20, 0x10, 
	0x7C, 0x44, 0x44, 0x44, 0x7C, 0x06, 0x42, 0x42, 0x22, 0x1E, 
	0x0A, 0x4A, 0x4A, 0x2A, 0x1E, 0x04, 0x44, 0x40, 0x20, 0x1C, 
	0x02, 0x04, 0x01, 0x02, 0x00, 0x07, 0x05, 0x07, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x14, 0x14, 0xF4, 0x04, 0xF4, 0x00, 0x00, 0xFF, 0x00, 0xF7, 
	0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0xF7, 0x00, 0xF7, 
	0x14, 0x14, 0x14, 0x17, 0x14, 0x10, 0x10, 0x1F, 0x10, 0x1F, 
	0x14, 0x14, 0x14, 0xF4, 0x14, 0x10, 0x10, 0xF0, 0x10, 0xF0, 
	0x00, 0x00, 0x1F, 0x10, 0x1F, 0x00, 0x00, 0x00, 0x1F, 0x14, 
	0x00, 0x00, 0x00, 0xFC, 0x14, 0x00, 0x00, 0xF0, 0x10, 0xF0, 
	0x10, 0x10, 0xFF, 0x10, 0xFF, 0x14, 0x14, 0x14, 0xFF, 0x14, 
	0x10, 0x10, 0x10, 0x1F, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x10, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 
	0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 
	0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x38, 0x44, 0x44, 0x38, 0x44, 
	0x00, 0xF0, 0x0C, 0x06, 0xFC, 0x00, 0x00, 0x0C, 0xFE, 0x00, 
	0x00, 0x0C, 0x06, 0x86, 0x7C, 0x00, 0x0C, 0xC6, 0xC6, 0x3C, 
	0x00, 0xFE, 0x80, 0xFC, 0x80, 0x00, 0xFE, 0xC6, 0xC6, 0x86, 
	0x00, 0xE0, 0x18, 0x84, 0x02, 0x00, 0x0E, 0x06, 0xC6, 0x3E, 
	0x00, 0x3C, 0xC6, 0xC6, 0x3C, 0x00, 0xFC, 0x86, 0xC6, 0xFC, 
	0x30, 0x49, 0x4B, 0x4D, 0x39, 0x30, 0x48, 0x78, 0x48, 0x30, 
	0xBC, 0x62, 0x5A, 0x46, 0x3D, 0x38, 0x54, 0x54, 0x54, 0x44, 
	0x01, 0x7F, 0x01, 0x7F, 0x01, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 
	0x00, 0x3F, 0x60, 0x30, 0x0F, 0x00, 0x00, 0x00, 0x7F, 0x00, 
	0x00, 0x78, 0x66, 0x61, 0x70, 0x00, 0x38, 0x44, 0x60, 0x3F, 
	0x00, 0x01, 0x01, 0x7F, 0x01, 0x00, 0x39, 0x64, 0x60, 0x3F, 
	0x00, 0x3F, 0x63, 0x61, 0x3F, 0x00, 0x00, 0x7E, 0x01, 0x00, 
	0x00, 0x3F, 0x60, 0x60, 0x3F, 0x00, 0x40, 0x21, 0x18, 0x07, 
	0x20, 0x40, 0xFF, 0x01, 0x01, 0x00, 0x1F, 0x01, 0x01, 0x1E, 
	0x00, 0x19, 0x1D, 0x17, 0x12, 0x00, 0x3C, 0x3C, 0x3C, 0x3C, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
};

static const uint8_t bmp_ON[] PROGMEM = {
	0xFF, 0xFF, 0xFF, 0xC3, 0xDB, 0xC3, 0xFF, 0xFF, 0xC3, 0xF7,
	0xEF, 0xC3, 0xFF, 0xFF, 0xFF
};

static const uint8_t bmp_OFF[] PROGMEM = {
	0xFF, 0x81, 0xBD, 0xA5, 0xBD, 0x81, 0xBD, 0x95, 0x85, 0x81,
	0xBD, 0x95, 0x85, 0x81, 0xFF
};

static const uint8_t bmp_SINE[] PROGMEM = {
	0x00, 0x18, 0x04, 0x02, 0x02, 0x02, 0x04, 0x18, 0x20, 0x40,
	0x40, 0x40, 0x20, 0x18, 0x0
};

static const uint8_t bmp_TRI[] PROGMEM = {
	0x00, 0x20, 0x10, 0x08, 0x04, 0x02, 0x04, 0x08, 0x10, 0x20,
	0x40, 0x20, 0x10, 0x08, 0x4
};

static const uint8_t bmp_SQUARE[] PROGMEM = {
	0x00, 0x0E, 0x02, 0x02, 0x02, 0x02, 0x02, 0x7E, 0x40, 0x40,
	0x40, 0x40, 0x40, 0x70, 0x0
};

static const uint8_t bmp_BAT[8][12] PROGMEM = {
	{ 0x18, 0x7E, 0x42, 0x42, 0x42, 0x00, 0xBF, 0x42, 0x42, 0x42, 0x42, 0x7E },
	{ 0x18, 0x7E, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x5A, 0x42, 0x7E },
	{ 0x18, 0x7E, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x5A, 0x5A, 0x42, 0x7E },
	{ 0x18, 0x7E, 0x42, 0x42, 0x42, 0x42, 0x42, 0x5A, 0x5A, 0x5A, 0x42, 0x7E },
	{ 0x18, 0x7E, 0x42, 0x42, 0x42, 0x42, 0x5A, 0x5A, 0x5A, 0x5A, 0x42, 0x7E },
	{ 0x18, 0x7E, 0x42, 0x42, 0x42, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A, 0x42, 0x7E },
	{ 0x18, 0x7E, 0x42, 0x42, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A, 0x42, 0x7E },
	{ 0x18, 0x7E, 0x42, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A, 0x42, 0x7E }
};

static const uint8_t font2[] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5E, 0x00, 
	0x7E, 0x42, 0x42, 0x7E, 0x7E, 0x42, 0x42, 0x7E, 
	0x7E, 0x42, 0x42, 0x7E, 0x26, 0x16, 0x68, 0x64, 
	0x7E, 0x42, 0x42, 0x7E, 0x00, 0x08, 0x06, 0x00, 
	0x00, 0x3C, 0x42, 0x00, 0x00, 0x42, 0x3C, 0x00, 
	0x7E, 0x42, 0x42, 0x7E, 0x08, 0x1C, 0x08, 0x00, 
	0x40, 0x30, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 
	0x00, 0x20, 0x00, 0x00, 0x40, 0x30, 0x0C, 0x02, 
	0x30, 0x48, 0x24, 0x18, 0x00, 0x08, 0x7C, 0x00, 
	0x48, 0x64, 0x54, 0x48, 0x48, 0x84, 0x94, 0x68, 
	0x1E, 0x10, 0x7C, 0x10, 0x5C, 0x94, 0x94, 0x64, 
	0x38, 0x4C, 0x2A, 0x11, 0x04, 0xC4, 0x34, 0x0C, 
	0x34, 0x4A, 0x4A, 0x34, 0x88, 0x54, 0x32, 0x1C, 
	0x00, 0x14, 0x00, 0x00, 0x40, 0x34, 0x00, 0x00, 
	0x10, 0x28, 0x44, 0x00, 0x28, 0x28, 0x28, 0x28, 
	0x00, 0x44, 0x28, 0x10, 0x04, 0x52, 0x0A, 0x04, 
	0x3C, 0x42, 0x5A, 0x1C, 0x78, 0x14, 0x12, 0x7C, 
	0x7E, 0x4A, 0x2A, 0x14, 0x38, 0x44, 0x42, 0x22, 
	0x7E, 0x42, 0x22, 0x1C, 0x7E, 0x4A, 0x4A, 0x42, 
	0x7E, 0x0A, 0x0A, 0x02, 0x38, 0x44, 0x52, 0x72, 
	0x7E, 0x08, 0x08, 0x7E, 0x42, 0x7E, 0x42, 0x00, 
	0x82, 0x7E, 0x02, 0x00, 0x7E, 0x08, 0x14, 0x62, 
	0x7E, 0x40, 0x40, 0x40, 0x7E, 0x0C, 0x0C, 0x7E, 
	0x7E, 0x08, 0x10, 0x7E, 0x38, 0x44, 0x22, 0x1C, 
	0x7E, 0x12, 0x12, 0x0C, 0x38, 0x44, 0x22, 0x5C, 
	0x7E, 0x12, 0x32, 0x4C, 0x20, 0x44, 0x4A, 0x32, 
	0x02, 0x3E, 0x42, 0x02, 0x3E, 0x40, 0x40, 0x3E, 
	0x3E, 0x40, 0x30, 0x0E, 0x7E, 0x30, 0x30, 0x7E, 
	0x62, 0x14, 0x68, 0x46, 0x0E, 0x70, 0x08, 0x06, 
	0x62, 0x52, 0x4A, 0x46, 0x00, 0x7E, 0x42, 0x00, 
	0x02, 0x0C, 0x30, 0x40, 0x00, 0x42, 0x7E, 0x00, 
	0x04, 0x02, 0x04, 0x00, 0x40, 0x40, 0x40, 0x40, 
	0x00, 0x08, 0x06, 0x00, 0x60, 0x54, 0x38, 0x40, 
	0x7E, 0x50, 0x48, 0x30, 0x30, 0x48, 0x48, 0x20, 
	0x30, 0x48, 0x28, 0x7E, 0x38, 0x54, 0x54, 0x08, 
	0x10, 0x7C, 0x12, 0x04, 0x18, 0xA4, 0x94, 0x7C, 
	0x7E, 0x10, 0x08, 0x70, 0x00, 0x08, 0x3A, 0x40, 
	0x00, 0x88, 0x7A, 0x00, 0x7E, 0x10, 0x30, 0x48, 
	0x02, 0x3E, 0x40, 0x00, 0x78, 0x08, 0x38, 0x70, 
	0x78, 0x08, 0x08, 0x70, 0x30, 0x48, 0x48, 0x30, 
	0xF8, 0x28, 0x28, 0x10, 0x10, 0x28, 0x28, 0xF8, 
	0x78, 0x10, 0x08, 0x08, 0x48, 0x54, 0x54, 0x20, 
	0x08, 0x3E, 0x48, 0x28, 0x38, 0x40, 0x40, 0x78, 
	0x38, 0x40, 0x20, 0x18, 0x38, 0x40, 0x70, 0x78, 
	0x48, 0x28, 0x50, 0x48, 0x18, 0xA0, 0xA0, 0x78, 
	0x48, 0x68, 0x58, 0x48, 0x10, 0x6C, 0x82, 0x00, 
	0x00, 0xFE, 0x00, 0x00, 0x00, 0x82, 0x6C, 0x10, 
	0x10, 0x08, 0x10, 0x08, 0x7E, 0x42, 0x42, 0x7E, 
}; 

#endif




