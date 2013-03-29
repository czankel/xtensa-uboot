#ifndef _ASM_XTENSA_UNALIGNED_H
#define _ASM_XTENSA_UNALIGNED_H

#include <linux/unaligned/le_byteshift.h>
#include <linux/unaligned/be_byteshift.h>
#include <linux/unaligned/generic.h>

/*
 * Select endianness
 */
#ifndef __XTENSA_EB__
#define get_unaligned	__get_unaligned_le
#define put_unaligned	__put_unaligned_le
#elif __XTENSA_EL__
#define get_unaligned	__get_unaligned_be
#define put_unaligned	__put_unaligned_be
#else
#error Cannot determine endianess
#endif

#endif /* _ASM_XTENSA_UNALIGNED_H */
