/*
 * (C) Copyright 2016, Fernando Lugo <lugo.fernando@gmail.com>
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <processor.h>

.global _start
.global _car_init_ret

.text
hello_world:
	.ascii	"Hello World! stack ready!\n\r"
	len	= . - hello_world

car_error_msg:
	.ascii	"Error setting up CAR!\n\r"
	car_error_len	= . - car_error_msg

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

	# quick stack test
	call	stack_test

	call	init

	## if we came back here stack is working fine
	mov	$len, %cx
	mov	$hello_world, %esi
	jmp	print_and_hang
	jmp .

stack_test:
	mov	(%esp), %eax
	ret

_car_error:
	mov	$car_error_len, %ecx
	mov	$car_error_msg, %esi
	jmp	print_and_hang

print_and_hang:

uart_power_on:
	# enable com1
	mov	$0x8000f880, %eax
	mov	$0xcf8, %dx
	outl	%eax, %dx
	mov	$1, %eax
	mov	$0xcfc, %dx
	outl	%eax, %dx
	mfence

	# enable GBASE
	mov	$0x8000f848, %eax
	mov	$0xcf8, %dx
	outl	%eax, %dx
	mov	$0x503, %eax
	mov	$0xcfc, %dx
	outl	%eax, %dx
	mfence

	# enable IOBASE
	mov	$0x8000f84c, %eax
	mov	$0xcf8, %dx
	outl	%eax, %dx
	mov	$0xfed0c002, %eax
	mov	$0xcfc, %dx
	outl	%eax, %dx
	mfence

	# pin mux select UART RXD
	mov	0xfed0c520,%eax
	and	$0xfffffff8,%eax
	or	$0x1,%eax
	mov	%eax,0xfed0c520

	# pin mux select UART TXD
	mov	0xfed0c530,%eax
	and	$0xfffffff8,%eax
	or	$0x1,%eax
	mov	%eax,0xfed0c530

uart_init:
	mov	$0x3f9, %dx
	xor	%al, %al
	out	%ax, %dx

	mov	$0x3fc, %dx
	mov	$3, %al
	out	%ax, %dx

	mov	$0x3fa, %dx
	mov	$7, %al
	out	%ax, %dx

        mov	$0x3fb, %dx
        mov	$0x83, %al
        out	%al, %dx

	mov	$0x3f8, %dx
	mov	$0x1, %al
	out	%al, %dx

	mov	$0x3f9, %dx
	xor	%al, %al
	out	%al, %dx

	mov	$0x3fb, %dx
	mov	$0x3, %ax
	out	%al, %dx

uart_puts:
1:        # print message in SI
	mov	$0x3f8, %dx
	mov	$0x3fd, %dx
2:	in	%dx, %al
	and	$0x20, %al
	jz	2b
	mov	$0x3f8, %dx
	outsb
	loop	1b

	jmp .
