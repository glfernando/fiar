/*
 * (C) Copyright 2016, Fernando Lugo <lugo.fernando@gmail.com>
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <common.h>

__weak void soc_early_init() {}
__weak void board_early_init() {}
__weak void console_early_init() {}
__weak void cpu_init() {}
__weak void soc_init() {}
__weak void board_init() {}

extern char _data_start[];
extern char _data_end[];
extern char _data_load[];
extern char _bss_start[];
extern char _bss_end[];

extern int main(void);

__noreturn void init(void)
{
	soc_early_init();
	board_early_init();
	console_early_init();

	printf("fiar init\n");

	/*
	 * at this point ddr is already init, so lets initialze .bss and .data
	 * sections
	 */
	/* copy .data sections */
	memcpy(_data_start, _data_load, _data_end - _data_start);
	/* clean .bss section */
	memset(_bss_start, 0, _bss_end - _bss_start);
	/* now we can use global and static variables */

	cpu_init();
	soc_init();
	board_init();

	main();

	while (1)
		asm ("pause");
}
