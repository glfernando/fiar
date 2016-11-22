/*
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <io.h>

#define COM1		0x3f8
#define UART_BASE	COM1

#define UART_THR	UART_BASE
#define UART_RBR	UART_BASE
#define UART_DLL	UART_BASE
#define UART_IER	(UART_BASE + 0x1)
#define UART_DLH	(UART_BASE + 0x1)
#define UART_IIR	(UART_BASE + 0x2)
#define UART_FCR	(UART_BASE + 0x2)
#define UART_LCR	(UART_BASE + 0x3)
#define UART_MCR	(UART_BASE + 0x4)
#define UART_LSR	(UART_BASE + 0x5)
#define UART_MSR	(UART_BASE + 0x6)
#define UART_SR		(UART_BASE + 0x7)

#define UART_LSR_TEMT	0x40
#define UART_LSR_THRE	0x20

#define UART_LCR_DLAB	0x80

#define UART_FCR_FIFO_EN	0x1
#define UART_FCR_RXSR		0x2
#define UART_FCR_TXSR		0x4

#define UART_LCR_8N1    0x03

void console_early_init(void)
{
	/* wait for any pending transaction */
	while (!(inb(UART_LSR) & UART_LSR_TEMT))
		;

	/* disable interrupts */
	outb(0, UART_IER);

	/* enable fifos */
	outb(UART_FCR_FIFO_EN | UART_FCR_RXSR | UART_FCR_TXSR, UART_FCR);

	/* set 115200 baudrate and 8n1 */
	outb(UART_LCR_DLAB | UART_LCR_8N1, UART_LCR);
	outb(0, UART_DLH);
	outb(1, UART_DLL);
	outb(UART_LCR_8N1, UART_LCR);
}

int putchar(int c)
{
	/* wait until we can transmit */
	while (!(inb(UART_LSR) & UART_LSR_THRE))
		;

	outb(c, UART_THR);
	if (c == '\n')
		putchar('\r');

	return c;
}
