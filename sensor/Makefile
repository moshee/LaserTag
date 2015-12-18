F_CPU   = 8000000L
MCU     = atmega328p

###############################################################################

PROJECT = $(notdir $(shell pwd))
#SRC     = $(wildcard *.c)
SRC     = light_ws2812.c sensor.c main.c
OBJ     = $(patsubst %.c, build/%.o, $(SRC))
HEX     = build/$(PROJECT).hex
OBJDIR  = build

all: $(HEX)

clean:
	rm -rf build/*.o build/*.hex build/*.elf

%.hex: %.elf
	avr-objcopy -R .eeprom -O ihex $< $@

build/$(PROJECT).elf: $(OBJ)
	avr-gcc -g -Os -Wall -Werror -Wl,--gc-sections -mmcu=$(MCU) -o $@ $(OBJ)

build/%.o: %.c
	avr-gcc -g -c -Os -Wall -Werror -ffunction-sections -fdata-sections -MMD -mmcu=$(MCU) -DF_CPU=$(F_CPU) $< -o $@

$(OBJ): | $(OBJDIR)

$(OBJDIR):
	mkdir -p build

upload: $(HEX)
	@avr-size --format=avr --mcu=atmega328p build/$(PROJECT).elf
	avrdude -p$(MCU) -cusbtiny -B 1 -Uflash:w:$(HEX):i
