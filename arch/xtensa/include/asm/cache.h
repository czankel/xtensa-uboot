/*
 * include/asm-xtensa/cache.h
 */
#ifndef _XTENSA_CACHE_H
#define _XTENSA_CACHE_H

#include <asm/arch/core.h>

//extern void flush_cache_all(void);
//extern void flush_dcache_range(unsigned long start, unsigned long stop);

#define ARCH_DMA_MINALIGN	XCHAL_DCACHE_LINESIZE

#endif	/* _XTENSA_CACHE_H */
