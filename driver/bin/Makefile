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
SRCS := main.c
OBJS := $(patsubst %.c,%.o,$(SRCS))
# Compiler
CC ?= gcc
CFLAGS = -DR232LC_INTERNAL=1
LIBS := -lrs232rgblc
#
TARGET := rs232rgblc

$(TARGET) : CLFAGS += -DNDEBUG -O2
$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) main.c -o $@ $(CLIB) -lrs232rgblc

%.o : %.c
	$(CC) $(CFLAGS) -c $^ -o $@

install : $(TARGET)
	@echo "Installing rs232rgblc program controller.\n"
	$(MKDIR) $(INSTALL_LOCATION)/bin
	$(CP) $(TARGET) $(INSTALL_LOCATION)/bin

distribution : $(TARGET)
	$(RM) -r $(PROJNAME)-$(VERSION)
	$(MKDIR) $(PROJNAME)-$(VERSION)
	$(CP) -r src include $(PROJNAME)-$(VERSION)
	$(CP) Makefile $(PROJNAME)-$(VERSION)
	tar cf - $(PROJNAME)-$(VERSION) | gzip -c > $(PROJNAME)-$(VERSION).tar.gz
	$(RM) -r $(PROJNAME)-$(VERSION)

clean :
	$(RM) *.o

.PHONY : clean install distribution

