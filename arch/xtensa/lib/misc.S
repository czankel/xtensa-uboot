/*
 * arch/xtensa/mm/misc.S
 *
 * Miscellaneous assembly functions.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2001 - 2007 Tensilica Inc.
 *
 * Chris Zankel	<chris@zankel.net>
 */


#include <linux/linkage.h>
#include <asm/asmmacro.h>
#include <asm/cacheasm.h>

/*
 * void __invalidate_icache_page(ulong start)
 */

ENTRY(__invalidate_icache_page)

	entry	sp, 16

	___invalidate_icache_page a2 a3
	isync

	retw

ENDPROC(__invalidate_icache_page)

/*
 * void __invalidate_dcache_page(ulong start)
 */

ENTRY(__invalidate_dcache_page)

	entry	sp, 16

	___invalidate_dcache_page a2 a3
	dsync

	retw

ENDPROC(__invalidate_dcache_page)

/*
 * void __flush_invalidate_dcache_page(ulong start)
 */

ENTRY(__flush_invalidate_dcache_page)

	entry	sp, 16

	___flush_invalidate_dcache_page a2 a3

	dsync
	retw

ENDPROC(__flush_invalidate_dcache_page)

/*
 * void __flush_dcache_page(ulong start)
 */

ENTRY(__flush_dcache_page)

	entry	sp, 16

	___flush_dcache_page a2 a3

	dsync
	retw

ENDPROC(__flush_dcache_page)

/*
 * void __invalidate_icache_range(ulong start, ulong size)
 */

ENTRY(__invalidate_icache_range)

	entry	sp, 16

	___invalidate_icache_range a2 a3 a4
	isync

	retw

ENDPROC(__invalidate_icache_range)

/*
 * void __flush_invalidate_dcache_range(ulong start, ulong size)
 */

ENTRY(__flush_invalidate_dcache_range)

	entry	sp, 16

	___flush_invalidate_dcache_range a2 a3 a4
	dsync

	retw

ENDPROC(__flush_invalidate_dcache_range)

/*
 * void _flush_dcache_range(ulong start, ulong size)
 */

ENTRY(__flush_dcache_range)

	entry	sp, 16

	___flush_dcache_range a2 a3 a4
	dsync

	retw

ENDPROC(__flush_dcache_range)

/*
 * void _invalidate_dcache_range(ulong start, ulong size)
 */

ENTRY(__invalidate_dcache_range)

	entry	sp, 16

	___invalidate_dcache_range a2 a3 a4

	retw

ENDPROC(__invalidate_dcache_range)

/*
 * void _invalidate_icache_all(void)
 */

ENTRY(__invalidate_icache_all)

	entry	sp, 16

	___invalidate_icache_all a2 a3
	isync

	retw

ENDPROC(__invalidate_icache_all)

/*
 * void _flush_invalidate_dcache_all(void)
 */

ENTRY(__flush_invalidate_dcache_all)

	entry	sp, 16

	___flush_invalidate_dcache_all a2 a3
	dsync

	retw

ENDPROC(__flush_invalidate_dcache_all)

/*
 * void _invalidate_dcache_all(void)
 */

ENTRY(__invalidate_dcache_all)

	entry	sp, 16

	___invalidate_dcache_all a2 a3
	dsync

	retw

ENDPROC(__invalidate_dcache_all)
