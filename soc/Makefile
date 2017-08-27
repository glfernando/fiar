#
# (C) Copyright 2016, Fernando Lugo <lugo.fernando@gmail.com>
#
# SPDX-License-Identifier:      GPL-2.0+
#

mkfile_path := $(lastword $(MAKEFILE_LIST))
cdir := $(patsubst %/,%,$(dir $(mkfile_path)))
soc_dir := $(cdir)

ifeq ($(SOC), baytrail)
include $(soc_dir)/baytrail/Makefile
else ifeq ($(SOC), bochs)
include $(soc_dir)/bochs/Makefile
else ifeq ($(SOC), zynq)
include $(soc_dir)/zynq/Makefile
endif
