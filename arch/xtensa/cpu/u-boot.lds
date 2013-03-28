/*
 * (C) Copyright 2008 Tensilica, Inc.
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
/* Automatically generated - do not edit */
/*
 * config_cmd_defaults.h - sane defaults for everyone
 *
 * Copyright (c) 2010-2011 Analog Devices Inc.
 *
 * Licensed under the GPL-2 or later.
 */
/*
 * config_defaults.h - sane defaults for everyone
 *
 * Copyright (c) 2009 Analog Devices Inc.
 *
 * Licensed under the GPL-2 or later.
 */
/* Support bootm-ing different OSes */
/*
 * Copyright (C) 2007-2008 Tensilica, Inc.
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
/*
 * include/asm-xtensa/addrspace.h
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2008-2010 Tensilica Inc.
 */
/*
 * Xtensa processor core configuration information.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (c) 1999-2007 Tensilica Inc.
 */
/****************************************************************************
	    Parameters Useful for Any Code, USER or PRIVILEGED
 ****************************************************************************/
/*
 *  Note:  Macros of the form XCHAL_HAVE_*** have a value of 1 if the option is
 *  configured, and a value of 0 otherwise.  These macros are always defined.
 */
/*----------------------------------------------------------------------
				ISA
  ----------------------------------------------------------------------*/
/*#define XCHAL_HAVE_POPC		0*/ /* POPC instruction */
/*#define XCHAL_HAVE_CRC		0*/ /* CRC instruction */
/*----------------------------------------------------------------------
				MISC
  ----------------------------------------------------------------------*/
/*  In T1050, applies to selected core load and store instructions (see ISA): */
/*
 *  These definitions describe the hardware targeted by this software.
 */
/*  If software targets a *range* of hardware versions, these are the bounds: */
/*----------------------------------------------------------------------
				CACHE
  ----------------------------------------------------------------------*/
/****************************************************************************
    Parameters Useful for PRIVILEGED (Supervisory or Non-Virtualized) Code
 ****************************************************************************/
/*----------------------------------------------------------------------
				CACHE
  ----------------------------------------------------------------------*/
/*  If present, cache size in bytes == (ways * 2^(linewidth + setwidth)).  */
/*  Number of cache sets in log2(lines per way):  */
/*  Cache set associativity (number of ways):  */
/*  Cache features:  */
/*  Number of encoded cache attr bits (see <xtensa/hal.h> for decoded bits):  */
/*----------------------------------------------------------------------
			INTERNAL I/D RAM/ROMs and XLMI
  ----------------------------------------------------------------------*/
/*----------------------------------------------------------------------
			INTERRUPTS and TIMERS
  ----------------------------------------------------------------------*/
 /* (always 1 in XEA1; levels 2 .. EXCM_LEVEL are "medium priority") */
/*  Masks of interrupts at each interrupt level:  */
/*  Masks of interrupts at each range 1..n of interrupt levels:  */
/*  Level of each interrupt:  */
/*  Type of each interrupt:  */
/*  Masks of interrupts for each type of interrupt:  */
/*  Interrupt numbers assigned to specific interrupt sources:  */
/*  Interrupt numbers for levels at which only one interrupt is configured:  */
/*  (There are many interrupts each at level(s) 1, 3.)  */
/*
 *  External interrupt vectors/levels.
 *  These macros describe how Xtensa processor interrupt numbers
 *  (as numbered internally, eg. in INTERRUPT and INTENABLE registers)
 *  map to external BInterrupt<n> pins, for those interrupts
 *  configured as external (level-triggered, edge-triggered, or NMI).
 *  See the Xtensa processor databook for more details.
 */
/*  Core interrupt numbers mapped to each EXTERNAL interrupt number:  */
/*----------------------------------------------------------------------
			EXCEPTIONS and VECTORS
  ----------------------------------------------------------------------*/
/*----------------------------------------------------------------------
				DEBUG
  ----------------------------------------------------------------------*/
/*----------------------------------------------------------------------
				MMU
  ----------------------------------------------------------------------*/
/*  See core-matmap.h header file for more details.  */
/*  If none of the above last 4 are set, it's a custom TLB configuration.  */
/*
 * MMU Memory Map
 *
 * V2 MMU:
 *   IO (uncached)	f0000000..ffffffff	-> f000000
 *   IO (cached)	e0000000..efffffff	-> f000000
 *   MEM (uncached)	d8000000..dfffffff	-> 0000000
 *   MEM (cached)	d0000000..d7ffffff	-> 0000000
 *
 * V3 MMU:
 *   IO (uncached)	f0000000..ffffffff	-> f000000
 *   MEM (uncached)	00000000..0fffffff	-> 0000000
 *
 */
/* Region typically starting at 0xf0000000 */
/* 
 * Region typically starting at 
 * 	0xD0000000 for V2 MMU 
 * and 
 * 	0x00000000 for V3 MMU 
 */
/*=====================*/
/* Board and Processor */
/*=====================*/
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
/* FPGA core clock frequency in Hz (also input to UART) */
/*
 * DIP switch (left=sw1=lsb=bit0, right=sw8=msb=bit7; off=0, on=1):
 *   Bits 0..5 set the lower 6 bits of the default ethernet MAC.
 *   Bit 6 is reserved for future use by Tensilica.
 *   Bit 7 maps the first 128KB of ROM address space at CONFIG_SYS_ROM_BASE to 
 *   the base of flash * (when on/1) or to the base of RAM (when off/0).
 */
/* Force hard reset of board by writing a code to this register */
/*====================*/
/* ASCII Display Info */
/*====================*/
/*====================*/
/* Serial Driver Info */
/*====================*/
/* Input clk to NS16550 (in Hz; the SYS_CLK_FREQ is in kHz) */
/*=============*/
/* Ethernet Driver Info */
/*=============*/
        /* byte comes from DIP sw) */
/*=====================*/
/* Flash & Environment */
/*=====================*/
/* XT-AV60 Flash has bottom block subdivided into 8x8KB parameter blocks */
/* U-Boot monitor lives at the base of flash where it's mapped to ROM area */
 /* 
 * u-boot must fit in 128K (0x20000), size of of SRAM, 
 * when running under for OCD; ie: 2 FLASH Sectors 
 */
/* Put env. in top block (allows simple driver and avoids mangled memory map) */
/* Another option would be to put env. in 2nd param block offs 8KB, size 8KB */
/* Try stiff from include/configs/P1_P2_RDB.h */
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
/* U-Boot malloc heap and stack area (grow together at top of RAM) */
/* U-Boot area in RAM after unpacking ('make' symbol TEXT_BASE points here) */
/* Linux boot params area in RAM (used only when booting linux) */
/* U-Boot initial RAM area before it unpacks itself (not used in this port). */
/* Memory test is destructive so default must not overlap vectors or U-Boot */
/*==============================*/
/* U-Boot general configuration */
/*==============================*/
/*==============================*/
/* U-Boot autoboot configuration */
/*==============================*/
/*
 *  * Be selective on what keys can delay or stop the autoboot process
 *   *      To stop use: " "
 *    */
/*=================*/
/* U-Boot commands */
/*=================*/
/*
 * Copyright 2007 Freescale Semiconductor, Inc.
 *
 * This file is licensed under the terms of the GNU General Public
 * License Version 2. This file is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */
/*
 * Alphabetical list of all commands that are configured by default.
 * This is essentially all commands minus those that are considered
 * "non-standard" for some reason (memory hogs, requires special
 * hardware, not fully tested, etc.).
 */
/*
 * config file header
 *
 * Copyright (C) 2009 Tensilica Inc.
 * Based on the Linux/Xtensa version of this header.
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
 * Xtensa processor core configuration information.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (c) 1999-2007 Tensilica Inc.
 */
/*
 * Copyright 2012 Texas Instruments
 *
 * This file is licensed under the terms of the GNU General Public
 * License Version 2. This file is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */
/* Rather than repeat this expression each time, add a define for it */
/*
 * (C) Copyright 2012
 * Ilya Yanok, ilya.yanok@gmail.com
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
 * Foundation, Inc.
 *
 * We don't use any commands in SPL, but generic networking code
 * has some features enabled/disabled based on CONFIG_CMD_*
 * options. As we want a minimal set of features included
 * into network SPL image, we undefine some config options here.
 */
/*
 * (C) Copyright 2007 Tensilica, Inc.
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
 * This linker script is pre-processed with CPP to avoid hard-coding
 * addresses that depend on the Xtensa core configuration, because
 * this FPGA board can be used with a huge variety of Xtensa cores.
 */
/*
 * Xtensa processor core configuration information.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (c) 1999-2007 Tensilica Inc.
 */
/*
 * include/asm-xtensa/addrspace.h
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2008-2010 Tensilica Inc.
 */
/*
 * Xtensa processor core configuration information.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (c) 1999-2007 Tensilica Inc.
 */
/*
 * Specify an output section that will be added to the ROM store table
 * (PACKED_SECTION) or one that will be resident in ROM (RESIDENT_SECTION).
 * 'symname' is a base name for section boundary symbols *_start & *_end.
 * 'lma' is the load address at which a section will be packed in ROM.
 * 'region' is the basename identifying a memory region and program header.
 * 'keep' prevents removal of empty sections (must be 'KEEP' or 'NOKEEP').
 */
/* In MMU configs there are two aliases of SYSROM, cached and uncached.
 * For various reasons it is simpler to use the uncached mapping for load
 * addresses, so ROM sections end up contiguous with the reset vector and
 * we get a compact binary image. However we can gain performance by doing
 * the unpacking from the cached ROM mapping. So we adjust all the load
 * addresses in the ROM store table with an offset to the cached mapping,
 * including the symbols referring to the ROM store table itself.
 */
/*
 * Xtensa processor core configuration information.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (c) 1999-2007 Tensilica Inc.
 */
/*
 * include/asm-xtensa/addrspace.h
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2008-2010 Tensilica Inc.
 */
/*
 * Xtensa processor core configuration information.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (c) 1999-2007 Tensilica Inc.
 */
OUTPUT_ARCH(xtensa)
ENTRY(_ResetVector)
/*
 * U-Boot resets from SYSROM and unpacks itself from a ROM store to RAM.
 * The reset vector is usually near the base of SYSROM and has room
 * above it for the ROM store into which the rest of U-Boot is packed.
 * The ROM store also needs to be above any other vectors that are in ROM.
 * If a core has its vectors near the top of ROM, this must be edited.
 */
SECTIONS
{
  . = + SIZEOF_HEADERS;
  .interp : { *(.interp) }
  .ResetVector.text 0xFE000000 : { . = .; KEEP(*(.ResetVector.text)); KEEP(*(.reset.literal .reset.text)) }
  .WindowVectors.text 0xD0000000 : AT(((LOADADDR(.ResetVector.text) + SIZEOF(.ResetVector.text) + 4 -1)) & ~(4 -1)) { . = ALIGN(4); _WindowVectors_text_start = ABSOLUTE(.); KEEP(*(.WindowVectors.text)) _WindowVectors_text_end = ABSOLUTE(.); }
  .KernelExceptionVector.literal 0xD0000300 -8 : AT(((LOADADDR(.WindowVectors.text) + SIZEOF(.WindowVectors.text) + 4 -1)) & ~(4 -1)) { . = ALIGN(4); _KernelExceptionVector_literal_start = ABSOLUTE(.); KEEP(*(.KernelExceptionVector.literal)) _KernelExceptionVector_literal_end = ABSOLUTE(.); }
  .KernelExceptionVector.text 0xD0000300 : AT(((LOADADDR(.KernelExceptionVector.literal) + SIZEOF(.KernelExceptionVector.literal) + 4 -1)) & ~(4 -1)) { . = ALIGN(4); _KernelExceptionVector_text_start = ABSOLUTE(.); KEEP(*(.KernelExceptionVector.text)) _KernelExceptionVector_text_end = ABSOLUTE(.); }
  .UserExceptionVector.literal 0xD0000340 -8 : AT(((LOADADDR(.KernelExceptionVector.text) + SIZEOF(.KernelExceptionVector.text) + 4 -1)) & ~(4 -1)) { . = ALIGN(4); _UserExceptionVector_literal_start = ABSOLUTE(.); KEEP(*(.UserExceptionVector.literal)) _UserExceptionVector_literal_end = ABSOLUTE(.); }
  .UserExceptionVector.text 0xD0000340 : AT(((LOADADDR(.UserExceptionVector.literal) + SIZEOF(.UserExceptionVector.literal) + 4 -1)) & ~(4 -1)) { . = ALIGN(4); _UserExceptionVector_text_start = ABSOLUTE(.); KEEP(*(.UserExceptionVector.text)) _UserExceptionVector_text_end = ABSOLUTE(.); }
  .DoubleExceptionVector.literal 0xD00003C0 -8 : AT(((LOADADDR(.UserExceptionVector.text) + SIZEOF(.UserExceptionVector.text) + 4 -1)) & ~(4 -1)) { . = ALIGN(4); _DoubleExceptionVector_literal_start = ABSOLUTE(.); KEEP(*(.DoubleExceptionVector.literal)) _DoubleExceptionVector_literal_end = ABSOLUTE(.); }
  .DoubleExceptionVector.text 0xD00003C0 : AT(((LOADADDR(.DoubleExceptionVector.literal) + SIZEOF(.DoubleExceptionVector.literal) + 4 -1)) & ~(4 -1)) { . = ALIGN(4); _DoubleExceptionVector_text_start = ABSOLUTE(.); KEEP(*(.DoubleExceptionVector.text)) _DoubleExceptionVector_text_end = ABSOLUTE(.); }
  . = ALIGN(4096);
  __memory_avail_start = .;
  . = ((((0xD0000000 - 0x00000000) + 0x04000000) - (128 << 10) - (256 << 10)) - (128 << 10));
  __memory_avail_end = .;
  .text ALIGN(16) : AT(((LOADADDR(.DoubleExceptionVector.text) + SIZEOF(.DoubleExceptionVector.text) + 4 -1)) & ~(4 -1)) { _text_start = ABSOLUTE(.); *(.literal .text) *(.literal.* .text.* .stub) *(.gnu.warning .gnu.linkonce.literal.*) *(.gnu.linkonce.t.*.literal .gnu.linkonce.t.*) *(.fini.literal) *(.fini) *(.gnu.version) _text_end = ABSOLUTE(.); }
  .rodata ALIGN(16) : AT(((LOADADDR(.text) + SIZEOF(.text) + 4 -1)) & ~(4 -1)) { _rodata_start = ABSOLUTE(.); *(.rodata) *(.rodata.*) *(.gnu.linkonce.r.*) *(.rodata1) __XT_EXCEPTION_TABLE__ = ABSOLUTE(.); *(.xt_except_table) *(.gcc_except_table) *(.gnu.linkonce.e.*) *(.gnu.version_r) . = ALIGN(16); __u_boot_cmd_start = ABSOLUTE(.); *(.u_boot_cmd) __u_boot_cmd_end = ABSOLUTE(.); _rodata_end = ABSOLUTE(.); }
  .data ALIGN(16) : AT(((LOADADDR(.rodata) + SIZEOF(.rodata) + 4 -1)) & ~(4 -1)) { _data_start = ABSOLUTE(.); *(.data) *(.data.*) *(.gnu.linkonce.d.*) *(.data1) *(.sdata) *(.sdata.*) *(.gnu.linkonce.s.*) *(.sdata2) *(.sdata2.*) *(.gnu.linkonce.s2.*) *(.jcr) *(.eh_frame) *(.dynamic) *(.gnu.version_d) _data_end = ABSOLUTE(.); }
  .bss ALIGN(16) : AT(((LOADADDR(.data) + SIZEOF(.data) + 4 -1)) & ~(4 -1)) { . = ALIGN (8); _bss_start = ABSOLUTE(.); __bss_start = ABSOLUTE(.); *(.dynsbss) *(.sbss) *(.sbss.*) *(.gnu.linkonce.sb.*) *(.scommon) *(.sbss2) *(.sbss2.*) *(.gnu.linkonce.sb2.*) *(.dynbss) *(.bss) *(.bss.*) *(.gnu.linkonce.b.*) *(COMMON) *(.sram.bss) . = ALIGN (8); _bss_end = ABSOLUTE(.); __bss_end = ABSOLUTE(.); _end = ALIGN(0x8); PROVIDE(end = ALIGN(0x8)); _stack_sentry = ALIGN(0x8); }
  __stack = ((0xD0000000 - 0x00000000) + 0x04000000);
  __heap_start = .;
  .reloc.data (LOADADDR(.bss) + SIZEOF(.bss) + 3) & ~ 3 : AT(((LOADADDR(.bss) + SIZEOF(.bss) + 4 -1)) & ~(4 -1))
  {
    __boot_reloc_table_start = ABSOLUTE(.);
    LONG(_WindowVectors_text_start); LONG(_WindowVectors_text_end); LONG(LOADADDR(.WindowVectors.text));;
    LONG(_KernelExceptionVector_literal_start); LONG(_KernelExceptionVector_literal_end); LONG(LOADADDR(.KernelExceptionVector.literal));;
    LONG(_KernelExceptionVector_text_start); LONG(_KernelExceptionVector_text_end); LONG(LOADADDR(.KernelExceptionVector.text));;
    LONG(_UserExceptionVector_literal_start); LONG(_UserExceptionVector_literal_end); LONG(LOADADDR(.UserExceptionVector.literal));;
    LONG(_UserExceptionVector_text_start); LONG(_UserExceptionVector_text_end); LONG(LOADADDR(.UserExceptionVector.text));;
    LONG(_DoubleExceptionVector_literal_start); LONG(_DoubleExceptionVector_literal_end); LONG(LOADADDR(.DoubleExceptionVector.literal));;
    LONG(_DoubleExceptionVector_text_start); LONG(_DoubleExceptionVector_text_end); LONG(LOADADDR(.DoubleExceptionVector.text));;
    LONG(_text_start); LONG(_text_end); LONG(LOADADDR(.text));;
    LONG(_rodata_start); LONG(_rodata_end); LONG(LOADADDR(.rodata));;
    LONG(_data_start); LONG(_data_end); LONG(LOADADDR(.data));;
    __boot_reloc_table_end = ABSOLUTE(.);
  }
  __monitor_start = LOADADDR(.ResetVector.text);
  __monitor_end = LOADADDR(.reloc.data) + SIZEOF(.reloc.data);
  /*
   * On many Xtensa boards a region of RAM may be mapped to the ROM address 
   * space to facilitate on-chip-debug, and U-Boot must fit with that region.
   * The config variables CONFIG_SYS_MONITOR_* define the region. If U-Boot extends
   * beyond this * region it will appear discontiguous in the address space
   * and is in danger of overwriting itself during unpacking ("relocation").
   * This causes U-Boot to crash in a way that is difficult to debug. On some
   * boards (such as xtav60) the region is small enough that U-Boot will not
   * fit if compiled entirely with -O0 (a common scenario). To avoid a lengthy
   * debugging session when this happens, ensure a link-time error occurs.
   *
   * Note: On the xtav200 this isn't a problem.
   */
   ASSERT(__monitor_end - __monitor_start <= (128 << 10),
          "U-Boot ROM image is too large. Check optimization level.")
  .xt.insn 0 : { KEEP (*(.xt.insn)) KEEP (*(.gnu.linkonce.x.*)) } .xt.prop 0 : { KEEP (*(.xt.prop)) KEEP (*(.xt.prop.*)) KEEP (*(.gnu.linkonce.prop.*)) } .xt.lit 0 : { KEEP (*(.xt.lit)) KEEP (*(.xt.lit.*)) KEEP (*(.gnu.linkonce.p.*)) } .xt.profile_range 0 : { KEEP (*(.xt.profile_range)) KEEP (*(.gnu.linkonce.profile_range.*)) } .xt.profile_ranges 0 : { KEEP (*(.xt.profile_ranges)) KEEP (*(.gnu.linkonce.xt.profile_ranges.*)) } .xt.profile_files 0 : { KEEP (*(.xt.profile_files)) KEEP (*(.gnu.linkonce.xt.profile_files.*)) }
  .debug 0 : { *(.debug) } .line 0 : { *(.line) } .debug_srcinfo 0 : { *(.debug_srcinfo) } .debug_sfnames 0 : { *(.debug_sfnames) } .debug_aranges 0 : { *(.debug_aranges) } .debug_pubnames 0 : { *(.debug_pubnames) } .debug_info 0 : { *(.debug_info) } .debug_abbrev 0 : { *(.debug_abbrev) } .debug_line 0 : { *(.debug_line) } .debug_frame 0 : { *(.debug_frame) } .debug_str 0 : { *(.debug_str) } .debug_loc 0 : { *(.debug_loc) } .debug_macinfo 0 : { *(.debug_macinfo) } .debug_weaknames 0 : { *(.debug_weaknames) } .debug_funcnames 0 : { *(.debug_funcnames) } .debug_typenames 0 : { *(.debug_typenames) } .debug_varnames 0 : { *(.debug_varnames) }
}
