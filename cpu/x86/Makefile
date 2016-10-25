#
# (C) Copyright 2016, Fernando Lugo <lugo.fernando@gmail.com>
#
# SPDX-License-Identifier:      GPL-2.0+
#

mkfile_path := $(lastword $(MAKEFILE_LIST))
cdir := $(patsubst %/,%,$(dir $(mkfile_path)))

# building from baytrail right now. Fix later
CFLAGS += -march=atom

ifeq ($(ARCH), x86_64)
$(error $(ARCH) arch not functional yet)
BITS := 64
CFLAGS += -m64 -fPIE
LDFLAGS += -m elf_x86_64
else
BITS := 32
CFLAGS += -m32
LDFLAGS += -m elf_i386
endif

objs += $(cdir)/resetvec.o $(cdir)/start16.o $(cdir)/start.o
