/*
 * (C) Copyright 2016, Fernando Lugo <lugo.fernando@gmail.com>
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

.section .resetvec, "ax"

.code16
reset_vector:
	cli		# clear interrupts
	cld		# clear direction flag
	jmp _start16	# to real mode startup code

	.org 0x10, 0xff	# fill the rest of the reset vector section with 0xff
