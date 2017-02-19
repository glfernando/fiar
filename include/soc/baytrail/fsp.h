/*
 * (C) Copyright 2016, Fernando Lugo <lugo.fernando@gmail.com>
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#ifndef _BAYTRAIL_FSP_H
#define _BAYTRAIL_FSP_H

#define FSP_HEADER_OFFSET	0x94
#define VPD_IMAGE_ID		0x3157454956594c56	/* 'VLYVIEW1' */

struct fsp_header {
	uint32_t	sign;		//0x0
	uint32_t	header_len;	//0x4
	uint8_t		rsv1[3];	//0x8
	uint8_t		header_rev;	//0xb
	uint32_t	img_rev;	//0xc
	char		img_id[8];	//0x10
	uint32_t	img_size;	//0x18
	uint32_t	img_base;	//0x1c
	uint32_t	img_attr;	//0x20
	uint32_t	cfg_reg_off;	//0x24
	uint32_t	cfg_reg_size;	//0x28
	uint32_t	api_num;	//0x2c
	uint32_t	tmp_ram_init;	//0x30
	uint32_t	fsp_init;	//0x34
	uint32_t	notify_phase;	//0x38
	uint32_t	rsv2;		//0x3c
} __packed;

struct fsp_init_rt_common_buf {
	uint32_t *stack_top;
	uint32_t boot_mode;
	void *upd_data;
	uint32_t rsv[7];
} __packed;

struct fsp_init_rt_buf {
	struct fsp_init_rt_common_buf common;
};

struct fsp_init_params {
	void *nvs;
	void *rt_buf;
	void (*con_fn)(int, void *);
};

struct fsp_tmp_ram_init_params {
	uint32_t ucode_base;
	uint32_t ucode_size;
	uint32_t code_base;
	uint32_t code_size;
};

struct azalia_table_header {
	uint32_t vendor_dev_id;
	uint16_t sub_system_id;
	uint8_t rev_id;
	uint8_t front_panel_support;
	uint16_t num_rear_acks;
	uint16_t num_front_jacks;
} __packed;

struct azalia_table {
	struct azalia_table_header header;
	uint32_t *table_data;
} __packed;

struct azalia_cfg {
	uint8_t pme : 1;	// 0: Disable; 1: Enable
	uint8_t ds : 1; 	// 0: Docking not supported, 1:Docking supported
	uint8_t da : 1; 	// 0: Docking not attached; 1:Docking attached
	uint8_t hdmi_codec : 1; // 0: Disable; 1: Enable
	uint8_t azalia_vci : 1; // 0: Disable; 1: Enable
	uint8_t rsvd : 3;
	uint8_t azalia_verb_table_num; 		// # of verb tables
	struct azalia_table *azalia_table; 	// Ptr to the actual verb table
						// arrays
	uint16_t reset_wait_timer; // The delay in uS after Azalia reset
} __packed;

struct memory_down_data {
	uint8_t enable_memory_down;
	uint8_t dram_speed;
	uint8_t dram_type;
	uint8_t dimm_0_enable;
	uint8_t dimm_1_enable;
	uint8_t dimm_width;
	uint8_t dimm_density;
	uint8_t dimm_bus_width;
	uint8_t dimm_sides;	// ranks per DIMM
	uint8_t dimm_tcl;
	uint8_t dimm_trp_trcd;	// tRP and tRCD DRAM clk 5:12.5ns, 6:15ns, etc.
	uint8_t dimm_twr;	// tWR in DRAM clk
	uint8_t dimm_twtr;	// tWTR in DRAM clk
	uint8_t dimm_trrd;	// tRRD in DRAM clk
	uint8_t dimm_trtp;	// tRTP in DRAM clk
	uint8_t dimm_tfaw;	// tFAW in DRAM clk
} __packed;

struct upd_data_region {
	uint64_t signature;
	uint8_t reserved0[24];
	uint16_t mrc_init_tseg_size;
	uint16_t mrc_init_mmio_size;
	uint8_t mrc_init_spd_addr1;
	uint8_t mrc_init_spd_addr2;
	uint8_t emmc_boot_mode;
	uint8_t enable_sdio;
	uint8_t enable_sdcard;
	uint8_t enable_hsuart0;
	uint8_t enable_hsuart1;
	uint8_t enable_spi;
	uint8_t reserved1;
	uint8_t enable_sata;
	uint8_t sata_mode;
	uint8_t enable_azalia;
	uint32_t azalia_config_ptr;
	uint8_t enable_xhci;
	uint8_t enable_lpe;
	uint8_t lpss_sio_enable_pci_mode;
	uint8_t enable_dma0;
	uint8_t enable_dma1;
	uint8_t enable_i2_c0;
	uint8_t enable_i2_c1;
	uint8_t enable_i2_c2;
	uint8_t enable_i2_c3;
	uint8_t enable_i2_c4;
	uint8_t enable_i2_c5;
	uint8_t enable_i2_c6;
	uint8_t enable_pwm0;
	uint8_t enable_pwm1;
	uint8_t enable_hsi;
	uint8_t igd_dvmt50_pre_alloc;
	uint8_t aperture_size;
	uint8_t gtt_size;
	uint8_t	reserved2[5];
	uint8_t mrc_debug_msg;
	uint8_t isp_enable;
	uint8_t scc_enable_pci_mode;
	uint8_t igd_render_standby;
	uint8_t txe_uma_enable;
	uint8_t os_selection;
	uint8_t emmc45_ddr50_enabled;
	uint8_t emmc45_hs200_enabled;
	uint8_t emmc45_retune_timer_value;
	uint8_t enable_igd;
	uint8_t unused1[155];
	struct memory_down_data mem_params;
	uint16_t terminator;
} __packed;

struct vpd_region {
	uint64_t sign;
	uint32_t img_rev;
	uint32_t upd_offset;
	uint8_t unused[16];
	uint32_t fsp_rsvd_mem_len;
	uint8_t platform_type;
	uint8_t enable_secure_boot;
} __packed;

typedef int (*fsp_tmp_ram_init_t)(struct fsp_tmp_ram_init_params *p);
typedef int (*fsp_init_t)(struct fsp_init_params *p);

void fsp_soc_init(void);

#endif /* _BAYTRAIL_FSP_H */
