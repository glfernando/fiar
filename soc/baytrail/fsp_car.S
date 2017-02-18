/*
 * (C) Copyright 2016, Fernando Lugo <lugo.fernando@gmail.com>
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#define	IMAGE_BASE		0x1c
#define	TMP_RAM_INIT_OFFSET	0x30
#define FSP_HEADER_OFFSET	0x94

.text
.code32
.global _car_init
_car_init:
	mov	$(FSP_ADDR + FSP_HEADER_OFFSET), %ebx	# load fsp header addr
	mov	TMP_RAM_INIT_OFFSET(%ebx), %eax		# get ram init offset
	add	IMAGE_BASE(%ebx), %eax			# add image base addr
	## now we have the ram init address in eax
	lea	rom_tmp_ram_stack, %esp		# set fake stack parameters
	# now jump to temp ram init function
	jmp	*%eax

tmp_ram_init_done:
	## FSP initializes the ECX and EDX registers to point to a temporary
	## but writeable memory range. Register ECX points to the start of
	## this temporary memory range and EDX points to the end of the range

	mov	%ecx, %eax		# CAR address passed in eax
	sub	%ecx, %edx
	mov	%edx, %ecx		# CAR size passed in ecx

	jmp _car_init_ret

tmp_ram_init_params:
	.long	UCODE_ADDR
	.long	UCODE_SIZE
	.long	0xfff00000
	.long	0x00100000

rom_tmp_ram_stack:
	.long	tmp_ram_init_done
	.long	tmp_ram_init_params
