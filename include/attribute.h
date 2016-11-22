/*
 * (C) Copyright 2016, Fernando Lugo <lugo.fernando@gmail.com>
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#ifndef _ATTRIBUTE_H
#define _ATTRIBUTE_H

#define __weak		__attribute__((weak))
#define __packed	__attribute__((packed))
#define __noreturn	__attribute__((noreturn))
#define __aligned(x)	__attribute__((aligned(x)))

#endif /* _ATTRIBUTE_H */
