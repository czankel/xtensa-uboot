/*
 * (C) Copyright 2007 - 2010, Tensilica Inc.
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

#include <linux/ctype.h>
#include <linux/string.h>
#include <linux/stringify.h>
#include <asm/xtensa.h>
#include <common.h>
#include <command.h>

#include "lcd.h"

/*
 * Check board idendity.
 * (Print information about the board to stdout.)
 */

int checkboard (void)
{
	printf("Board:  XT-AV110: "
	       "Avnet board + Xilinx LX110 FPGA + Tensilica bitstream\n");
	return 0;
}


/*
 * Miscellaneous early initializations.
 * We use this hook to retrieve the processor frequency
 * and to initialize the LCD display.
 */

int misc_init_f(void)
{
	/*
	 * Obtain CPU clock frequency from board and cache in global 
	 * data structure (Hz). Return 0 on success (OK to continue), 
	 * else non-zero (hang).
	 */

#ifdef CONFIG_SYS_FPGAREG_FREQ
	gd->cpu_clk = (*(volatile unsigned long*) CONFIG_SYS_FPGAREG_FREQ);
#else
	/* early Tensilica bitstreams lack this reg, but most run at 50 MHz */
	gd->cpu_clk = 50000000UL;
#endif

	/* Initialize the LCD. */

	lcd_init();
	display_printf("U-Boot starting", NULL);

	return 0;
}


/*
 *  Miscellaneous late initializations.
 *  The environment has been set up, so we can set the Ethernet address.
 */

int misc_init_r(void)
{
#ifdef CONFIG_CMD_NET
	/*
	 * Initialize ethernet environment variables and board info.
	 * Default MAC address comes from CONFIG_ETHADDR + DIP switches 1-6.
	 */

	char *s = getenv("ethaddr");
	if (s == 0) {
		unsigned int x;
		s = __stringify(CONFIG_ETHBASE);
		x = (*(volatile u32 *) CONFIG_SYS_FPGAREG_DIPSW) & FPGAREG_MAC_MASK;
		sprintf(&s[15], "%02x", x);
		setenv("ethaddr", s);
	}
#endif /* CONFIG_CMD_NET */

	return 0;
}

/*
 * Print a formatted string to the board's ASCII character display.
 * String may have embedded newlines. Starts at top left and wraps long lines.
 */

#ifdef CONFIG_SYS_ASCDISP
void display_printf(const char *fmt, ...)
{
	va_list args;


	/* Warning: sprintf() can overflow this buffer if too small! */
	char buf[CONFIG_SYS_ASCDISP_BUFSZ];
	int i;

	va_start(args, fmt);
	vsprintf(buf, fmt, args);

	/* Truncate to one line and pad line with blanks. */
	for (i = 0; 
	     i < CONFIG_SYS_ASCDISP_BUFSZ-1 && buf[i] != '\0' && buf[i] != '\n'; 
	     ++i
	     );
	for (; i < CONFIG_SYS_ASCDISP_CHARS; ++i)
		buf[i] = ' ';
	buf[CONFIG_SYS_ASCDISP_CHARS] = 0;

	lcd_disp_at_pos(buf, 0);

	va_end(args);
}
#endif

#ifdef CONFIG_SHOW_BOOT_PROGRESS
/* Display a boot progress number on the LCD display. */
void show_boot_progress(int val)
{
	display_printf("Progress = %d", val);
}
#endif

/* Implement the "reset" command. */
void board_reset (void)
{
	*(vu_long*)CONFIG_SYS_FPGAREG_RESET = CONFIG_SYS_FPGAREG_RESET_CODE;
	/* Shouldn't reach here. */
}
