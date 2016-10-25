/*
 * (C) Copyright 2016, Fernando Lugo <lugo.fernando@gmail.com>
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <config.h>

SECTIONS
{
        . = TEXT_BASE;

	.text : {
                *(.text*);
        }

	.data ALIGN(4): {
                *(.data*);
        }

	.rodata ALIGN(4): {
                *(.rodata*);
        }

	.bss ALIGN(4): {
                *(.bss*);
        }

	. = 0xFFFFFFF0;
        .resetvec : {
                *(.resetvec*);
        }

	/DISCARD/ :
        {
		*(.eh_frame*)
		*(.comment)
		*(.note*)
		*(.igot*)
		*(.iplt*)
		*(.rel*)
        }
}
