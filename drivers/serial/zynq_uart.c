/*
 * (C) Copyright 2017, Fernando Lugo <lugo.fernando@gmail.com>
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <common.h>
#include <io.h>

#define UART_CLOCK		50000000
#define UART_BASE		0xe0001000

#define UART_CONTROL		UART_BASE
#define UART_MODE		(UART_BASE + 0x4)
#define UART_BAUD		(UART_BASE + 0x18)
#define UART_CHNL_STATUS	(UART_BASE + 0x2c)
#define UART_TX_RX_FIFO		(UART_BASE + 0x30)

#define UART_SR_TX_EMPTY	(1 << 3)

void console_early_init(void)
{
}

int putchar(int c)
{
	while (!(readl(UART_CHNL_STATUS) & UART_SR_TX_EMPTY))
		;

	writel(c, UART_TX_RX_FIFO);
	if (c == '\n') putchar ('\r');

	return c;
}
