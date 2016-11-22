#
# (C) Copyright 2016, Fernando Lugo <lugo.fernando@gmail.com>
#
# SPDX-License-Identifier:      GPL-2.0+
#

mkfile_path := $(lastword $(MAKEFILE_LIST))
cdir := $(patsubst %/,%,$(dir $(mkfile_path)))

# div64 libraries for 32 bits only
ifneq ($(ARCH), x86_64)
objs += $(cdir)/__divdi3.o $(cdir)/__moddi3.o $(cdir)/__udivdi3.o
objs += $(cdir)/__udivmoddi4.o $(cdir)/__umoddi3.o
endif
