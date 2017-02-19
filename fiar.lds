/*
 * (C) Copyright 2016, Fernando Lugo <lugo.fernando@gmail.com>
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <config.h>

SECTIONS
{
	. = DATA_BASE;
	.data ALIGN(4): AT(_data_load) {
		_data_start = ADDR(.data);
                *(.data*);
		_data_end = .;
        }
	.bss ALIGN(4): AT(_bss_load) {
		_bss_start = ADDR(.bss);
                *(.bss*);
		. = ALIGN(4);
		_bss_end = .;
        }

	_stack_start = .;
	. = . + STACK_SIZE;
	_stack_end = .;

        . = TEXT_BASE;

	.text : AT(TEXT_BASE) {
                *(.text*);
        }

	.rodata ALIGN(4) : {
                *(.rodata*);
		. = ALIGN(4);
		_data_load = .;
        }

	. = _data_load;
	. = . + SIZEOF(.data);

	_bss_load = .;
	. = . + SIZEOF(.bss);

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
