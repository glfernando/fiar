#
# (C) Copyright 2016, Fernando Lugo <lugo.fernando@gmail.com>
#
# SPDX-License-Identifier:       GPL-2.0+
#

CONFIG_FILE=include/config_minnowmax.h
SOC=baytrail
USE_FSP ?= 1
ifeq ($(USE_FSP), 1)
CFLAGS += -DUSE_FSP
endif
