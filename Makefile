#
# (C) Copyright 2016, Fernando Lugo <lugo.fernando@gmail.com>
#
# SPDX-License-Identifier:	GPL-2.0+
#

USE_CLANG ?= 1

ifeq ($(USE_CLANG), 1)
CC	= clang
else
CC	= $(CROSS_COMPILE)gcc
endif

LD	= $(CROSS_COMPILE)ld.gold
NM	= $(CROSS_COMPILE)nm
OBJCOPY	= $(CROSS_COMPILE)objcopy

# Quiet mode
ifeq ($(V), 1)
Q =
else
Q = @
endif

CFLAGS = -fno-builtin
CFLAGS += -O2 -Wall -g
CFLAGS += -Iinclude -include include/config.h

ifeq ($(USE_CLANG), 1)
CFLAGS +=
else
CFLAGS += -fno-stack-protector -fno-delete-null-pointer-checks
endif

LDFLAGS =  -T _fiar.lds

# default to x86 32 bits
ARCH ?= i386

OBJCPYFLAGS = -S --gap-fill 0xff

LINKER_SCRIPT := fiar.lds

objs :=

include cpu/Makefile

# print variable for debugging
print-%  : ; @echo $* = $($*)

all: fiar.bin System.map

System.map : fiar.elf
	$(Q)$(NM) -a $< > $@

fiar.bin : fiar.elf
	$(Q)$(OBJCOPY) -O binary $(OBJCPYFLAGS) $< $@

fiar.elf : $(objs) _fiar.lds
	$(Q)$(LD) $(LDFLAGS) -o $@ $^

_fiar.lds : $(LINKER_SCRIPT)
	$(Q)$(CC) $(CFLAGS) -E -x assembler-with-cpp -P -o $@ $<

%.o : %.S
	$(Q)$(CC) $(CFLAGS) -c $< -o $@

%.o : %.c
	$(Q)$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(Q)find -name *.o | xargs rm -f
	$(Q)rm -f fiar.elf fiar.bin *.map _fiar.lds
