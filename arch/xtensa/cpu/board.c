/*
 * (C) Copyright 2008 - 2013, Tensilica Inc.
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

#include <config.h>
#include <common.h>
#include <stdio_dev.h>
#include <version.h>
#include <net.h>
#include <config.h>
#include <linux/stringify.h>
#include <asm/xtensa.h>
#include <asm/addrspace.h>
#include <asm/bootparam.h>

/* Import linker-defined symbols (see u-boot.lds) */
extern void *__monitor_start, *__monitor_end;

void board_init_r(gd_t *id, ulong dest_addr);

DECLARE_GLOBAL_DATA_PTR;

#ifndef __XTENSA_CALL0_ABI__
gd_t *gd;
#endif

#ifndef CONFIG_IDENT_STRING
#define CONFIG_IDENT_STRING ""
#endif

ulong monitor_flash_len;	/* size of U-Boot packed image in flash */

const char version_string[] =
	U_BOOT_VERSION" (" __DATE__ " - " __TIME__ ")"CONFIG_IDENT_STRING;


/*
 * Initialize baudrate settings in global and board data structures.
 * This does not actually initialize the UART or set its baudrate.
 * Return 0 on success (OK to continue), else non-zero (hang). 
 */
static int init_baudrate(void)
{
        gd->baudrate = getenv_ulong("baudrate", 10, CONFIG_BAUDRATE);
        return 0;
}

/*
 * Initialize System RAM parameters and display RAM size.
 * Install dummy exception handler that ignores load/store exceptions.
 * Return 0 on success (OK to continue), else non-zero (hang). 
 */
static int init_sysram(void)
{
	gd->ram_size = CONFIG_SYS_MEMORY_SIZE;
	gd->ram_top = CONFIG_SYS_MEMORY_TOP;
	gd->relocaddr = CONFIG_SYS_TEXT_ADDR;

	gd->bd->bi_memstart = CONFIG_SYS_SDRAM_VADDR;
	gd->bd->bi_memsize  = CONFIG_SYS_SDRAM_SIZE;

	puts("DRAM:  ");
	print_size(gd->bd->bi_memsize, "\n");

	return 0;
}

/*
 * Breath some life into the board...
 *
 * The first part of initialization is running from Flash memory;
 * its main purpose is to initialize the RAM so that we
 * can relocate the monitor code to RAM.
 *
 * All attempts to come up with a "common" initialization sequence
 * that works for all boards and architectures failed: some of the
 * requirements are just _too_ different. To get rid of the resulting
 * mess of board dependend #ifdef'ed code we now make the whole
 * initialization sequence configurable to the user.
 *
 * The requirements for any new initalization function is simple: it
 * receives a pointer to the "global data" structure as it's only
 * argument, and returns an integer return code, where 0 means
 * "continue" and != 0 means "fatal error, hang the system".
 */
typedef int (init_fnc_t) (void);

init_fnc_t *init_sequence[] = {
	board_postclk_init,
	env_init,
	init_baudrate,
	serial_init,
	console_init_f,
	display_options,
	checkcpu,
#if defined(CONFIG_DISPLAY_CPUINFO)
	print_cpuinfo,
#endif
	checkboard,
	misc_init_f,
	init_sysram,
	board_init_r,
	NULL,
};


/*
 * Initialize board.
 */

void xtensa_board_init(ulong gd_addr)
{
        char *s;

	/*
	 * All RAM sections have been unpacked to RAM (relocated)
	 * and the board has been initialized.
	 */
	init_fnc_t **init_fnc_ptr;
	bd_t *bd;

	/* Don't cross 1GB range */
	ulong memsize = CONFIG_SYS_SDRAM_SIZE;
	ulong maxsize = 0x40000000 - (CONFIG_SYS_SDRAM_SIZE & 0x3fffffff);
	if (memsize > maxsize)
		memsize = maxsize;
	//ulong memtop = CONFIG_SYS_SDRAM_VADDR + memsize;

	gd = (gd_t *)gd_addr;
	memset((void *)gd, 0, sizeof(gd_t));
	gd->flags = GD_FLG_RELOC;	/* relocation is already done */

	bd = (bd_t *)((ulong)gd + ((sizeof(gd_t) + 15) & -16));
	memset((void *)bd, 0, sizeof(bd_t));
	gd->bd = bd;

	/* Reserve memory for passing linux boot parameters to kernel */
	bd->bi_boot_params = (ulong)bd + ((sizeof(bd_t) + 15) & -16);

	/*
	 * Perform initialization sequence, call functions enumerated above.
	 */
	for (init_fnc_ptr = init_sequence; *init_fnc_ptr; ++init_fnc_ptr) {
		if ((*init_fnc_ptr)() != 0) {
			hang ();
		}
	}

	/* Initialize from environment */
	if ((s = getenv ("loadaddr")) != NULL) {
		load_addr = simple_strtoul (s, NULL, 16);
	}
#if defined(CONFIG_CMD_NET)
	if ((s = getenv ("bootfile")) != NULL) {
		copy_filename (BootFile, s, sizeof (BootFile));
	}
#endif

#ifdef CONFIG_SYS_ASCDISP
	{
		char mhz[8];

		/* Announce our arrival and clock frequency */
		display_printf("U-Boot %5s MHz", strmhz(mhz, gd->cpu_clk));
	}
#endif

	while(1)
		main_loop();

	/* NOT REACHED */
}
