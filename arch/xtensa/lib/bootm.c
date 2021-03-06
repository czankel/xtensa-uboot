/*
 * (C) Copyright 2008 - 2013 Tensilica Inc.
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

#include <common.h>
#include <command.h>
#include <u-boot/zlib.h>
#include <asm/byteorder.h>
#include <asm/addrspace.h>
#include <asm/bootparam.h>
#include <asm/cache.h>
#include <image.h>

DECLARE_GLOBAL_DATA_PTR;

/*
 * Setup boot-parameters.
 */

static struct bp_tag *setup_first_tag(struct bp_tag *params)
{
	params->id = BP_TAG_FIRST;
	params->size = sizeof(long);
	*(unsigned long*)&params->data = BP_VERSION;

	return bp_tag_next(params);
}

static struct bp_tag *setup_last_tag(struct bp_tag *params)
{
	params->id = BP_TAG_LAST;
	params->size = 0;

	return bp_tag_next(params);
}

static struct bp_tag *setup_memory_tag(struct bp_tag *params)
{
	struct bd_info *bd = gd->bd;
	struct meminfo *mem;

	params->id = BP_TAG_MEMORY;
	params->size = sizeof(struct meminfo);
	mem = (struct meminfo *) params->data;
	mem->type = MEMORY_TYPE_CONVENTIONAL;
	mem->start = bd->bi_memstart;
	mem->end = bd->bi_memstart + bd->bi_memsize;

	printf("   MEMORY:          tag:0x%04x, type:0X%lx, start:0X%lx,"
	       " end:0X%lx\n", BP_TAG_MEMORY, mem->type, mem->start, mem->end);

	return bp_tag_next(params);
}

static struct bp_tag *setup_commandline_tag(struct bp_tag *params,char *cmdline)
{
	int len;

	if (!cmdline)
		return params;

	len = strlen(cmdline);

	params->id = BP_TAG_COMMAND_LINE;
	params->size = (len + 3) & -4;
	strcpy ((char*) params->data, cmdline);

	printf("   COMMAND_LINE:    tag:0x%04x, size:%u, data:'%s'\n", 
			BP_TAG_COMMAND_LINE, params->size, cmdline);

	return bp_tag_next(params);
}

static struct bp_tag *setup_ramdisk_tag(struct bp_tag *params,
					unsigned long rd_start,
					unsigned long rd_end)
{
	struct meminfo *mem;

	if (rd_start == rd_end)
		return params;

	/* Add a single banked memory. */

	params->id = BP_TAG_INITRD;
	params->size = sizeof(struct meminfo);

	mem = (struct meminfo *) params->data;
	mem->type =  MEMORY_TYPE_CONVENTIONAL;
	mem->start = PHYSADDR(rd_start);
	mem->end = PHYSADDR(rd_end);

	printf("   INITRD:          tag:0x%x, type:0X%04lx, start:0X%lx,"
	       " end:0X%lx\n", BP_TAG_INITRD, mem->type, mem->start, mem->end);

	return bp_tag_next(params);
}

static struct bp_tag *setup_serial_tag(struct bp_tag *params)
{
	params->id = BP_TAG_SERIAL_BAUDRATE;
	params->size = sizeof (unsigned long);
	params->data[0] = gd->baudrate;

	printf("   SERIAL_BAUDRATE: tag:0x%04x, size:%u, baudrate:%lu\n",
	       BP_TAG_SERIAL_BAUDRATE, params->size, params->data[0]);

	return bp_tag_next(params);
}

#ifdef CONFIG_OF_LIBFDT

static struct bp_tag *setup_fdt_tag(struct bp_tag *params, void *fdt_start)
{
	params->id = BP_TAG_FDT;
	params->size = sizeof (unsigned long);
	params->data[0] = (unsigned long)fdt_start;

	printf("   FDT:             tag:0x%04x, size:%u, start:0x%lx\n",
		BP_TAG_FDT, params->size, params->data[0]);

	return bp_tag_next(params);
}

#endif

/*
 * Boot Linux.
 */

int do_bootm_linux(int flag, int argc, char *argv[], bootm_headers_t *images)
{
	struct bp_tag *params, *params_start;
	image_header_t *hdr = images->legacy_hdr_os;
	ulong initrd_start, initrd_end;
	char *commandline = getenv ("bootargs");
	void (*theKernel) (struct bp_tag*);

	if ((flag != 0) && (flag != BOOTM_STATE_OS_GO)) {
		goto error;
	}
	theKernel = (void*) ntohl(hdr->ih_ep);

	if (ntohl (hdr->ih_magic) != IH_MAGIC) {
		printf("Magic Number:0x%x != IH_MAGIC:0x%x\n",
			ntohl (hdr->ih_magic), IH_MAGIC);
	}

	show_boot_progress (15);

	if (images->rd_start) {
		initrd_start = images->rd_start;
		initrd_end = images->rd_end;
	} else {
		initrd_start = 0;
		initrd_end = 0;
	}

	params = params_start = (struct bp_tag*)gd->bd->bi_boot_params;
	params = setup_first_tag(params);
	params = setup_memory_tag(params);
	params = setup_commandline_tag(params, commandline);
	params = setup_serial_tag(params);

	if (initrd_start)
		params = setup_ramdisk_tag(params, initrd_start, initrd_end);

#ifdef CONFIG_OF_LIBFDT
	if (images->ft_addr)
		params = setup_fdt_tag(params, images->ft_addr);
#endif

	printf("\n");

	params = setup_last_tag(params);

	show_boot_progress (15);

	printf("Transferring Control to Linux @0x%08lx ...\n\n",
		(ulong) theKernel);

	/*
 	 * _start() in vmlinux expects boot params in register a2.
	 * NOTE: 
	 *    Disable/delete your u-boot breakpoints before stepping into linux.
	 */
	asm volatile (
"		mov	a2, %0		\n\t"
"		mov	a3, %1		\n\t"
"		jx	%2		\n\t"
		: : "a" (params_start), "a" (params_start), "a" (theKernel)
		: "a2", "a3", "memory");

	/* Does not return */

error:
	return(1);
}

