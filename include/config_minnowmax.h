/*
 * (C) Copyright 2016, Fernando Lugo <lugo.fernando@gmail.com>
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#ifndef _CONFIG_H
#define _CONFIG_H

#define DATA_BASE	0x100000
#define TEXT_BASE	0xffff8000	/* 32K */
#define TSC_FREQ	12000000

#define FSP_ADDR	0xfffc0000
#define STACK_SIZE	(4096 * 2)

#define UCODE_ADDR	0xfffb0000
#define UCODE_SIZE	0xcc00

#define MINNOWMAX


#endif /* _CONFIG_H */
