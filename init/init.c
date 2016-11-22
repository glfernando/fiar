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

extern int main(void);

__noreturn void init(void)
{
	soc_early_init();
	board_early_init();
	console_early_init();

	printf("fiar init\n");

	cpu_init();
	soc_init();
	board_init();

	main();

	while (1)
		asm ("pause");
}
