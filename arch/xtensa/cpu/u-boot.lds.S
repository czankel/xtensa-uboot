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

#include <config.h>
#include <asm/ldscript.h>
#include <asm/arch/core.h>
#include <asm/addrspace.h>

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

  SECTION_ResetVector(XCHAL_RESET_VECTOR_VADDR, LMA_EQ_VMA)
  SECTION_VECTOR(WindowVectors,text,XCHAL_WINDOW_VECTORS_VADDR,FOLLOWING(.ResetVector.text))
  SECTION_VECTOR(KernelExceptionVector,literal,XCHAL_KERNEL_VECTOR_VADDR-8,FOLLOWING(.WindowVectors.text))
  SECTION_VECTOR(KernelExceptionVector,text,XCHAL_KERNEL_VECTOR_VADDR,FOLLOWING(.KernelExceptionVector.literal))
  SECTION_VECTOR(UserExceptionVector,literal,XCHAL_USER_VECTOR_VADDR-8,FOLLOWING(.KernelExceptionVector.text))
  SECTION_VECTOR(UserExceptionVector,text,XCHAL_USER_VECTOR_VADDR,FOLLOWING(.UserExceptionVector.literal))
  SECTION_VECTOR(DoubleExceptionVector,literal,XCHAL_DOUBLEEXC_VECTOR_VADDR-8,FOLLOWING(.UserExceptionVector.text))
  SECTION_VECTOR(DoubleExceptionVector,text,XCHAL_DOUBLEEXC_VECTOR_VADDR,FOLLOWING(.DoubleExceptionVector.literal))

  . = ALIGN(4096);

  __memory_avail_start = .;
  . = XTENSA_SYS_TEXT_BASE;
  __memory_avail_end = .;

  SECTION_text(ALIGN(16), FOLLOWING(.DoubleExceptionVector.text))
  SECTION_rodata(ALIGN(16),FOLLOWING(.text))
  SECTION_data(ALIGN(16),FOLLOWING(.rodata))
  SECTION_bss(ALIGN(16),FOLLOWING(.data))
  __stack = CONFIG_SYS_MEMORY_TOP;

  __heap_start = .;

  .reloc.data (LOADADDR(.bss) + SIZEOF(.bss) + 3) & ~ 3 : FOLLOWING(.bss)
  {
    __boot_reloc_table_start = ABSOLUTE(.);
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
   ASSERT(__monitor_end - __monitor_start <= CONFIG_SYS_MONITOR_LEN,
          "U-Boot ROM image is too large. Check optimization level.")

  SECTION_xtensa
  SECTION_debug
}
