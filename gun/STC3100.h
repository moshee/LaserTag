#ifndef STC3100_H
#define STC3100_H

#include <stdint.h>
#include <Wire.h>

#define STC3100_ADDR 0x70

#define STC3100_REG_MODE        0  // R/W Mode register
#define STC3100_REG_CTRL        1  // R/W Control and status register
#define STC3100_REG_CHARGE      2  // R   Gas gauge charge data (16 bits)
#define STC3100_REG_COUNTER     4  // R   Number of conversions (16 bits)
#define STC3100_REG_CURRENT     6  // R   Battery current value (16 bits)
#define STC3100_REG_VOLTAGE     8  // R   Battery voltage value (16 bits)
#define STC3100_REG_TEMPERATURE 10 // R   Temperature value (16 bits)
#define STC3100_REG_ID          24 // R   Unique device ID (8 bytes)
#define STC3100_REG_RAM         32 // R/W User RAM (32 bytes)

// MODE register bits
#define SEL_EXT_CLK 0x01
#define GG_RES_14   0x00
#define GG_RES_13   0x02
#define GG_RES_12   0x04
#define GG_CAL      0x08
#define GG_RUN      0x10

// CTRL register bits
#define IO0DATA     0x01
#define GG_RST      0x02
#define GG_EOC      0x04
#define VTM_EOC     0x08
#define PORDET      0x10

// TODO: lookup table for voltage to SoC conversion estimate

class STC3100 {
public:
    void init(float mWh, float mOhm);
    uint8_t get_soc(void); // return a byte representing empty (0x00) to full (0xFF)
    float get_voltage(void);
    float get_current(void);
    float get_charge(void);
    float get_temp(void);
    uint16_t get_counter(void);

private:
    uint8_t read8(uint8_t addr);
    uint16_t read16(uint8_t addr);
    void write8(uint8_t addr, uint8_t val);
    void write16(uint8_t addr, uint16_t val);

    float max_cap;
    float r;
};

#endif /* STC3100_H */




