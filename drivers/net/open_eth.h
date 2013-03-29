/*
 * Ethernet driver header for Open Ethernet Controller (www.opencores.org).
 * Adapted from Linux kernel driver by Tensilica.
 *      Copyright (c) 2006-2008 Tensilica Inc.
 *      Copyright (c) 2002 Simon Srot (simons@opencores.org)
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

typedef unsigned int uint32;

typedef struct _oeth_regs {
  uint32    moder;          /* Mode Register */
  uint32    int_src;        /* Interrupt Source Register */
  uint32    int_mask;       /* Interrupt Mask Register */
  uint32    ipgt;           /* Back to Bak Inter Packet Gap Register */
  uint32    ipgr1;          /* Non Back to Back Inter Packet Gap Register */
  uint32    ipgr2;          /* Non Back to Back Inter Packet Gap Register */
  uint32    packet_len;     /* Packet Length Register (min. and max.) */
  uint32    collconf;       /* Collision and Retry Configuration Register */
  uint32    tx_bd_num;      /* Transmit Buffer Descriptor Number Register */
  uint32    ctrlmoder;      /* Control Module Mode Register */
  uint32    miimoder;       /* MII Mode Register */
  uint32    miicommand;     /* MII Command Register */
  uint32    miiaddress;     /* MII Address Register */
  uint32    miitx_data;     /* MII Transmit Data Register */
  uint32    miirx_data;     /* MII Receive Data Register */
  uint32    miistatus;      /* MII Status Register */
  uint32    mac_addr0;      /* MAC Individual Address Register 0 */
  uint32    mac_addr1;      /* MAC Individual Address Register 1 */
  uint32    hash_addr0;     /* Hash Register 0 */
  uint32    hash_addr1;     /* Hash Register 1 */
} oeth_regs;

typedef struct _oeth_bd {
  uint32 len_status;
  uint32 addr;
} oeth_bd;

/* Tx BD */
#define OETH_TX_BD_READY        0x8000 /* Tx BD Ready */
#define OETH_TX_BD_IRQ          0x4000 /* Tx BD IRQ Enable */
#define OETH_TX_BD_WRAP         0x2000 /* Tx BD Wrap (last BD) */
#define OETH_TX_BD_PAD          0x1000 /* Tx BD Pad Enable */
#define OETH_TX_BD_CRC          0x0800 /* Tx BD CRC Enable */

#define OETH_TX_BD_UNDERRUN     0x0100 /* Tx BD Underrun Status */
#define OETH_TX_BD_RETRY        0x00F0 /* Tx BD Retry Status */
#define OETH_TX_BD_RETLIM       0x0008 /* Tx BD Retransmission Limit Status */
#define OETH_TX_BD_LATECOL      0x0004 /* Tx BD Late Collision Status */
#define OETH_TX_BD_DEFER        0x0002 /* Tx BD Defer Status */
#define OETH_TX_BD_CARRIER      0x0001 /* Tx BD Carrier Sense Lost Status */

#define OETH_TX_BD_STATS        (OETH_TX_BD_UNDERRUN            | \
                                OETH_TX_BD_RETRY                | \
                                OETH_TX_BD_RETLIM               | \
                                OETH_TX_BD_LATECOL              | \
                                OETH_TX_BD_DEFER                | \
                                OETH_TX_BD_CARRIER)
                                
/* Rx BD */                     
#define OETH_RX_BD_EMPTY        0x8000 /* Rx BD Empty */
#define OETH_RX_BD_IRQ          0x4000 /* Rx BD IRQ Enable */
#define OETH_RX_BD_WRAP         0x2000 /* Rx BD Wrap (last BD) */
                                
#define OETH_RX_BD_MISS         0x0080 /* Rx BD Miss Status */
#define OETH_RX_BD_OVERRUN      0x0040 /* Rx BD Overrun Status */
#define OETH_RX_BD_INVSIMB      0x0020 /* Rx BD Invalid Symbol Status */
#define OETH_RX_BD_DRIBBLE      0x0010 /* Rx BD Dribble Nibble Status */
#define OETH_RX_BD_TOOLONG      0x0008 /* Rx BD Too Long Status */
#define OETH_RX_BD_SHORT        0x0004 /* Rx BD Too Short Frame Status */
#define OETH_RX_BD_CRCERR       0x0002 /* Rx BD CRC Error Status */
#define OETH_RX_BD_LATECOL      0x0001 /* Rx BD Late Collision Status */
#define OETH_RX_BD_STATS        (OETH_RX_BD_MISS                | \
                                OETH_RX_BD_OVERRUN              | \
                                OETH_RX_BD_INVSIMB              | \
                                OETH_RX_BD_DRIBBLE              | \
                                OETH_RX_BD_TOOLONG              | \
                                OETH_RX_BD_SHORT                | \
                                OETH_RX_BD_CRCERR               | \
                                OETH_RX_BD_LATECOL)

/* MODER Register */
#define OETH_MODER_RXEN         0x00000001 /* Receive Enable  */
#define OETH_MODER_TXEN         0x00000002 /* Transmit Enable */
#define OETH_MODER_NOPRE        0x00000004 /* No Preamble  */
#define OETH_MODER_BRO          0x00000008 /* Reject Broadcast */
#define OETH_MODER_IAM          0x00000010 /* Use Individual Hash */
#define OETH_MODER_PRO          0x00000020 /* Promiscuous (receive all) */
#define OETH_MODER_IFG          0x00000040 /* Min. IFG not required */
#define OETH_MODER_LOOPBCK      0x00000080 /* Loop Back */
#define OETH_MODER_NOBCKOF      0x00000100 /* No Backoff */
#define OETH_MODER_EXDFREN      0x00000200 /* Excess Defer */
#define OETH_MODER_FULLD        0x00000400 /* Full Duplex */
#define OETH_MODER_RST          0x00000800 /* Reset MAC */
#define OETH_MODER_DLYCRCEN     0x00001000 /* Delayed CRC Enable */
#define OETH_MODER_CRCEN        0x00002000 /* CRC Enable */
#define OETH_MODER_HUGEN        0x00004000 /* Huge Enable */
#define OETH_MODER_PAD          0x00008000 /* Pad Enable */
#define OETH_MODER_RECSMALL     0x00010000 /* Receive Small */

/* Control Module Mode Register */
#define OETH_CTRLMODER_PASSALL  0x00000001 /* Pass Control Frames */
#define OETH_CTRLMODER_RXFLOW   0x00000002 /* Receive Control Flow Enable */
#define OETH_CTRLMODER_TXFLOW   0x00000004 /* Transmit Control Flow Enable */
                               
/* MII Mode Register */        
#define OETH_MIIMODER_CLKDIV    0x000000FF /* Clock Divider */
#define OETH_MIIMODER_NOPRE     0x00000100 /* No Preamble */
#define OETH_MIIMODER_RST       0x00000200 /* MIIM Reset */
 
/* MII Command Register */
#define OETH_MIICOMMAND_SCANSTAT  0x00000001 /* Scan Status */
#define OETH_MIICOMMAND_RSTAT     0x00000002 /* Read Status */
#define OETH_MIICOMMAND_WCTRLDATA 0x00000004 /* Write Control Data */
 
/* MII Address Register */
#define OETH_MIIADDRESS_FIAD    0x0000001F /* PHY Address */
#define OETH_MIIADDRESS_RGAD    0x00001F00 /* RGAD Address */
 
/* MII Status Register */
#define OETH_MIISTATUS_LINKFAIL 0x00000001 /* Link Fail */
#define OETH_MIISTATUS_BUSY     0x00000002 /* MII Busy */
#define OETH_MIISTATUS_NVALID   0x00000004 /* Data in MII Status Register is invalid */

#define MII_BMCR                 0x00
#define MII_BMSR                 0x01
#define MII_TPISTATUS            0x1b

#define BMCR_RESET               0x8000

/* Buffer number (must be 2^n)  */
#define OETH_RXBD_NUM		16
#define OETH_TXBD_NUM		16
#define OETH_RXBD_NUM_MASK	(OETH_RXBD_NUM-1)
#define OETH_TXBD_NUM_MASK	(OETH_TXBD_NUM-1)

/* Buffer size */
#define OETH_MAX_FRAME_SIZE	((1518 + 7) & ~7)
#define OETH_RX_BUFF_SIZE	OETH_MAX_FRAME_SIZE
#define OETH_TX_BUFF_SIZE	OETH_MAX_FRAME_SIZE

#define ETH_ZLEN	60	/* FIXME - shall be defined in a generic ethernet header */
