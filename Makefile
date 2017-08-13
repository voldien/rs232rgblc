#!/bin/bash

# Version
MAJOR := 0
MINOR := 0
PATCH := 9
STATE := a
VERSION := $(MAJOR).$(MINOR)$(STATE)$(PATCH)
# Utilitys
RM := rm -f
CP := cp
MKDIR := mkdir -p
CHMOD := chmod
# Destination
DESTDIR ?=
PREFIX ?= /usr
INSTALL_LOCATION=$(DESTDIR)$(PREFIX)
# Compiler
CC ?= cc

all :
	$(MAKE) -C firmware
	$(MAKE) -C driver

install : $(TARGET)
	$(MAKE) -C driver/lib install CC=$(CC)
	$(MAKE) -C driver/bin install CC=$(CC)

install_firmware:
	$(MAKE) -C firmware install

distribution : $(TARGET)
	$(RM) -r $(TARGET)-$(VERSION)
	$(MKDIR) $(TARGET)-$(VERSION)
	$(CP) -r Makefile README.md  $(TARGET)-$(VERSION)
	tar cf - $(TARGET)-$(VERSION) | gzip -c > $(TARGET)-$(VERSION).tar.gz
	$(RM) -r $(TARGET)-$(VERSION)

clean :
	$(MAKE) -C firmware clean
	$(MAKE) -C driver/bin clean
	$(MAKE) -C driver/lib clean

.PHONY : all install install_firmware distribution clean
