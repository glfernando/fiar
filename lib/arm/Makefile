#
# (C) Copyright 2017, Fernando Lugo <lugo.fernando@gmail.com>
#
# SPDX-License-Identifier:      GPL-2.0+
#

mkfile_path := $(lastword $(MAKEFILE_LIST))
cdir := $(patsubst %/,%,$(dir $(mkfile_path)))

objs += $(cdir)/aeabi_uldivmod.o $(cdir)/__udivmoddi4.o
