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
# Destination
DESTDIR ?=
PREFIX ?= /usr
INSTALL_LOCATION=$(DESTDIR)$(PREFIX)
# Sources
SRCS := $(wildcard src/*.c)
OBJS := $(patsubst %.c,%.o,$(SRCS))
HEADER := $(wildcard include/*.h)
# Compiler
CC ?= gcc
CFLAGS = -Wall -I"include" -fPIC -DR232LC_INTERNAL=1
LIBS =
#
PROJNAME := rs232rgblc
TARGET := librs232rgblc.so

all : $(TARGET)
	@echo "Finished making $(TARGET) \n"

$(TARGET) : CFLAGS += -DNDEBUG -O2
$(TARGET) : $(OBJS)
	$(CC) --shared $(CLFAGS) $^ -o $@ $(CLIBS)

%.o : %.c
	$(CC) $(CFLAGS) -c $^ -o $@

install : $(TARGET)
	@echo "Installing rs232rgblc userpace driver library.\n"
	$(MKDIR) $(INSTALL_LOCATION)/lib
	$(CP) $(TARGET) $(INSTALL_LOCATION)/lib
	$(MKDIR) $(INSTALL_LOCATION)/include/rs232lc
	$(CP) $(HEADER) $(INSTALL_LOCATION)/include/rs232lc

distribution : $(TARGET)
	$(RM) -r $(PROJNAME)-$(VERSION)
	$(MKDIR) $(PROJNAME)-$(VERSION)
	$(CP) -r src include $(PROJNAME)-$(VERSION)
	$(CP) Makefile $(PROJNAME)-$(VERSION)
	tar cf - $(PROJNAME)-$(VERSION) | gzip -c > $(PROJNAME)-$(VERSION).tar.gz
	$(RM) -r $(PROJNAME)-$(VERSION)

clean :
	$(RM) *.o

.PHONY : all install distribution clean

