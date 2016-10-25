/*
 * (C) Copyright 2016, Fernando Lugo <lugo.fernando@gmail.com>
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#ifndef _PROCESSOR_H
#define _PROCESSOR_H

#define X86_CR0_PE	1		/* Protection Enable */
#define X86_CR0_MP	(1 << 1)	/* Monitor Coprocessor */
#define X86_CR0_EM	(1 << 2)	/* Emulation */
#define X86_CR0_TS	(1 << 3)	/* Task Switched */
#define X86_CR0_ET	(1 << 4)	/* Extension Type */
#define X86_CR0_NE	(1 << 5)	/* Numeric Error */
#define X86_CR0_WP	(1 << 16)	/* Write Protect */
#define X86_CR0_AM	(1 << 18)	/* Alignment Mask */
#define X86_CR0_NW	(1 << 29)	/* Not Write-through */
#define X86_CR0_CD	(1 << 30)	/* Cache Disable */
#define X86_CR0_PG	(1 << 31)	/* Paging */

#define CODE_SEGMENT	0x10
#define DATA_SEGMENT	0x18
#define CODE64_SEGMENT	0x20

#endif /* _PROCESSOR_H */
