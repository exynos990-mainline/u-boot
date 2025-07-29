// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (c) 2024, Linaro Ltd.
 * Author: Sam Protsenko <semen.protsenko@linaro.org>
 */

#include <efi_loader.h>
#include <env.h>
#include <init.h>
#include <mapmem.h>
#include <asm/io.h>

int dram_init(void)
{
	return fdtdec_setup_mem_size_base();
}

int dram_init_banksize(void)
{
	return fdtdec_setup_memory_banksize();
}

/* Read the unique SoC ID from OTP registers */
static u64 get_chip_id(void)
{
	return 0xDEADBEEF; // TODO: Read OTP
}

static void setup_serial(void)
{
	char serial_str[17] = { 0 };
	u64 serial_num;

	if (env_get("serial#"))
		return;

	serial_num = get_chip_id();
	snprintf(serial_str, sizeof(serial_str), "%016llx", serial_num);
	env_set("serial#", serial_str);
}

int board_late_init(void)
{
	setup_serial();

	return 0;
}
