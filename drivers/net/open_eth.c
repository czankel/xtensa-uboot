/*
 * Ethernet driver for Open Ethernet Controller (www.opencores.org).
 * Adapted from Linux kernel driver by Tensilica.
 *      Copyright (c) 2006-2008 Tensilica Inc.
 *      Copyright (c) 2002 Simon Srot (simons@opencores.org)
 * 
 * Based on:
 *
 * Ethernet driver for Motorola MPC8xx.
 *      Copyright (c) 1997 Dan Malek (dmalek@jlc.net)
 *
 * mcen302.c: A Linux network driver for Mototrola 68EN302 MCU
 *
 *      Copyright (C) 1999 Aplio S.A. Written by Vadim Lebedev
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
 *  The Open Ethernet Controller is just a MAC, it needs to be
 *  combined with a PHY and buffer memory in order to create an
 *  ethernet device. Thus some of the hardware parameters are device
 *  specific. They need to be defined in asm/hardware.h. Example:
 * 
 * The IRQ for the device:
 * #define OETH_IRQ                1
 *
 * The flag to be passed to request_irq:
 * #define OETH_REQUEST_IRQ_FLAG   0
 * 
 * The address where the MAC registers are mapped:
 * #define OETH_BASE_ADDR          0xFD030000
 *
 * The address where the MAC RX/TX buffers are mapped:
 * #define OETH_SRAM_BUFF_BASE     0xFD800000
 * 
 * Sizes for a RX or TX buffer:
 * #define OETH_RX_BUFF_SIZE       2048
 * #define OETH_TX_BUFF_SIZE       2048
 * The number of RX and TX buffers:
 * #define OETH_RXBD_NUM           16
 * #define OETH_TXBD_NUM           16
 * The PHY ID (needed if MII is enabled):
 * #define OETH_PHY_ID             0
 * 
 * Code to perform the device specific initialization (REGS is a
 *  struct oeth_regs*):
 * #define OETH_PLATFORM_SPECIFIC_INIT(REGS)
 * it should at least initialize the device MAC address in
 *  REGS->mac_addr1 and REGS->mac_addr2.
 */

#include <common.h>
#include <command.h>
#include <net.h>

#include <config.h>
#include "open_eth.h"

#define HAL_READ_UINT32(a, v) (v = *a)
#define HAL_WRITE_UINT32(a, v) (*a = v)

#define OETH_REGLOAD(a, v) HAL_READ_UINT32(&(a), v)
#define OETH_REGSAVE(a, v) HAL_WRITE_UINT32(&(a), v)
#define OETH_REGORIN(a, v)	\
  do { uint32 va;	\
    OETH_REGLOAD(a, va);	\
    va |= v;	\
    OETH_REGSAVE(a, va);	\
  } while(0)
#define OETH_REGANDIN(a, v)	\
  do { uint32 va;	\
    OETH_REGLOAD(a, va);	\
    va &= v;	\
    OETH_REGSAVE(a, va);	\
  } while(0)

#define OETH_TXBUFF_ADDR CONFIG_SYS_OETH_BUFF_ADDR
#define OETH_RXBUFF_ADDR (CONFIG_SYS_OETH_BUFF_ADDR + (OETH_TXBD_NUM*OETH_TX_BUFF_SIZE))

#define debug_print 

static volatile oeth_bd * tx_bd;
static volatile oeth_bd * rx_bd;
static int tx_next, rx_next;

#if 0
static int mdio_read(volatile oeth_regs * regs, int phy, int loc)
{
  int i;
  int regs_value = -1;
  volatile int v;
  regs->miiaddress =
    (phy & OETH_MIIADDRESS_FIAD) |
    ((loc << 8) & OETH_MIIADDRESS_RGAD);
  regs->miicommand = OETH_MIICOMMAND_RSTAT;

  for (i = 1000; i >=0; i--) {
    v = regs->miistatus;
    if ((v & OETH_MIISTATUS_BUSY) == 0) {
      regs_value = regs->miirx_data;
      regs->miicommand = 0;
      break;
    }
  }
  return regs_value;
}
#endif

static void mdio_write(volatile oeth_regs * regs, int phy, int loc, int val)
{
  int i;
  volatile int v;
  regs->miiaddress =
    (phy & OETH_MIIADDRESS_FIAD) |
    ((loc << 8) & OETH_MIIADDRESS_RGAD);
  regs->miitx_data = val;
  regs->miicommand = OETH_MIICOMMAND_WCTRLDATA;

  for (i = 100; i >= 0; i--) {
    v = regs->miistatus;
    if ((v & OETH_MIISTATUS_BUSY) == 0) {
      break;
    }
  }
  return;
}

static int oeth_init(struct eth_device *dev, bd_t *bd)
{
  int i;
  unsigned long rxmem_addr = OETH_RXBUFF_ADDR;
  unsigned long txmem_addr = OETH_TXBUFF_ADDR;
  volatile oeth_regs * regs = (oeth_regs *) CONFIG_SYS_OETH_REG_BASE;

  // Pass mac address from MACADDRx defines back to bd's array TBD


  // reset the controller
  OETH_REGSAVE(regs->moder, OETH_MODER_RST);
  OETH_REGANDIN(regs->moder, ~OETH_MODER_RST);

  // Set TXBD and RXBD base (TBD: also store in a private structure)
  OETH_REGSAVE(regs->tx_bd_num, OETH_TXBD_NUM);
  tx_bd = (volatile oeth_bd *) CONFIG_SYS_OETH_BD_BASE;
  rx_bd = (volatile oeth_bd *) CONFIG_SYS_OETH_BD_BASE + OETH_TXBD_NUM;

  // Initialize transmit pointers TBD

  // Initialize something else (what's behind the magic?)
  OETH_REGSAVE(regs->packet_len, 0x00400600);
  OETH_REGSAVE(regs->ipgt, 0x00000015);
  OETH_REGSAVE(regs->ipgr1, 0x0000000c);
  OETH_REGSAVE(regs->ipgr2, 0x00000012);
  OETH_REGSAVE(regs->collconf, 0x000f003f);
  OETH_REGSAVE(regs->ctrlmoder, 0);

  do {
    int phy = 0;
    regs->miimoder = (OETH_MIIMODER_CLKDIV & 0x02);
    mdio_write(regs, phy, MII_BMCR, BMCR_RESET);
    mdio_write(regs, 0, MII_TPISTATUS, 0xce);
  } while (0);

  /*
  // 10 mbit
  OETH_REGSAVE(regs->miiaddress, 0);
  OETH_REGSAVE(regs->miitx_data, 0);
  OETH_REGSAVE(regs->miicommand, OETH_MIICOMMAND_WCTRLDATA);

  // Tx, Rx and Link status
  OETH_REGSAVE(regs->miiaddress, 20 << 8);
  OETH_REGSAVE(regs->miitx_data, 0x1422);
  OETH_REGSAVE(regs->miicommand, OETH_MIICOMMAND_WCTRLDATA);
  */

  // Initialize TXBDs
  for (i = 0; i < OETH_TXBD_NUM; i++) {
    OETH_REGSAVE(tx_bd[i].len_status, OETH_TX_BD_PAD | OETH_TX_BD_CRC);
    OETH_REGSAVE(tx_bd[i].addr, txmem_addr);
    txmem_addr += OETH_TX_BUFF_SIZE;
  }
  OETH_REGORIN(tx_bd[OETH_TXBD_NUM - 1].len_status, OETH_TX_BD_WRAP);
  tx_next = 0;

  // Initialize RXBDs
  for (i = 0; i < OETH_RXBD_NUM; i++) {
    OETH_REGSAVE(rx_bd[i].len_status, OETH_RX_BD_EMPTY);
    OETH_REGSAVE(rx_bd[i].addr, rxmem_addr);
    rxmem_addr += OETH_RX_BUFF_SIZE;
  }
  OETH_REGORIN(rx_bd[OETH_TXBD_NUM - 1].len_status, OETH_RX_BD_WRAP);
  rx_next = 0;

  // Initialize MAC address
  OETH_REGSAVE(regs->mac_addr1, bd->bi_enetaddr[0] << 8 | bd->bi_enetaddr[1]);
  OETH_REGSAVE(regs->mac_addr0,
	       bd->bi_enetaddr[2] << 24 | bd->bi_enetaddr[3] << 16 | 
	       bd->bi_enetaddr[4] << 8 | bd->bi_enetaddr[5]);

  // Clear all pending interrupts - just in case
  OETH_REGSAVE(regs->int_src, 0xffffffff);

  // Promisc, IFG, CRCEn
  OETH_REGORIN(regs->moder, OETH_MODER_PAD | OETH_MODER_IFG | OETH_MODER_CRCEN);

  // Do NOT enable interrupts
  // Anything else?

  OETH_REGORIN(regs->moder, OETH_MODER_RXEN | OETH_MODER_TXEN);

  // debug_print("OETH Core version 1.0\n");
  return 0;
}

void oeth_halt(struct eth_device *dev)
{
}


static int oeth_rcv_packet(struct eth_device *dev)
{
  volatile oeth_bd * bdp = rx_bd + rx_next;
  u32 len_status = bdp->len_status;
  void * rxbuf = (void *) NetRxPackets[0];
  int packet_size;
  int bad = 0;

  if (len_status & OETH_RX_BD_EMPTY)
    return 0;

  if (len_status & (OETH_RX_BD_TOOLONG | OETH_RX_BD_SHORT)) {
    bad = 1;
  } else if (len_status & OETH_RX_BD_DRIBBLE) {
    bad = 1;
  } else if (len_status & OETH_RX_BD_CRCERR) {
    bad = 1;
  } else if (len_status & OETH_RX_BD_OVERRUN) {
    bad = 1;
  } else if (len_status & OETH_RX_BD_TOOLONG) {
    bad = 1;
  } else if (len_status & OETH_RX_BD_MISS) {
    // Linux driver doesn't set 'bad' here
  } else if (len_status & OETH_RX_BD_LATECOL) {
    bad = 1;
  }

  if (bad) {
    bdp->len_status = (len_status & ~OETH_RX_BD_STATS) | OETH_RX_BD_EMPTY;
    return 0;
  }
  packet_size = len_status >> 16;
  memcpy(rxbuf, (void *) bdp->addr, packet_size);
  bdp->len_status = (len_status & ~OETH_RX_BD_STATS) | OETH_RX_BD_EMPTY;
  rx_next = (rx_next == (OETH_RXBD_NUM - 1))? 0: rx_next + 1;
  NetReceive(NetRxPackets[0], packet_size);

  return packet_size;
}

static int oeth_send_packet(struct eth_device *dev, volatile void * packet, int length)
{
  int sent = 0;

  while (length > 0) {
    volatile oeth_bd * bdp = tx_bd + tx_next;
    int gulp = (length > OETH_TX_BUFF_SIZE)? OETH_TX_BUFF_SIZE: length;
    u32 len_status = bdp->len_status;

    if (len_status & OETH_TX_BD_READY) {
      // The buffer is still transmitting. Bail out. Or wait for a while?
      return sent;
    }

    len_status &= ~OETH_TX_BD_STATS;
    if (gulp < ETH_ZLEN)
      len_status |= OETH_TX_BD_PAD;
    else
      len_status &= ~OETH_TX_BD_PAD;

    // Fill up the buffer and send it out
    memcpy((void *) bdp->addr, (const void *) packet, gulp);
    len_status = (len_status & 0x0000ffff) | length << 16;
    len_status |= (OETH_TX_BD_READY | OETH_TX_BD_CRC);
    bdp->len_status = len_status;

    /* Unclear - shall we wait for completion here? If the controller
       proceed for the next buffer automatically, we should not */

    // Prepare for the next buffer
    length -= gulp;
    packet += gulp;
    sent += gulp;
    tx_next = (tx_next == (OETH_TXBD_NUM - 1))? 0: tx_next + 1;
  }

  return sent;
}

struct eth_device oeth_device;

int oeth_initialize(bd_t *bis)

{
	struct eth_device *dev = &oeth_device;

	memset(dev, 0, sizeof *dev);

	/* Copy MAC address from bis to dev */
	memcpy(dev->enetaddr, bis->bi_enetaddr, 6);

	dev->iobase = 0;
	dev->init = oeth_init;
	dev->halt = oeth_halt;
	dev->send = oeth_send_packet;
	dev->recv = oeth_rcv_packet;

	sprintf(dev->name, "open_ethernet");

	eth_register(dev);
	return(1);
}
