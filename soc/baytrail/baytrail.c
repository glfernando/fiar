/*
 * (C) Copyright 2016, Fernando Lugo <lugo.fernando@gmail.com>
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <common.h>
#include <io.h>
#include <soc/baytrail.h>

static void baytrail_pcu_debug_uart_init(void)
{
	uint32_t x;

	/* enable com1 */
	outl(0x8000f880, 0xcf8);
	outl(1, 0xcfc);

	/* enable GBASE */
	outl(0x8000f848, 0xcf8);
	outl(0x503, 0xcfc);

	/* enable GBASE */
	outl(0x8000f84c, 0xcf8);
	outl(0xfed0c002, 0xcfc);

	/* pin mux select uart rxd */
	x = readl(0xfed0c520);
	x &= 0xfffffff8;
	x |= 1;
	writel(x, 0xfed0c520);

	/* pin mux select uart rxd */
	x = readl(0xfed0c530);
	x &= 0xfffffff8;
	x |= 1;
	writel(x, 0xfed0c530);
}

void soc_early_init()
{
	baytrail_pcu_debug_uart_init();
	/* uncomment below line if you want to debug fsp or some early init
	 * function. it is as early as we can get the console */
	//console_early_init();
#ifdef USE_FSP
	fsp_soc_init();
#endif
}
