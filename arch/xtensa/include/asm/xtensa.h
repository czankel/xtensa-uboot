/*
 * Copyright (C) 2007 Tensilica, Inc.
 *
 * A place for global definitions specific to Xtensa-based ports.
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef _XTENSA_H_
#define _XTENSA_H_

#include <stdarg.h>
#include <config.h>
#include <asm/u-boot.h>

/* Much of this is not specific to Xtensa and should move to a common header. */

/* Quote a macro value as a string constant. */
#define QUOTE1(s) #s
#define QUOTE(s) QUOTE1(s)

/* Align a value up to nearest n-byte boundary, where n is a power of 2. */
#define ALIGNUP(n, val) (((val) + (n)-1) & -(n))

#ifdef CONFIG_SYS_ASCDISP
/*
 * Print a formatted string to the board's ASCII character display.
 * String may have embedded newlines. Starts at top left and wraps long lines.
 */
extern void display_printf(const char *fmt, ...);
extern void lcd_disp_at_pos(char *, unsigned char);
#else
#define display_printf(fmt, args)
#endif

extern int oeth_initialize(bd_t *);

#endif /* _XTENSA_H_ */
