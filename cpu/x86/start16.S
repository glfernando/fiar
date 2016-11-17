/*
 * (C) Copyright 2016, Fernando Lugo <lugo.fernando@gmail.com>
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <processor.h>

.text
.code16
.global _start16
_start16:
# Unfortunately clang is not very good at 16 bit code. And it inserts
# address-size overwrite prefix to lgdt instruction making gdt 32 bits
# address. For that reason we need to put opcode
	# load gdt table
	.byte 0x2e, 0x66, 0x0f, 0x1, 0x16; .word gdt	# = lgdtl   %cs:gdt
	# load idt table
	.byte 0x2e, 0x66, 0x0f, 0x1, 0x1e; .word idt	# = lidtl   %cs:idt

	## enter protect mode
	mov	%cr0, %eax
	or	$X86_CR0_PE, %eax
	mov	%eax, %cr0

	## load all segment register
	mov	$DATA_SEGMENT, %ax
	mov	%ax, %ds
	mov	%ax, %es
	mov	%ax, %fs
	mov	%ax, %gs
	mov	%ax, %ss

	## far jump to modify CS
	ljmpl	$CODE_SEGMENT, $_start

.align 4
## GDT and IDT Tables
	# null idt
idt:
	.word	0	# limit
	.long	0	# base

	# GDT use linux kernel style
gdt:
	.word	gdt_end - gdt - 1	# size
	.long	gdt			# gdt address
	.word	0			# padding to complete null descriptor

	.quad	0	# unused segment

	## code segment
	.word	0xffff	# limit low
	.byte	0, 0, 0	# base low
	.byte	0x9b	# P + S + code segment Execute/Read, accessed
	.byte	0xcf	# limit high + G + 32-bit segment
	.byte	0	# base high

	## data segment
	.word	0xffff	# limit low
	.byte	0, 0, 0	# base low
	.byte	0x93	# P + S + data segment Read/Write, accessed
	.byte	0xcf	# limit high + G + 32-bit segment
	.byte	0	# base high

	## 64 bits code segment
	.long	0	# don't care
	.byte	0	# don't care
	.byte	0x9b	# P + S + code segment Execute/Read, accessed
	.byte	0x20	# L
	.byte	0	# don't care
gdt_end:
