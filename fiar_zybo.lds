/*
 * (C) Copyright 2017, Fernando Lugo <lugo.fernando@gmail.com>
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <config.h>

ENTRY(_reset)
SECTIONS
{
        . = TEXT_BASE;

	.text : AT(TEXT_BASE) {
                *(.vectors);
                *(.text*);
        }
	.rodata ALIGN(4) : {
                *(.rodata*);
		. = ALIGN(4);
        }
	.data ALIGN(4): {
                _data_start = ADDR(.data);
		_data_load = .;
                *(.data*);
                _data_end = .;
        }
        .bss ALIGN(4): {
                _bss_start = ADDR(.bss);
                *(.bss*);
                . = ALIGN(4);
                _bss_end = .;
        }

	. = ALIGN(8);
	. = . + STACK_SIZE;
	_stack_top = .;

	/DISCARD/ :
        {
		*(.eh_frame*)
		*(.comment)
		*(.note*)
		*(.igot*)
		*(.iplt*)
		*(.rel*)
		*(.ARM.exidx*)
		*(.ARM.attributes*)
		*(.note.GNU-stack*)
        }
}
