/*
 * (C) Copyright 2016, Fernando Lugo <lugo.fernando@gmail.com>
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <common.h>
#include <uart.h>

#define LEFT		(1 << 0)
#define ZEROPAD		(1 << 1)
#define SIGN		(1 << 2)
#define CAPS		(1 << 3)

/* 22 should be big enough for a 64 bits integer */
#define NUM_BUF_MAX	22

static void pr_c(char **pbuf, char c)
{
	pbuf ? *(*pbuf)++ = c : putchar(c);
}

static int pr_s(char **pbuf, char *s, int w, int f)
{
	char p = f & ZEROPAD ? '0' : ' ';
	int len, i;
	char *t;
	int n;

	/* calculate lenght of string */
	for (t = s; *t; ++t)
		;
	len = t - s;
	n = len > w ? len : w;

	if (!(f & LEFT))
		while (len < w--)
			pr_c(pbuf, p);

	for (i = 0; i < len; i++)
		pr_c(pbuf, *s++);

	while (len < w--)
		pr_c(pbuf, p);

	return n;
}

static int pr_num(char **pbuf, uint64_t n, int b, int w, int f)
{
	char num_buf[NUM_BUF_MAX];
	int t, neg = 0, pc = 0;
	unsigned mask = 0, shift = 0;
	int l = f & CAPS ? 'A' : 'a';
	char *s;

	if (n == 0ULL) {
		num_buf[0] = '0';
		num_buf[1] = '\0';
		return pr_s(pbuf, num_buf, w, f);
	}

	if (b == 10 && f & SIGN && (int64_t)n < 0) {
		neg = 1;
		n = -(int64_t)n;
	}

	s = num_buf + NUM_BUF_MAX - 1;
	*s = '\0';

	mask = b - 1;
	shift = 3 + b / 16;

	while (n) {
		if (b == 10) {
			t = n % b;
			n /= b;
		} else {
			t = n & mask;
			n >>= shift;
		}

		if (t > 9)
			 t += l - '0' - 10;
		*--s = t + '0';
	}

	if (neg) {
		if (w && (f & ZEROPAD)) {
			pr_c(pbuf, '-');
			pc++;
			--w;
		} else {
			*--s = '-';
		}
	}

	return pc + pr_s(pbuf, s, w, f);
}

static int vsprintf(char *buf, const char *fmt, va_list va)
{
	int n = 0;
	char **pbuf = buf ? &buf : NULL;

	for (; *fmt; ++fmt) {
		uint64_t num;
		int w, q, f, b;
		/* check for simple character */
		if (*fmt != '%') {
			pr_c(pbuf, *fmt);
			n++;
			continue;
		}

		fmt++;
		/* if no more characters or another % just printf % */
		if (!*fmt || *fmt == '%') {
			pr_c(pbuf, '%');
			n++;
			continue;
		}

		f = 0;
		if (*fmt == '-') {
			if (!*++fmt) break;
			f |= LEFT;
		}


		if (*fmt == '0') {
			if (!*++fmt) break;
			f |= ZEROPAD;
		}


		w = 0;
		while (*fmt && *fmt >= '0' && *fmt <= '9')
			w = w * 10 + *fmt++ - '0';

		if (!*fmt) break;

		q = 0;
		if (*fmt == 'l' || *fmt == 'L') {
			q = *fmt++;
			if (*fmt && *fmt == 'l') {
				if (!*++fmt) break;
				q = 'L';
			}
		}


		/* default base = 10 */
		b = 10;
		switch (*fmt) {
			char c[2];
			char *s;
		case 'c':
			c[0] = (char)va_arg(va, int);
			c[1] = '\0';
			n += pr_s(pbuf, c, w, f);
			continue;
		case 's':
			s = va_arg(va, char *);
			n += pr_s(pbuf, s ? : "(null)", w, f);
			continue;
		case 'o':
			b = 8;
			break;
		case 'X':
			f |= CAPS;
		case 'x':
			b = 16;
			break;
		case 'd':
		case 'i':
			f |= SIGN;
		case 'u':
			break;
		default:
			continue;
		}

		if (q == 'L') {
			num = va_arg(va, unsigned long long);
		} else if (q == 'l') {
			num = va_arg(va, unsigned long);
			if (f & SIGN)
				num = (long)num;
		} else {
			num = va_arg(va, unsigned int);
			if (f & SIGN)
				num = (int)num;
		}

		n += pr_num(pbuf, num, b, w, f);
	}

	if (buf) **pbuf = '\0';

	return n;
}

int printf(const char *fmt, ...)
{
	va_list args;
	int n;

	va_start(args, fmt);
	n = vsprintf(NULL, fmt, args);
	va_end(args);

	return n;
}

int sprintf(char *buf, const char *fmt, ...)
{
	va_list args;
	int n;

	va_start(args, fmt);
	n = vsprintf(buf, fmt, args);
	va_end(args);

	return n;
}
