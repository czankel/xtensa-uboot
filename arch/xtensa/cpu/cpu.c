/*
 * (C) Copyright 2008 - 2013 Tensilica Inc.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

/*
 * CPU specific code
 */

#include <common.h>
#include <command.h>
#include <linux/stringify.h>
#include <asm/string.h>
#include <asm/misc.h>

#ifndef __XTENSA_CALL0_ABI__
gd_t *gd;
#endif

/*
 * Print information about the CPU.
 */

int checkcpu(void)
{
	DECLARE_GLOBAL_DATA_PTR;
	char buf[120], mhz[8];

	sprintf(buf, "CPU:   Xtensa %s at %s MHz\n",
		XCHAL_CORE_ID, strmhz(mhz, gd->cpu_clk));
	puts(buf);
	return 0;
}

/*
 * Implement the "reset" command.
 * We need support from the board, though.
 */

int do_reset (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	board_reset();

	/* Shouldn't come back! */
	printf("****** RESET FAILED ******\n");
	return (0);
}

/*
 * We currently run always with caches enabled when running for mmemory.
 * Xtensa version D or later will support changing cache behavior, so
 * we could implement it if necessary.
 */

int dcache_status(void)
{
	return 1;
}

void dcache_enable(void)
{
}

void dcache_disable(void)
{
}

void flush_cache(ulong start_addr, ulong size)
{
	__flush_invalidate_dcache_range(start_addr, size);
	__invalidate_icache_range(start_addr, size);
}

void flush_dcache_range(ulong start_addr, ulong end_addr)
{
	__flush_invalidate_dcache_range(start_addr, end_addr - start_addr);
}
