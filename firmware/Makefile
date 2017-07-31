#!/bin/bash

# Version
MAJOR := 1
MINOR := 0
PATCH := 0
STATE := a
VERSION := $(MAJOR).$(MINOR)$(STATE)$(PATCH)
# Utilitys
BASE := $(call my-dir)
RM := rm -f
MKDIR := mkdir -p
CP := cp
# Sources
SRCS := $(wildcard src/*.c)
OBJS := $(patsubst %.c,%.o,$(SRCS))
LSS := $(patsubst %.c,%.lss,$(SRCS))
C_DEPS := $(patsubst %.c,%.d,$(SRCS))
# Dummy target for printing size.
SIZEDUMMY := sizedummy
# Flash and EPROGM file target.
FLASH_IMAGE := firmware.hex
EEPROM_IMAGE := firmware.eep
# AVR programmer.
AVRDUDE := avrdude
PROG := cavrisp # Default programmer
# Compiler Options
LIBS :=
MCU ?= atmega8
CFLAGS = -Wall -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -s -DF_CPU=16000000UL -mmcu=$(MCU) -O2 -I"include" -DVERSION=\"$(VERSION)\"
# Main target
TARGET := rs232rgblc


all: firmware.elf secondary-outputs
	@echo "Finished making $(TARGET) \n"

%.o : %.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc  $(CFLAGS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c $^ -o $@
	@echo 'Finished building: $<'
	@echo ' '

firmware.elf : $(OBJS)
	@echo 'Building target: $@'
	avr-gcc -Wl,-Map,firmware.map -o firmware.elf $(OBJS) $(LIBS)
	@echo 'Finished building target: $@'

firmware.lss: firmware.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S $^  > "$@"
	@echo 'Finished building: $@'
	@echo ' '

# Flash image.
firmware.hex: firmware.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex $^ "$@"
	@echo 'Finished building: $@'
	@echo ' '

# EEPROM
firmware.eep: firmware.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex $^ "$@"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: firmware.elf
	-avr-size --format=avr --mcu=$(MCU) $^
	@echo ''

secondary-outputs: $(LSS) $(SIZEDUMMY) $(FLASH_IMAGE) $(EEPROM_IMAGE)

install : $(FLASH_IMAGE)
	$(AVRDUDE) -pm8 -$(PROG) -Uflash:w:$(FLASH_IMAGE):a
#	$(AVRDUDE) -pm8 -c bsd -$(PROG) -U lfuse:w:0xE1:m -U hfuse:w:0xD9:m -U efuse:r:con:r

distribution : 
	$(RM) -r $(TARGET)-$(VERSION)
	$(MKDIR) $(TARGET)-$(VERSION)
	$(CP) -r src include Makefile $(TARGET)-$(VERSION)
	tar cf - $(TARGET)-$(VERSION) | gzip -c > $(TARGET)-$(VERSION).tar.gz
	$(RM) -r $(TARGET)-$(VERSION)

clean:
	$(RM) $(OBJS) $(LSS) firmware.elf $(FLASH_IMAGE) $(EEPROM_IMAGE) driver.map $(C_DEPS)

.PHONY: all clean secondary-outputs sizedummy distribution install

