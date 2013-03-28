/*
 * (C) Copyright 2008, Tensilica Inc.
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

#include <common.h>
#include <asm/global_data.h>
#include <linux/stringify.h>

DECLARE_GLOBAL_DATA_PTR;

#if XCHAL_HAVE_CCOUNT
static ulong get_ccount(void)
{
	ulong ccount;
	asm volatile ("rsr %0,"__stringify(CCOUNT) : "=a" (ccount));
	return ccount;
}
#else
static ulong fake_ccount = 0;
#define get_ccount() fake_ccount
#endif

static void delay_cycles(unsigned cycles)
{
#if XCHAL_HAVE_CCOUNT
    unsigned expiry = get_ccount() + cycles;
    while ((signed)(expiry - get_ccount()) > 0);
#else
#warning "Without Xtensa timer option, timing will not be accurate."

    /*
    Approximate the cycle count by a loop iteration count. 
    This is highly dependent on config and optimization.
    */

    volatile unsigned i;
    for (i = cycles >> 4U; i > 0; --i);
    fake_ccount += cycles;
#endif
}

#if 0
/*
 * Delay (busy-wait) for a number of microseconds.
 */

void udelay(unsigned long usec)
{
	ulong lo, hi, i;
        ulong mhz = CONFIG_SYS_CLK_FREQ / 1000000;

	/* Scale to support full 32-bit usec range */

	lo = usec & ((1<<22)-1);
	hi = usec >> 22UL;
	for (i=0; i<hi; ++i)
		delay_cycles(mhz << 22);
	delay_cycles(mhz * lo);
}
#endif


/*
 * Return the elapsed time (ticks) since 'base'.
 */

ulong get_timer(ulong base)
{
	/* Don't tie up a timer; use cycle counter if available (or fake it). */

#if XCHAL_HAVE_CCOUNT
	register ulong ccount;
	__asm__ volatile ("rsr %0, CCOUNT" : "=a"(ccount));
	return ccount / (CONFIG_SYS_CLK_FREQ / CONFIG_SYS_HZ) - base;
#else
	/*
	 * Add at least the overhead of this call (in cycles).
	 * Avoids hanging in case caller doesn't use udelay().
         * Note that functions that don't call udelay() (such as
         * the "sleep" command) will not get a significant delay 
         * because there is no time reference.
	 */

	fake_ccount += 20;
	return fake_ccount / (CONFIG_SYS_CLK_FREQ / CONFIG_SYS_HZ) - base;
#endif
}


/*
 * This function is derived from ARM/PowerPC code (read timebase as long long).
 * On Xtensa it just returns the timer value.
 */
unsigned long long get_ticks(void)
{
	return get_timer(0);
}

/*
 * This function is derived from ARM/PowerPC code (timebase clock frequency).
 * On Xtensa it returns the number of timer ticks per second.
 */
ulong get_tbclk (void)
{
	ulong tbclk;

	tbclk = CONFIG_SYS_HZ;
	return tbclk;
}

