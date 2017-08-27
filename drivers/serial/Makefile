#
# (C) Copyright 2016, Fernando Lugo <lugo.fernando@gmail.com>
#
# SPDX-License-Identifier:      GPL-2.0+
#

mkfile_path := $(lastword $(MAKEFILE_LIST))
cdir := $(patsubst %/,%,$(dir $(mkfile_path)))

objs += $(cdir)/uart.o
ifeq ($(ARCH),i386)
objs += $(cdir)/ns16550_uart.o
else ifeq ($(ARCH),x86_64)
objs += $(cdir)/ns16550_uart.o
else
objs += $(cdir)/zynq_uart.o
endif
