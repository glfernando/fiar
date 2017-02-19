/*
 * (C) Copyright 2016, Fernando Lugo <lugo.fernando@gmail.com>
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <common.h>
#include <io.h>
#include <soc/baytrail.h>

extern char _stack_end[];
extern void init(void);

const uint32_t azalia_table_data[] = {
	/* alc262 verb table - 10ec0262 */
	//pin complex (nid 0x11 )
	0x01171cf0,
	0x01171d11,
	0x01171e11,
	0x01171f41,
	//pin complex (nid 0x12 )
	0x01271cf0,
	0x01271d11,
	0x01271e11,
	0x01271f41,
	//pin complex (nid 0x14 )
	0x01471c10,
	0x01471d40,
	0x01471e01,
	0x01471f01,
	//pin complex (nid 0x15 )
	0x01571cf0,
	0x01571d11,
	0x01571e11,
	0x01571f41,
	//pin complex (nid 0x16 )
	0x01671cf0,
	0x01671d11,
	0x01671e11,
	0x01671f41,
	//pin complex (nid 0x18 )
	0x01871c20,
	0x01871d98,
	0x01871ea1,
	0x01871f01,
	//pin complex (nid 0x19 )
	0x01971c21,
	0x01971d98,
	0x01971ea1,
	0x01971f02,
	//pin complex (nid 0x1a )
	0x01a71c2f,
	0x01a71d30,
	0x01a71e81,
	0x01a71f01,
	//pin complex (nid 0x1b )
	0x01b71c1f,
	0x01b71d40,
	0x01b71e21,
	0x01b71f02,
	//pin complex (nid 0x1c )
	0x01c71cf0,
	0x01c71d11,
	0x01c71e11,
	0x01c71f41,
	//pin complex (nid 0x1d )
	0x01d71c01,
	0x01d71dc6,
	0x01d71e14,
	0x01d71f40,
	//pin complex (nid 0x1e )
	0x01e71cf0,
	0x01e71d11,
	0x01e71e11,
	0x01e71f41,
	//pin complex (nid 0x1f )
	0x01f71cf0,
	0x01f71d11,
	0x01f71e11,
	0x01f71f41
};

const struct azalia_table atable[] = {
	{
		/*
		 * VerbTable: (RealTek ALC262)
		 * Revision ID = 0xFF, support all steps
		 * Codec Verb Table For AZALIA
		 * Codec Address: CAd value (0/1/2)
		 * Codec Vendor: 0x10EC0262
		 */
		{
			0x10ec0262,	// Vendor ID/Device ID
			0x0000,		// SubSystem ID
			0xff,		// Revision ID
			0x01,		// Front panel support (1=yes, 2=no)
			0x000b,		// Number of Rear Jacks = 11
			0x0002		// Number of Front Jacks = 2

		},
		(uint32_t *)azalia_table_data
	}
};

const struct azalia_cfg acfg = {
	.pme = 1,
	.ds = 1,
	.da = 0,
	.hdmi_codec = 1,
	.azalia_vci = 1,
	.rsvd = 0,
	.azalia_verb_table_num = 1,
	.azalia_table = (struct azalia_table *)atable,
	.reset_wait_timer = 300,
};

static void mnwmax_fill_upd_data(struct upd_data_region *upd)
{
	/* fill default minnow max data */
	upd->mrc_init_mmio_size = 0x800;
	upd->mrc_init_spd_addr1 = 0xa0;
	upd->mrc_init_spd_addr2 = 0xa2;
	upd->emmc_boot_mode = 1;
	upd->enable_sdio = 1;
	upd->enable_sdcard = 1;
	upd->enable_hsuart1 = 1;
	upd->enable_spi = 1;
	upd->enable_sata = 1;
	upd->sata_mode = 1;
	upd->enable_azalia = 0;
	upd->enable_xhci = 1;
	upd->enable_lpe = 1;
	upd->lpss_sio_enable_pci_mode = 1;
	upd->enable_dma0 = 1;
	upd->enable_dma1 = 1;
	upd->enable_i2_c0 = 1;
	upd->enable_i2_c1 = 1;
	upd->enable_i2_c2 = 1;
	upd->enable_i2_c3 = 1;
	upd->enable_i2_c4 = 1;
	upd->enable_i2_c5 = 1;
	upd->enable_i2_c6 = 1;
	upd->enable_pwm0 = 1;
	upd->enable_pwm1 = 1;
	upd->enable_hsi = 1;
	upd->igd_dvmt50_pre_alloc = 2;
	upd->aperture_size = 2;
	upd->gtt_size = 2;
	upd->mrc_debug_msg = 0;
	upd->isp_enable = 0;
	upd->scc_enable_pci_mode = 1;
	upd->igd_render_standby = 0;
	upd->txe_uma_enable = 0;
	upd->os_selection = 4;
	upd->emmc45_ddr50_enabled = 1;
	upd->emmc45_hs200_enabled = 0;
	upd->emmc45_retune_timer_value = 8;
	upd->enable_igd = 1;
	upd->mem_params.enable_memory_down = 1;
	upd->mem_params.dram_speed = 1;
	upd->mem_params.dram_type = 1;
	upd->mem_params.dimm_0_enable = 1;
	upd->mem_params.dimm_1_enable = 0;
	upd->mem_params.dimm_width = 1;
	upd->mem_params.dimm_density = 2;
	upd->mem_params.dimm_bus_width = 3;
	upd->mem_params.dimm_sides = 0;
	upd->mem_params.dimm_tcl = 0xb;
	upd->mem_params.dimm_trp_trcd = 0xb;
	upd->mem_params.dimm_twr = 0xc;
	upd->mem_params.dimm_twtr = 6;
	upd->mem_params.dimm_trrd = 6;
	upd->mem_params.dimm_trtp = 6;
	upd->mem_params.dimm_tfaw = 0x14;

}

static void fsp_continue(int status, void *hob)
{
	/* lets go to init again */
	init();
}

void fsp_soc_init(void)
{
	struct fsp_header *h;
	struct fsp_init_params p;
	struct fsp_init_rt_buf rt;
	fsp_init_t fsp_init;
	struct upd_data_region upd;
	struct vpd_region *vpd;

	/* lets test memory to see if ddr is initializa */
	writel(0xcafecafe, 0xffff0);
	/*
	 * at boot time first MB is mapped to top MB. So lets try to write
	 * the resec vector (0xffff0) if we can write to that address it is
	 * not the reset vector anymore
	 */
	if (readl(0xffff0) == 0xcafecafe) {
		/* memory already initialized */
		return;
	}

	memset(&rt, 0, sizeof rt);

	h = (struct fsp_header *)(FSP_ADDR + FSP_HEADER_OFFSET);
	fsp_init = (fsp_init_t)(h->img_base + h->fsp_init);

	vpd = (struct vpd_region *)(h->img_base + h->cfg_reg_off);

	memcpy(&upd, (void *)(h->img_base + vpd->upd_offset), sizeof upd);
	upd.azalia_config_ptr = (uint32_t)&acfg;

	rt.common.stack_top = (void *)_stack_end;
	rt.common.boot_mode = 0;
	rt.common.upd_data = &upd;

	mnwmax_fill_upd_data(&upd);

	p.nvs = NULL;
	p.rt_buf = &rt;
	p.con_fn = fsp_continue;

	/* call into FSP init function */
	fsp_init(&p);

	/* we should never reach here */
	asm volatile ("jmp .");
}
