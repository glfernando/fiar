/*
 * (C) Copyright 2016, Fernando Lugo <lugo.fernando@gmail.com>
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#ifndef _MTRR_H
#define _MTRR_H

#define MTRR_TYPE_UC		0
#define MTRR_TYPE_WC		1
#define MTRR_TYPE_WT		4
#define MTRR_TYPE_WP		5
#define MTRR_TYPE_WB		6

#define MTRR_PHYS_MASK_VALID	(1 << 11)
#define MTRR_ENABLE		(1 << 11)

#endif /* _MTRR_H */
