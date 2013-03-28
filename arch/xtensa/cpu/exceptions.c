/*
 * (C) Copyright 2008 Tensilica Inc.
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
 * Exception handling.
 *  We currently don't handle any exception and force a reset.
 *  (Note that alloca is a special case and handled in start.S)
 */

#include <common.h>
#include <command.h>
#include <asm/xtensa.h>
#include <asm/string.h>
#include <asm/regs.h>

extern void xtensa_mem_exc_dummy(struct pt_regs*);

void unhandled_exception(struct pt_regs*);

typedef void (*handler_t)(struct pt_regs*);

#define E(cause) EXCCAUSE_ ## cause

handler_t exc_table[EXCCAUSE_LAST] = { 
	unhandled_exception,	/* EXCCAUSE_ILLEGAL_INSTRUCTION */
	unhandled_exception,    /* EXCCAUSE_SYSTEM_CALL */
	unhandled_exception,    /* EXCCAUSE_INSTRUCTION_FETCH_ERROR */
	xtensa_mem_exc_dummy,   /* EXCCAUSE_LOAD_STORE_ERROR */
	unhandled_exception,    /* EXCCAUSE_LEVEL1_INTERRUPT */
	unhandled_exception,    /* EXCCAUSE_ALLOCA */
	unhandled_exception,    /* EXCCAUSE_INTEGER_DIVIDE_BY_ZERO */
	unhandled_exception,    /* EXCCAUSE_SPECULATION */
	unhandled_exception,    /* EXCCAUSE_PRIVILEGED */
	xtensa_mem_exc_dummy,   /* EXCCAUSE_UNALIGNED */
	unhandled_exception,    /* EXCCAUSE_INSTR_DATA_ERROR */
	xtensa_mem_exc_dummy,   /* EXCCAUSE_LOAD_STORE_DATA_ERROR */
	unhandled_exception,    /* EXCCAUSE_INSTR_ADDR_ERROR */
	xtensa_mem_exc_dummy,   /* EXCCAUSE_LOAD_STORE_ADDR_ERROR */
	unhandled_exception,    /* EXCCAUSE_ITLB_MISS */
	unhandled_exception,    /* EXCCAUSE_ITLB_MULTIHIT */
	unhandled_exception,    /* EXCCAUSE_ITLB_PRIVILEGE */
	unhandled_exception,    /* EXCCAUSE_ITLB_SIZE_RESTRICTION */
	xtensa_mem_exc_dummy,   /* EXCCAUSE_FETCH_CACHE_ATTRIBUTE */
	xtensa_mem_exc_dummy,   /* EXCCAUSE_DTLB_MISS */
	xtensa_mem_exc_dummy,   /* EXCCAUSE_DTLB_MULTIHIT */
	xtensa_mem_exc_dummy,   /* EXCCAUSE_DTLB_PRIVILEGE */
	xtensa_mem_exc_dummy,   /* EXCCAUSE_DTLB_SIZE_RESTRICTION */
	xtensa_mem_exc_dummy,   /* EXCCAUSE_LOAD_CACHE_ATTRIBUTE */
	xtensa_mem_exc_dummy,   /* EXCCAUSE_STORE_CACHE_ATTRIBUTE */
	[EXCCAUSE_STORE_CACHE_ATTRIBUTE+1 ... EXCCAUSE_LAST-1]
	    unhandled_exception 
};

void unhandled_exception(struct pt_regs *regs)
{
#ifdef CONFIG_SYS_ASCDISP
	display_printf("!! EXCCAUSE = %2ld", regs->exccause);
#endif
	printf("Unhandled Exception: EXCCAUSE = %ld\n", regs->exccause);
	udelay(10000000);	/* 10s to read display message */
	panic("*** PANIC\n");
}

#ifdef CONFIG_USE_IRQ
#error "Use of interrupts is not supported in Avnet/Xtensa ports"
#else
void enable_interrupts (void)
{
	return;
}
int disable_interrupts (void)
{
	return 0;
}
#endif

