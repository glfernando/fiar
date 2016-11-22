/*
 * (C) Copyright 2016, Fernando Lugo <lugo.fernando@gmail.com>
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */


#define CAR_ADDR	0x200000	/* abort page can do a good CAR */
#define CAR_SIZE	0x2000		/* 8K */


.text
.code32
.global _car_init
_car_init:

	## CAR is up and running.
	mov	$CAR_ADDR, %eax		# CAR address passed in eax
	mov	$CAR_SIZE, %ecx		# CAR size passed in ecx

	jmp _car_init_ret
