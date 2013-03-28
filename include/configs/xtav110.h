/*
 * Copyright (C) 2007-2010 Tensilica, Inc.
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

#ifndef __CONFIG_H
#define __CONFIG_H

#include <asm/addrspace.h>

/*=====================*/
/* Board and Processor */
/*=====================*/
#define CONFIG_XTAV110				/* Avnet LX110 board + Xtensa */
#define CONFIG_SYS_CLK_FREQ	(gd->cpu_clk)	/* FPGA CPU freq after init */
#define CONFIG_TIMER_INDEX	0		/* Which (core) timer to use */
#define CONFIG_SYS_HZ		1000		/* Timer ticks per second */

/*=========================================*/
/* FPGA Registers (board info and control) */
/*=========================================*/
/*
 * These assume FPGA bitstreams from Tensilica release RB and up. Earlier
 * releases may not provide any/all of these registers or at these offsets.
 * Some of the FPGA registers are broken down into bitfields described by
 * SHIFT left amount and field WIDTH (bits), and also by a bitMASK.
 */

/* Date of FPGA bitstream build in binary coded decimal (BCD) */
#define CONFIG_SYS_FPGAREG_DATE	IOADDR(0x0D020000)
#define FPGAREG_MTH_SHIFT	24		/* BCD month 1..12 */
#define FPGAREG_MTH_WIDTH	8
#define FPGAREG_MTH_MASK	0xFF000000
#define FPGAREG_DAY_SHIFT	16		/* BCD day 1..31 */
#define FPGAREG_DAY_WIDTH	8
#define FPGAREG_DAY_MASK	0x00FF0000
#define FPGAREG_YEAR_SHIFT	0		/* BCD year 2001..9999 */
#define FPGAREG_YEAR_WIDTH	16
#define FPGAREG_YEAR_MASK	0x0000FFFF

/* FPGA core clock frequency in Hz (also input to UART) */
#define CONFIG_SYS_FPGAREG_FREQ	IOADDR(0x0D020004)	/* CPU clock frequency*/

/*
 * DIP switch (left=sw1=lsb=bit0, right=sw8=msb=bit7; off=0, on=1):
 *   Bits 0..5 set the lower 6 bits of the default ethernet MAC.
 *   Bit 6 is reserved for future use by Tensilica.
 *   Bit 7 maps the first 128KB of ROM address space at CONFIG_SYS_ROM_BASE to 
 *   the base of flash * (when on/1) or to the base of RAM (when off/0).
 */
#define CONFIG_SYS_FPGAREG_DIPSW IOADDR(0x0D02000C)	/* DIP switch (8 bit) */
#define FPGAREG_MAC_SHIFT	0			/* Ethernet MAC bits 0..5 */
#define FPGAREG_MAC_WIDTH	6
#define FPGAREG_MAC_MASK	0x3f
#define FPGAREG_BOOT_SHIFT	7			/* Boot ROM addr mapping */
#define FPGAREG_BOOT_WIDTH	1
#define FPGAREG_BOOT_MASK	0x80
#define FPGAREG_BOOT_RAM	0			/* boot from RAM */
#define FPGAREG_BOOT_FLASH	(1<<FPGAREG_BOOT_SHIFT)	/* boot from flash */

/* Force hard reset of board by writing a code to this register */
#define CONFIG_SYS_FPGAREG_RESET IOADDR(0x0D020010)	/* Hard reset board */
#define CONFIG_SYS_FPGAREG_RESET_CODE	0x0000DEAD	/*   by writing this code */

/*====================*/
/* ASCII Display Info */
/*====================*/
#define CONFIG_SYS_ASCDISP		1		/* Board has ASCII display */
#define CONFIG_SYS_ASCDISP_ADDR	IOADDR(0x0D0C0000) 	/* Display controller regs */
#define CONFIG_SYS_ASCDISP_LINES	2		/* Display number of lines */
#define CONFIG_SYS_ASCDISP_CHARS	16		/* Display chars per line */
#define CONFIG_SYS_ASCDISP_BUFSZ	64		/* Display printf buffer size */

/*====================*/
/* Serial Driver Info */
/*====================*/
#define CONFIG_SYS_NS16550
#define CONFIG_SYS_NS16550_SERIAL
#define CONFIG_SYS_NS16550_REG_SIZE	-4		/* NS16550 register size */
#define CONFIG_SYS_NS16550_COM1	IOADDR(0x0D050000) 	/* Base address of UART0 */
/* Input clk to NS16550 (in Hz; the SYS_CLK_FREQ is in kHz) */
#define CONFIG_SYS_NS16550_CLK		CONFIG_SYS_CLK_FREQ
#define CONFIG_CONS_INDEX	1			/* use UART0 for console */
#define CONFIG_BAUDRATE		38400			/* Default baud rate */
#define CONFIG_SYS_BAUDRATE_TABLE	{ 9600, 19200, 38400, 57600, 115200 }

/*=============*/
/* Ethernet Driver Info */
/*=============*/
#define CONFIG_OPENCORES_ETHERNET
#define CONFIG_ETHBASE		00:50:C2:13:6f:00 	/* Default MAC base (last  */
						  	/* byte comes from DIP sw) */
#define CONFIG_ENV_OVERWRITE				/* Allow MAC address changes */
#define CONFIG_SYS_OETH_REG_BASE	IOADDR(0x0D030000) /* Register base */
#define CONFIG_SYS_OETH_BD_BASE	IOADDR(0x0D030400) 	/* Buffer descriptors base */
#define CONFIG_SYS_OETH_BUFF_ADDR	IOADDR(0x0D800000) /* Buffer base */
#define CONFIG_NET_MULTI				/* Soon to be manditory */
#define CONFIG_NET_DO_NOT_TRY_ANOTHER

/*=====================*/
/* Flash & Environment */
/*=====================*/
/* XT-AV110 Flash has bottom block subdivided into 8x8KB parameter blocks */
#define CONFIG_SYS_FLASH_CFI				/* flash has a CFI interface */
#define CONFIG_FLASH_CFI_DRIVER				/* use generic CFI driver */
#undef  CONFIG_FLASH_CFI_LEGACY        			/* Only use CFI for flash */
#define CONFIG_SYS_FLASH_CFI_WIDTH	FLASH_CFI_16BIT	/* bus interface width */
#define CONFIG_SYS_MAX_FLASH_BANKS	1		/* max number of flash banks */
#define CONFIG_SYS_FLASH_SIZE		0x1000000	/* flash size 16MB */
#define CONFIG_SYS_FLASH_SECT_SZ	0x20000		/* primary   block size 128KB */
#define CONFIG_SYS_FLASH_PARMSECT_SZ	0x2000		/* parameter block size  8KB */
#define CONFIG_SYS_MAX_FLASH_SECT 	(CONFIG_SYS_FLASH_SECT_SZ/CONFIG_SYS_FLASH_PARMSECT_SZ + \
				 CONFIG_SYS_FLASH_SIZE/CONFIG_SYS_FLASH_SECT_SZ - 1)
#define CONFIG_SYS_FLASH_PROTECTION			/* hardware flash protection */
#define CONFIG_SYS_FLASH_BASE		IOADDR(0x08000000)	/* flash uncached base addr */
#define CONFIG_SYS_FLASH_TOP		(CONFIG_SYS_FLASH_BASE + CONFIG_SYS_FLASH_SIZE)

/* U-Boot monitor lives at the base of flash where it's mapped to ROM area */
#define CONFIG_SYS_MONITOR_BASE	CONFIG_SYS_FLASH_BASE	/* Image lives at flash base */

 /* 
  * u-boot doesn't have to must fit in 128K (0x20000) like the LX60 
  * which was the size of of SRAM on LX60.
  *
  * Currently 2 Flash sectors, 256K, is sufficient to fit u-boot on the LX110
  * even when compiled -O0. Checked in cpu linker script.
  */
#define CONFIG_SYS_MONITOR_LEN		(256 << 10)	/* monitor  size 128KB */

/* Put env. in top block (allows simple driver and avoids mangled memory map) */
/* Another option would be to put env. in 2nd param block offs 8KB, size 8KB */
#define CONFIG_ENV_IS_IN_FLASH				/* environment is in Flash */
#define CONFIG_ENV_OFFSET	(CONFIG_SYS_FLASH_SIZE - CONFIG_SYS_FLASH_SECT_SZ) /* top */
#define CONFIG_ENV_SIZE		CONFIG_SYS_FLASH_SECT_SZ /* env occupies 1 block */

#define CONFIG_SYS_FLASH_EMPTY_INFO            	/* print 'E' for empty sector on flinfo */

/* Try stuff from include/configs/P1_P2_RDB.h */
#define CONFIG_SYS_FLASH_ERASE_TOUT     60000   /* Flash Erase Timeout (ms) */
#define CONFIG_SYS_FLASH_WRITE_TOUT     500     /* Flash Write Timeout (ms) */

/* new uImage format support */
#define CONFIG_FIT              1
#define CONFIG_OF_LIBFDT
#define CONFIG_FIT_VERBOSE      1 /* enable fit_format_{error,warning}() */

/* Try stuff from include/configs/P1_P2_RDB.h */
#define CONFIG_HOSTNAME         "LX110"
#define CONFIG_UBOOTPATH        u-boot.bin	/* U-Boot image on TFTP server */
#define CONFIG_SYS_FLASH_ERASE_TOUT     60000   /* Flash Erase Timeout (ms) */
#define CONFIG_SYS_FLASH_WRITE_TOUT     500     /* Flash Write Timeout (ms) */
#define CONFIG_SYS_FLASH_AMD_CHECK_DQ7

/* From include/configs/rsk7203.h */
#define CONFIG_SYS_BOOTMAPSZ            (8 * 1024 * 1024)
 


/*===================*/
/* RAM Memory Layout */
/*===================*/
/*
 * Layout of the system RAM, top to bottom:
 *	stack (grows down toward heap)
 *	  (note: the boundary between stack and heap is fluid)
 *	malloc heap (grows up toward stack)
 *	global data and board info
 *	u-boot code (and unused space above)
 *	[linux boot parameters area (only if booting linux kernel)]
 *	free to load kernel or application (bulk of RAM)
 *	RAM vectors (most core configurations).
 */
#define CONFIG_STACKSIZE		(128 << 10)	/* stack size 128KB */
#define CONFIG_SYS_MALLOC_LEN		(256 << 10)	/* heap  size 256KB */
#define CONFIG_SYS_GBL_DATA_SIZE	128		/* global & board data size */

/* U-Boot malloc heap and stack area (grow together at top of RAM) */
#define CONFIG_SYS_HEAP_BASE  (CONFIG_SYS_MEMORY_TOP - CONFIG_STACKSIZE - CONFIG_SYS_MALLOC_LEN)

/* U-Boot area in RAM after unpacking ('make' symbol TEXT_BASE points here) */
#define CONFIG_SYS_TEXT_LEN		(CONFIG_SYS_MONITOR_LEN - CONFIG_SYS_GBL_DATA_SIZE)
#define CONFIG_SYS_TEXT_BASE		(CONFIG_SYS_HEAP_BASE - CONFIG_SYS_MONITOR_LEN)

/* Linux boot params area in RAM (used only when booting linux) */
#define CONFIG_SYS_BOOTPARAMS_LEN	(64  << 10)	/* linux boot param area size */
#define CONFIG_SYS_BOOTPARAMS_BASE	(CONFIG_SYS_TEXT_BASE - CONFIG_SYS_BOOTPARAMS_LEN)

/* U-Boot initial RAM area before it unpacks itself (not used in this port). */

/* Memory test is destructive so default must not overlap vectors or U-Boot */
#define CONFIG_SYS_MEMTEST_START	MEMADDR(0x001000000)	/* memtest start addr */
#define CONFIG_SYS_MEMTEST_END		MEMADDR(0x002000000)	/* memtest end addr+1 */

#define CONFIG_SYS_SDRAM_BASE		0x00000000		/* PHYSICAL Address */
#define CONFIG_SYS_SDRAM_SIZE		0x03000000 - 8		/*  48 MB (48 * 1024 * 1024) */
#define CONFIG_SYS_MEMORY_ADDR		MEMADDR(0x00000000)	/* VIRTUAL Address */
#define CONFIG_SYS_MEMORY_SIZE		0x03000000		/*  48 MB (48 * 1024 * 1024) */
#define CONFIG_SYS_LOAD_ADDR		MEMADDR(0x02000000)	/* Used by tftpboot; env var 'loadaddr' */
#define CONFIG_SYS_MEMORY_TOP		((CONFIG_SYS_MEMORY_BASE + CONFIG_SYS_MEMORY_SIZE) - 8)

/*==============================*/
/* U-Boot general configuration */
/*==============================*/
#undef	CONFIG_USE_IRQ					/* Keep it simple, poll only */
#define CONFIG_MISC_INIT_R
#define CONFIG_BOOTFILE			"uImage"	/* Boot file name */
#define CONFIG_SYS_PROMPT		"U-Boot> "	/* Monitor Command Prompt */
#define CONFIG_SYS_CBSIZE		1024		/* Console I/O Buffer Size  */
#define CONFIG_SYS_PBSIZE		(CONFIG_SYS_CBSIZE+sizeof(CONFIG_SYS_PROMPT)+16) /* Prt buf */
#define CONFIG_SYS_MAXARGS		16		/* max number of command args */
#define CONFIG_SYS_BARGSIZE		CONFIG_SYS_CBSIZE	/* Boot Argument Buffer Size */


/*==============================*/
/* U-Boot autoboot configuration */
/*==============================*/
#define CONFIG_BOOTDELAY	10	/* enable autoboot after 10 seconds */
#define CONFIG_BOOT_RETRY_TIME 60	/* retry autoboot after 60 secs	*/
#define CONFIG_BOOT_RETRY_MIN	1	/* can go down to 1 second timeout */
/* 
 * Be selective on what keys can delay or stop the autoboot process
 *	To stop use: " "
 */
#define CONFIG_AUTOBOOT_KEYED
#define CONFIG_AUTOBOOT_PROMPT		"Autobooting in %d seconds, " \
					"press <SPACE> to stop\n", bootdelay
#define CONFIG_AUTOBOOT_STOP_STR	" "
#undef CONFIG_AUTOBOOT_DELAY_STR
#define DEBUG_BOOTKEYS		0

						
#define CONFIG_VERSION_VARIABLE
#define CONFIG_AUTO_COMPLETE				/* Support tab autocompletion */
#if 0							/* Leave hush out for now */
#undef CONFIG_AUTO_COMPLETE				/* Not implemented for hush */
#define CONFIG_SYS_HUSH_PARSER
#define CONFIG_SYS_PROMPT_HUSH_PS2	"> "
#endif
#define CONFIG_CMDLINE_EDITING
#define CONFIG_SYS_LONGHELP
#define CONFIG_CRC32_VERIFY
#define CONFIG_MX_CYCLIC
#define CONFIG_SHOW_BOOT_PROGRESS

#ifdef DEBUG
#define CONFIG_PANIC_HANG       1               /* Require manual reboot */
#endif

/*=================*/
/* U-Boot commands */
/*=================*/
#include <config_cmd_default.h>
#define CONFIG_CMD_ASKENV
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_DIAG
#define CONFIG_CMD_PING
#define CONFIG_CMD_SAVES
#undef CONFIG_CMD_FPGA
#undef CONFIG_CMD_SETGETDCR
#undef CONFIG_CMD_XIMG

#endif /* __CONFIG_H */
