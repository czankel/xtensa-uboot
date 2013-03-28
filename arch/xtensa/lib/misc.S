/*
 * (C) Copyright 2008 Tensilica Inc.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <asm/asmmacro.h>
#include <asm/arch/core.h>

/*
 * Make sure all data cache lines in a region have been written to memory,
 * and that instruction cache has been invalidated.
 */

	.global flush_cache
	.align	4
flush_cache:
	entry	a1, 16

	mov	a4, a2
	__loops	a4, a3, a5, XCHAL_DCACHE_LINEWIDTH
	dhwbi	a4, 0
	__endla	a4, a5, (1 << XCHAL_DCACHE_LINEWIDTH)

	__loops	a2, a3, a5, XCHAL_ICACHE_LINEWIDTH
	ihi	a2, 0
	__endla	a2, a5, (1 << XCHAL_ICACHE_LINEWIDTH)

	retw

	.global flush_cache_all
	.align 4
flush_cache_all:
	entry	a1, 16

	movi	a2, 0
	__loopi	a2, a3, XCHAL_DCACHE_SIZE, 4 << XCHAL_DCACHE_LINEWIDTH
	diwbi	a2, 0 << XCHAL_DCACHE_LINEWIDTH
	diwbi	a2, 1 << XCHAL_DCACHE_LINEWIDTH
	diwbi 	a2, 2 << XCHAL_DCACHE_LINEWIDTH
	diwbi	a2, 3 << XCHAL_DCACHE_LINEWIDTH
	__endla a2, a3, 4 << XCHAL_DCACHE_LINEWIDTH

	movi	a2, 0
	__loopi	a2, a3, XCHAL_ICACHE_SIZE, 4 << XCHAL_ICACHE_LINEWIDTH
	iii	a2, 0 << XCHAL_ICACHE_LINEWIDTH
	iii	a2, 1 << XCHAL_ICACHE_LINEWIDTH
	iii 	a2, 2 << XCHAL_ICACHE_LINEWIDTH
	iii	a2, 3 << XCHAL_ICACHE_LINEWIDTH
	__endla a2, a3, 4 << XCHAL_ICACHE_LINEWIDTH

	retw


