/*
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <uart.h>

int puts(const char *s)
{
	const char *i = s;
	while (*s)
		putchar(*s++);

	return s - i;
}
