#
# (C) Copyright 2016, Fernando Lugo <lugo.fernando@gmail.com>
#
# SPDX-License-Identifier:      GPL-2.0+
#

mkfile_path := $(lastword $(MAKEFILE_LIST))
lib_dir := $(patsubst %/,%,$(dir $(mkfile_path)))

ifeq ($(ARCH),i386)
include $(lib_dir)/x86/Makefile
endif
ifeq ($(ARCH),x86_64)
include $(lib_dir)/x86/Makefile
endif
