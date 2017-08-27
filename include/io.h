/*
 * (C) Copyright 2016, Fernando Lugo <lugo.fernando@gmail.com>
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#ifndef _IO_H
#define _IO_H

#define readb(addr) (*(volatile uint8_t *) (addr))
#define readw(addr) (*(volatile uint16_t *) (addr))
#define readl(addr) (*(volatile uint32_t *) (addr))
#define readq(addr) (*(volatile uint64_t *) (addr))
#define __raw_readb readb
#define __raw_readw readw
#define __raw_readl readl
#define __raw_readq readq

#define writeb(b,addr) (*(volatile uint8_t *) (addr) = (b))
#define writew(b,addr) (*(volatile uint16_t *) (addr) = (b))
#define writel(b,addr) (*(volatile uint32_t *) (addr) = (b))
#define writeq(b,addr) (*(volatile uint64_t *) (addr) = (b))
#define __raw_writeb writeb
#define __raw_writew writew
#define __raw_writel writel
#define __raw_writeq writeq

#if __i386__ || __x86_64__
static inline unsigned int inl(int port)
{
	unsigned long val;
	__asm__ __volatile__("inl %w1, %k0" : "=a"(val) : "Nd"(port));
	return val;
}

static inline unsigned short inw(int p)
{
	unsigned short v;
	__asm__ __volatile__("inw %w1, %w0" : "=a"(v) : "Nd"(p));
	return v;
}

static inline unsigned char inb(int p)
{
	unsigned char v;
	__asm__ __volatile__("inb %w1, %b0" : "=a"(v) : "Nd"(p));
	return v;
}

static inline void outl(unsigned int v, int p)
{
	__asm__ __volatile__("outl %k0, %w1" : : "a"(v), "Nd"(p));
}

static inline void outw(unsigned short v, int p)
{
	__asm__ __volatile__("outw %w0, %w1" : : "a"(v), "Nd"(p));
}

static inline void outb(unsigned char v, int p)
{
	__asm__ __volatile__("outb %b0, %w1" : : "a"(v), "Nd"(p));
}
#endif /* __i386__ || __x86_64__ */

#endif /* _IO_H */
