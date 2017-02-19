/*
 * SPDX-License-Identifier:     GPL-2.0+
 */

#ifndef _STRING_H
#define _STRING_H

void *memset(void *dstpp, int c, size_t len);
void *memcpy(void *dstpp, const void *srcpp, size_t len);
int memcmp(const void * cs,const void * ct,size_t count);
void *memchr(const void *s, int c, size_t n);
char *strcpy(char *dst, const char *src);
int strcmp(const char *dst, const char *src);

#endif /* _STRING_H */
