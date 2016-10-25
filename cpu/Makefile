#
# (C) Copyright 2016, Fernando Lugo <lugo.fernando@gmail.com>
#
# SPDX-License-Identifier:      GPL-2.0+
#

mkfile_path := $(lastword $(MAKEFILE_LIST))
cdir := $(patsubst %/,%,$(dir $(mkfile_path)))
cpu_dir := $(cdir)

ifeq ($(ARCH),i386)
include $(cpu_dir)/x86/Makefile
endif
ifeq ($(ARCH),x86_64)
include $(cpu_dir)/x86/Makefile
endif
