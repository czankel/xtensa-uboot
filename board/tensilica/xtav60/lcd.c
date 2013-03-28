/*
 * Driver for the LCD display on the Tensilica XT-AV60 Board.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2001, 2006 Tensilica Inc.
 */

/*
 * The LCD functions busy wait due to limitations of the LCD controller.
 * This is a single-threaded boot-loader, so we don't care about that.
 */


#include <config.h>
#include <common.h>

#define LCD_INSTR_ADDR		(char*)(CONFIG_SYS_ASCDISP_ADDR + 0)
#define LCD_DATA_ADDR		(char*)(CONFIG_SYS_ASCDISP_ADDR + 4)

#define LCD_PAUSE_ITERATIONS	4000 
#define LCD_CLEAR		0x1
#define LCD_DISPLAY_ON		0xc

/* 8bit and 2 lines display */
#define LCD_DISPLAY_MODE8BIT	0x38
#define LCD_DISPLAY_POS		0x80
#define LCD_SHIFT_LEFT		0x18
#define LCD_SHIFT_RIGHT		0x1c

void lcd_init(void)
{
	*LCD_INSTR_ADDR = LCD_DISPLAY_MODE8BIT;
	udelay(5000);
	*LCD_INSTR_ADDR = LCD_DISPLAY_MODE8BIT;
	udelay(200);
	*LCD_INSTR_ADDR = LCD_DISPLAY_MODE8BIT;
	udelay(50);
	*LCD_INSTR_ADDR = LCD_DISPLAY_ON;
	udelay(50);
	*LCD_INSTR_ADDR = LCD_CLEAR;
	udelay(10000);
}

void lcd_disp_at_pos (char *str, unsigned char pos)
{
	*LCD_INSTR_ADDR = LCD_DISPLAY_POS | pos;
	udelay(100);
	while (*str != 0){
		*LCD_DATA_ADDR = *str;
		udelay(200);
		str++;
	}
}

void lcd_shiftleft(void)
{
	*LCD_INSTR_ADDR = LCD_SHIFT_LEFT;
	udelay(50);
}

void lcd_shiftright(void)
{
	*LCD_INSTR_ADDR = LCD_SHIFT_RIGHT;
	udelay(50);
}

