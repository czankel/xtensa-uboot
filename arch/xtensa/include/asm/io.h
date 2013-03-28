/*
 * IO header file
 *
 * Copyright (C) 2001-2007 Tensilica Inc.
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

#ifndef _XTENSA_IO_H
#define _XTENSA_IO_H

#include <linux/types.h>
#include <asm/byteorder.h>


/*
 * swap functions to change byte order from little-endian to big-endian and
 * vice versa.
 */

static inline unsigned short _swapw (unsigned short v)
{
	return (v << 8) | (v >> 8);
}

static inline unsigned int _swapl (unsigned int v)
{
	return (v << 24) | ((v & 0xff00) << 8) | ((v >> 8) & 0xff00) | (v >> 24);
}

static inline void iounmap(void *addr)
{
}

/*
 * Generic I/O
 */

#define readb(addr) \
	({ unsigned char __v = (*(volatile unsigned char *)(addr)); __v; })
#define readw(addr) \
	({ unsigned short __v = (*(volatile unsigned short *)(addr)); __v; })
#define readl(addr) \
	({ unsigned int __v = (*(volatile unsigned int *)(addr)); __v; })
#define writeb(b, addr) (void)((*(volatile unsigned char *)(addr)) = (b))
#define writew(b, addr) (void)((*(volatile unsigned short *)(addr)) = (b))
#define writel(b, addr) (void)((*(volatile unsigned int *)(addr)) = (b))

#define __raw_readb readb
#define __raw_readw readw
#define __raw_readl readl
#define __raw_writeb writeb
#define __raw_writew writew
#define __raw_writel writel

/* These are the definitions for the x86 IO instructions
 * inb/inw/inl/outb/outw/outl, the "string" versions
 * insb/insw/insl/outsb/outsw/outsl, and the "pausing" versions
 * inb_p/inw_p/...
 * The macros don't do byte-swapping.
 */

#define inb(port)		readb((u8 *)((port)))
#define outb(val, port)		writeb((val),(u8 *)((unsigned long)(port)))
#define inw(port)		readw((u16 *)((port)))
#define outw(val, port)		writew((val),(u16 *)((unsigned long)(port)))
#define inl(port)		readl((u32 *)((port)))
#define outl(val, port)		writel((val),(u32 *)((unsigned long)(port)))

#define inb_p(port)		inb((port))
#define outb_p(val, port)	outb((val), (port))
#define inw_p(port)		inw((port))
#define outw_p(val, port)	outw((val), (port))
#define inl_p(port)		inl((port))
#define outl_p(val, port)	outl((val), (port))

extern void insb (unsigned long port, void *dst, unsigned long count);
extern void insw (unsigned long port, void *dst, unsigned long count);
extern void insl (unsigned long port, void *dst, unsigned long count);
extern void outsb (unsigned long port, const void *src, unsigned long count);
extern void outsw (unsigned long port, const void *src, unsigned long count);
extern void outsl (unsigned long port, const void *src, unsigned long count);

#define IO_SPACE_LIMIT ~0

#define memset_io(a,b,c)       memset((void *)(a),(b),(c))
#define memcpy_fromio(a,b,c)   memcpy((a),(void *)(b),(c))
#define memcpy_toio(a,b,c)      memcpy((void *)(a),(b),(c))

/* At this point the Xtensa doesn't provide byte swap instructions */

#ifdef __XTENSA_EB__
# define in_8(addr) (*(u8*)(addr))
# define in_le16(addr) _swapw(*(u16*)(addr))
# define in_le32(addr) _swapl(*(u32*)(addr))
# define out_8(b, addr) *(u8*)(addr) = (b)
# define out_le16(b, addr) *(u16*)(addr) = _swapw(b)
# define out_le32(b, addr) *(u32*)(addr) = _swapl(b)
#elif defined(__XTENSA_EL__)
# define in_8(addr)  (*(u8*)(addr))
# define in_le16(addr) (*(u16*)(addr))
# define in_le32(addr) (*(u32*)(addr))
# define out_8(b, addr) *(u8*)(addr) = (b)
# define out_le16(b, addr) *(u16*)(addr) = (b)
# define out_le32(b, addr) *(u32*)(addr) = (b)
#else
# error processor byte order undefined!
#endif


/*
 * Convert a physical pointer to a virtual kernel pointer for /dev/mem access
 */
#define xlate_dev_mem_ptr(p)    __va(p)

/*
 * Convert a virtual cached pointer to an uncached pointer
 */
#define xlate_dev_kmem_ptr(p)   p

/*
 * Given a physical address and a length, return a virtual address
 * that can be used to access the memory range with the caching
 * properties specified by "flags".
 */
#if 0
Moved to types.h
typedef unsigned long phys_addr_t;
#endif

#define MAP_NOCACHE	(0)
#define MAP_WRCOMBINE	(0)
#define MAP_WRBACK	(0)
#define MAP_WRTHROUGH	(0)

/* We are using uncached addresses, ie: 0x80000000 ... */
static inline void *
map_physmem(phys_addr_t paddr, unsigned long len, unsigned long flags)
{
	return (void *)paddr;
}

/*
 * Take down a mapping set up by map_physmem().
 */
static inline void unmap_physmem(void *vaddr, unsigned long flags)
{

}

/*
 * Dummy function to keep U-Boot's cfi_flash.c driver happy.
 */
static inline void sync(void)
{
}

#endif	/* _XTENSA_IO_H */
