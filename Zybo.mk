#
# (C) Copyright 2017, Fernando Lugo <lugo.fernando@gmail.com>
#
# SPDX-License-Identifier:       GPL-2.0+
#

CONFIG_FILE=include/config_zybo.h
ARCH=arm
SOC=zynq
ifeq ($(USE_CLANG), 1)
CFLAGS += -target armv7a-none-eabi -mcpu=cortex-a9
endif
