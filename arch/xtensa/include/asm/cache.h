/*
 * include/asm-xtensa/cache.h
 */
#ifndef _XTENSA_CACHE_H
#define _XTENSA_CACHE_H

#include <asm/arch/core.h>

extern void flush_cache_all(void);

#define ARCH_DMA_MINALIGN	XCHAL_DCACHE_LINESIZE

#endif	/* _XTENSA_CACHE_H */
