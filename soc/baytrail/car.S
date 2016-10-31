/*
 * (C) Copyright 2016, Fernando Lugo <lugo.fernando@gmail.com>
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <processor.h>
#include <msr.h>
#include <mtrr.h>

#define CAR_ADDR	0xfeb00000	/* abort page can do a good CAR */
#define CAR_SIZE	0x2000		/* 8K */

#define NEM_SETUP	1
#define NEM_RUN		(1 << 1)

#define L2_CACHE_ENABLE	(1 << 8)

.text
.code32
.global _car_init
_car_init:
	## check for MTRR support
	# we know baytrail supports MTRR

	## get max physical address
	# we know it is 36bits for baytrail
	mov	$0xf, %edi	# bits [35:32] of physical address mask

	## get # of variable MTRRs
	mov	$MSR_IA32_MTRRCAP, %ecx
	rdmsr			# read MTRRCAP
	movzx	%al, %ebx	# eax[7:0] is the # of MTRRs
	shl	$1, %ebx	# each mtrr entry uses 2 MSRs

	## Initialize variable MTRRS
	# first entry is ROM as WP
	mov	$MSR_IA32_MTRR_PHYSBASE0, %ecx		# mtrr 0
	mov	$(TEXT_BASE | MTRR_TYPE_WP), %eax	# start of ROM
	xor	%edx, %edx				# address is only 32bits
	wrmsr						# write to the entry

	## now set the mask
	inc	%ecx			# mov ecx to mtrr phys mask
	dec	%ebx			# dec MTRR MSR register count
	# ROM ends at 0xffffffff so mask is same as TEXT_BASE
	mov	$(TEXT_BASE | MTRR_PHYS_MASK_VALID), %eax
	mov	%edi, %edx		# [35:32] mask is in edi
	wrmsr

	inc	%ecx		# increase to next MTRR entry
	dec	%ebx		# decrease MSR counter

	## set CAR region
	mov	$(CAR_ADDR | MTRR_TYPE_WB), %eax	# set car address as WB
	xor	%edx, %edx
	wrmsr

	## now set the mask
	inc	%ecx			# mov ecx to mtrr phys mask
	dec	%ebx			# dec MTRR MSR register count
	mov	$(~(CAR_SIZE - 1) | MTRR_PHYS_MASK_VALID), %eax
	mov	%edi, %edi		# [35:32] mask is in edi
	wrmsr

	inc	%ecx		# increase to next MTRR entry
	dec	%ebx

	## clear remaining MTRRs
	xor	%eax, %eax	# write 0 for disabling MTRR
	xor	%edx, %edx
1:	wrmsr
	inc	%ecx		# increase to next MSR reg
	dec	%ebx		# reduce MSR counter
	jnz	1b		# wait until no more MTRRs

	## enable MTRRs
	mov	$MSR_IA32_MTRR_DEF_TYPE, %ecx
	rdmsr
	or	$MTRR_ENABLE, %eax	# enable MTRR with default Cache to UC
	wrmsr

	## enable L2 cache (shoudln't be enabled by default?)
	mov	$MSR_BBL_CR_CTL3, %ecx
	rdmsr
	or	$L2_CACHE_ENABLE, %eax
	wrmsr

	## enable cache
	invd			# invalidate any previous cache
	mov	%cr0, %eax
	and	$~(X86_CR0_CD | X86_CR0_NW), %eax
	mov	%eax, %cr0

	## enable no eviction mode
	mov	$MSR_IA32_BIOS_CACHE_AS_RAM, %ecx
	rdmsr
	or	$NEM_SETUP | NEM_RUN, %eax
	wrmsr

	## CAR is up and running.
	mov	$CAR_ADDR, %eax		# CAR address passed in eax
	mov	$CAR_SIZE, %ecx		# CAR size passed in ecx

	jmp _car_init_ret
