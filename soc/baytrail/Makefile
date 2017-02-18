#
# (C) Copyright 2016, Fernando Lugo <lugo.fernando@gmail.com>
#
# SPDX-License-Identifier:      GPL-2.0+
#

mkfile_path := $(lastword $(MAKEFILE_LIST))
cdir := $(patsubst %/,%,$(dir $(mkfile_path)))

objs += $(cdir)/baytrail.o $(cdir)/ddr.o
ifeq ($(USE_FSP), 1)
objs += $(cdir)/fsp_car.o
else
objs += $(cdir)/car.o
endif
