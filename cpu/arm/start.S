/*
 * (C) Copyright 2017, Fernando Lugo <lugo.fernando@gmail.com>
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

.section .vectors, "x"
.global _reset
_reset:
        b _boot
        b .
        b .
        b .
        b .
        b .
        b .
        b .

_boot:
	@@ only cpu 0 continues
	mrc	p15, 0, r1, c0, c0, 5	@ read CPU ID reg
	and	r1, r1, #0xf		@ mask cpu id
	cmp	r1, #0
	beq	_continue		@ continue if id=0
_wait:	wfe
	b	_wait			@ wait forever

_continue:
	ldr sp, =_stack_top		@ set stack pointer

	bl init				@ jump to C code
	b .				@ we should never reach here

inv_dcache:
	bx	lr
