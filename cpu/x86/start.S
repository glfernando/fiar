/*
 * (C) Copyright 2016, Fernando Lugo <lugo.fernando@gmail.com>
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <processor.h>

.global _start
.global _car_init_ret

.text
.code32
_start:
	## setup cache as ram (platform specific)
	jmp	_car_init
_car_init_ret:
	## we should have a valid address in eax (size in ecx)
	test	$-1, %eax	# -1 means invalid address (error)
	je	_car_error

	## lets use CAR as stack
	lea	(%eax, %ecx), %esp	# load stack at the TOP of CAR

	call	init

_car_error:
	pause
	jmp	_car_error
