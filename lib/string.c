/*
 * (C) Copyright 2016, Fernando Lugo <lugo.fernando@gmail.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 *
 * Very simple string library (no optimized). Optimized version can be
 * implemented on lib/<ARCH>/ direcotry
 */

#include <common.h>

typedef unsigned op_t;

__weak void *memset(void *s, int c, size_t n)
{
	char *p = s;
	while (n--)
		*p++ = c;

	return s;
}

__weak void *memcpy(void *dst, const void *src, size_t n)
{
	char *d = dst;
	const char *s = src;

	if (dst == src) return dst;

	while (n--)
		*d++ = *s++;

	return dst;
}

__weak int memcmp(const void *s1, const void *s2, size_t n)
{
	const char *b1 = s1, *b2 = s2;
	for (; n--; ++b1, ++b2)
		if (*b1 != *b2)
			return (int)(*b2 - *b1);
	return 0;
}

void *memchr(const void *s, int c, size_t n)
{
	const unsigned char *p = s;
	for (; n--; ++p)
		if (c == (int)*p++)
			return (void *)p;

	return NULL;
}

char *strcpy(char *dst, const char *src)
{
	char *d = dst;
	for (; *src; ++d, ++src)
		*d = *src;
	return dst;
}

int strcmp(const char *dst, const char *src)
{
	for (; *src; ++dst, ++src)
		if (*src != *dst)
			return (int)(*src - *dst);
	return 0;
}
