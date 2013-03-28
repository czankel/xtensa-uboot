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

unsigned char *lcd_instr_addr = LCD_INSTR_ADDR;
unsigned char *lcd_data_addr = LCD_DATA_ADDR;


#define LCD_PAUSE_ITERATIONS	4000 
#define LCD_CLEAR		0x1
#define LCD_DISPLAY_ON		0xc

/* 8bit and 2 lines display */
#define LCD_DISPLAY_MODE8BIT	0x38
#define LCD_DISPLAY_MODE_4BIT   0x28
#define LCD_DISPLAY_POS		0x80
#define LCD_SHIFT_LEFT		0x18
#define LCD_SHIFT_RIGHT		0x1c

/*
 * This is used to stuff bytes once the LCD has been put in 4/8 bit mode
 */
static void lcd_put_byte(unsigned char *lcd_register_addr, unsigned char instr)
{
	*lcd_register_addr =  (instr & 0XF0);		/* High Nibble First */
	*lcd_register_addr =  (instr << 4) & 0XF0;
}


void lcd_init(void)
{
	*LCD_INSTR_ADDR = LCD_DISPLAY_MODE8BIT;
	udelay(20000);
	*LCD_INSTR_ADDR = LCD_DISPLAY_MODE8BIT;
	udelay(20000);
	*LCD_INSTR_ADDR = LCD_DISPLAY_MODE8BIT;
	udelay(20000);
	*LCD_INSTR_ADDR = LCD_DISPLAY_MODE_4BIT;
	udelay(20000);
	lcd_put_byte(LCD_INSTR_ADDR, LCD_DISPLAY_MODE_4BIT);
	udelay(20000);
	lcd_put_byte(LCD_INSTR_ADDR, LCD_DISPLAY_ON);
	udelay(20000);
	lcd_put_byte(LCD_INSTR_ADDR, LCD_CLEAR);
	udelay(20000);
}

void lcd_disp_at_pos (char *str, unsigned char pos)
{
	udelay(100);
	lcd_put_byte(LCD_INSTR_ADDR, LCD_DISPLAY_POS | pos);
	udelay(100);
	while (*str != 0){
		lcd_put_byte(LCD_DATA_ADDR, *str);
		udelay(200);
		str++;
	}
}

void lcd_shiftleft(void)
{
	lcd_put_byte(LCD_INSTR_ADDR, LCD_SHIFT_LEFT);
	udelay(20000);
}

void lcd_shiftright(void)
{
	lcd_put_byte(LCD_INSTR_ADDR, LCD_SHIFT_RIGHT);
	udelay(20000);
}

