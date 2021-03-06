/*
 * (C) Copyright 2008 - 2013 Tensilica, Inc.
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
#include <asm/ldscript.h>
#include <asm/arch/core.h>
#include <asm/addrspace.h>
#include <asm-offsets.h>

OUTPUT_ARCH(xtensa)
ENTRY(_start)

/*
 * U-Boot resets from SYSROM and unpacks itself from a ROM store to RAM.
 * The reset vector is usually near the base of SYSROM and has room
 * above it for the ROM store into which the rest of U-Boot is packed.
 * The ROM store also needs to be above any other vectors that are in ROM.
 * If a core has its vectors near the top of ROM, this must be edited.
 *
 * Note that to run C code out of ROM, the processor would have to support
 * 'relocatable' exception vectors and provide a scratch memory for the
 * initial stack. Not all Xtensa processor configurations support that, so
 * we can simplify the boot process and unpack U-Boot to RAM immediately.
 * This, however, requires that memory have been initialized throug some
 * other means (serial ROM, for example) or are initialized early (requiring
 * an assembler functiont. See start.S for more details)
 */

SECTIONS
{
  . = + SIZEOF_HEADERS;
  SECTION_ResetVector(XCHAL_RESET_VECTOR_VADDR, LMA_EQ_VMA)

  .reloc_table ALIGN(4) : FOLLOWING(.ResetVector.text)
  {
    __reloc_table_start = ABSOLUTE(.);
    RELOCATE2(WindowVectors,text);
    RELOCATE2(KernelExceptionVector,literal);
    RELOCATE2(KernelExceptionVector,text);
    RELOCATE2(UserExceptionVector,literal);
    RELOCATE2(UserExceptionVector,text);
    RELOCATE2(DoubleExceptionVector,literal);
    RELOCATE2(DoubleExceptionVector,text);
    RELOCATE1(text);
    RELOCATE1(rodata);
    RELOCATE1(data);
    RELOCATE1(u_boot_list);
    __reloc_table_end = ABSOLUTE(.);
  }

  SECTION_VECTOR(WindowVectors,text,XCHAL_WINDOW_VECTORS_VADDR,FOLLOWING(.reloc_table))
  SECTION_VECTOR(KernelExceptionVector,literal,XCHAL_KERNEL_VECTOR_VADDR-8,FOLLOWING(.WindowVectors.text))
  SECTION_VECTOR(KernelExceptionVector,text,XCHAL_KERNEL_VECTOR_VADDR,FOLLOWING(.KernelExceptionVector.literal))
  SECTION_VECTOR(UserExceptionVector,literal,XCHAL_USER_VECTOR_VADDR-8,FOLLOWING(.KernelExceptionVector.text))
  SECTION_VECTOR(UserExceptionVector,text,XCHAL_USER_VECTOR_VADDR,FOLLOWING(.UserExceptionVector.literal))
  SECTION_VECTOR(DoubleExceptionVector,literal,XCHAL_DOUBLEEXC_VECTOR_VADDR-8,FOLLOWING(.UserExceptionVector.text))
  SECTION_VECTOR(DoubleExceptionVector,text,XCHAL_DOUBLEEXC_VECTOR_VADDR,FOLLOWING(.DoubleExceptionVector.literal))

 
  SECTION_text(CONFIG_SYS_TEXT_ADDR, FOLLOWING(.DoubleExceptionVector.text))
  SECTION_rodata(ALIGN(16), FOLLOWING(.text))
  SECTION_u_boot_list(ALIGN(16), FOLLOWING(.rodata))
  SECTION_data(ALIGN(16), FOLLOWING(.u_boot_list))

  __reloc_end = .;
  __init_end = .;

  SECTION_bss(__init_end (OVERLAY),)

  /*
   * On many Xtensa boards a region of RAM may be mapped to the ROM address
   * space to facilitate on-chip-debug, and U-Boot must fit with that region.
   * The config variables CONFIG_SYS_MONITOR_* define the region.
   * If U-Boot extends beyond this region it will appear discontiguous in the
   * address space and is in danger of overwriting itself during unpacking
   * ("relocation").
   * This causes U-Boot to crash in a way that is difficult to debug. On some
   * boards (such as xtav60) the region is small enough that U-Boot will not
   * fit if compiled entirely with -O0 (a common scenario). To avoid a lengthy
   * debugging session when this happens, ensure a link-time error occurs.
   *
   */

  __monitor_start = LOADADDR(.ResetVector.text);
  __monitor_end = LOADADDR(.data) + SIZEOF(.data);
   ASSERT(__monitor_end - __monitor_start <= CONFIG_SYS_MONITOR_LEN,
          "U-Boot ROM image is too large. Check optimization level.")

  SECTION_xtensa
  SECTION_debug

  /DISCARD/ : { *(.dynstr*) }
  /DISCARD/ : { *(.hash*) }
  /DISCARD/ : { *(.interp) }
  /DISCARD/ : { *(.got*) }
  /DISCARD/ : { *(.dynsym) }
}
