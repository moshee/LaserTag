#include "STC3100.h"

int16_t sign_extend(uint16_t x, uint8_t size) {
	uint16_t mask = 0xFFFF << (size - 1);
	if ((x & mask) != 0) {
		// sign bit is set
		return (int16_t)(x | mask);
	}
	return (int16_t)(x & ~mask);
}

void STC3100::init(float mWh, float mOhm) {
	this->max_cap = mWh;
	this->r = mOhm;

	this->write8(STC3100_REG_MODE, GG_RES_14 | GG_CAL);
	this->write8(STC3100_REG_CTRL, GG_RST);
	this->write8(STC3100_REG_MODE, GG_RUN);

	// estimate initial state of charge using voltage
}

uint8_t STC3100::get_soc(void) {
	// soc = ...
	
	// calibrate at 10% and 90%
	// we can take 10% to be ~3.575V and 90% to be ~4.000V
	// obviously it depends on the load but we'll assume the average load is "very small"

	uint16_t soc = read16(STC3100_REG_RAM+0);
	return 0;
}

float STC3100::get_voltage(void) {
	// voltage data (mV) = voltage_code * 2.44
	int16_t v = sign_extend(read16(STC3100_REG_VOLTAGE), 12);
	return (float)v * 2.44;
}

float STC3100::get_current(void) {
	// current (mA) = current_code * 11.77 / R (mΩ)
	int16_t i = sign_extend(read16(STC3100_REG_CURRENT), 14);
	return (float)i * 11.77 / this->r;
}

float STC3100::get_charge(void) {
	// charge data (mAh) = 6.70 * charge_code / R (mΩ)
	int16_t dq = (int16_t)read16(STC3100_REG_CHARGE);
	return (float)dq * 6.70 / this->r;
}

float STC3100::get_temp(void) {
	// temperature (°C) = temperature_code * 0.125
	int16_t t = sign_extend(read16(STC3100_REG_TEMPERATURE), 12);
	return (float)t * 0.125;
}

uint16_t STC3100::get_counter(void) {
	return read16(STC3100_REG_COUNTER);
}

uint8_t STC3100::read8(uint8_t addr) {
	return 0;
}

uint16_t STC3100::read16(uint8_t addr) {
	uint8_t l, h;

	return ((uint16_t)h<<8) | (uint16_t)l;
}

void STC3100::write8(uint8_t addr, uint8_t val) {
}

void STC3100::write16(uint8_t addr, uint16_t val) {
}



