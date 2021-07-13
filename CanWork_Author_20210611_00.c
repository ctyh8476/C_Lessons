/***********************************************************************************************//**
 * @file        Can Driver Author.c
 * @brief       FlexCan application hand code
 * @date        2020.05.13
 * @version     1.0.0
 * @author      Mr.Isly <ylguo1219@gmail.com>
 *
 * Revision History
 *------------------------------------------------------------------------------------------------
 *|Version   |Date       |Author         |Change ID      |Description                            |
 *|----------|-----------|---------------|---------------|---------------------------------------|
 *|1.0.0     |2020.05.13 |Mr.Isly        |00000000000    |Initial version created                |
 *|1.0.1     |2020.05.18 |Mr.Isly        |00000000001    |ISR Change to Author                   |
 **************************************************************************************************/

/*================================================================================================*=
 * INCLUDE FILES
 *================================================================================================*/
#include "KYMCOSoftAndFirmWareDept.h"

/*================================================================================================*=
 * LOCAL CONSTANTS
 *================================================================================================*/

/*================================================================================================*=
 * LOCAL VARIABLES
 *================================================================================================*/

/*================================================================================================*=
 * LOCAL MACROS
 *================================================================================================*/

/*================================================================================================*=
 * GLOBAL CONSTANTS
 *================================================================================================*/

/*================================================================================================*=
 * GLOBAL VARIABLES
 *================================================================================================*/

/*================================================================================================*=
 * LOCAL FUNCTIONS PROTOTYPE
 *================================================================================================*/

/*================================================================================================*=
 * LOCAL FUNCTIONS
 *================================================================================================*/

/*================================================================================================*=
 * GLOBAL FUNCTIONS
 *================================================================================================*/
/***********************************************************************************************//**
 * @brief
 *      S32K FlexCAN Initial
 **************************************************************************************************/
void CANInitial(void)
{
	UI8		i;

	/******************************************/
	/* Set CAN bus Clock Source               */
	/******************************************/
	/* Disable module before selecting clock */
	SetBit(CAN0->MCR, CAN_MCR_MDIS_SHIFT);

	/* Set CAN clock source 1 : bus, 0 : oscillator */
	SetBit(CAN0->CTRL1, CAN_CTRL1_CLKSRC_SHIFT);

	/* Enable module after selecting clock */
	ClrBit(CAN0->MCR, CAN_MCR_MDIS_SHIFT);

	/* Exit and Disable freeze mode */
	ClrBit(CAN0->MCR, CAN_MCR_FRZ_SHIFT);
	ClrBit(CAN0->MCR, CAN_MCR_HALT_SHIFT);

	/******************************************/
	/* CAN bus configuration                  */
	/******************************************/
	/* Enter and Enable freeze mode */
	SetBit(CAN0->MCR, CAN_MCR_FRZ_SHIFT);
	SetBit(CAN0->MCR, CAN_MCR_HALT_SHIFT);
	while (ValBit(CAN0->MCR, CAN_MCR_FRZACK_SHIFT));

	SetBit(CAN0->MCR, CAN_MCR_SUPV_SHIFT);
	MskBit(CAN0->MCR, CAN_MCR_MAXMB_MASK, CAN_MCR_MAXMB_SHIFT, 0x1F);
	MskBit(CAN0->MCR, CAN_MCR_AEN_MASK, CAN_MCR_AEN_SHIFT, 1);

	/* Bit-Rate configuration */
	MskBit(CAN0->CTRL1, CAN_CTRL1_PROPSEG_MASK, CAN_CTRL1_PROPSEG_SHIFT, 0x7);
	MskBit(CAN0->CTRL1, CAN_CTRL1_PSEG2_MASK, CAN_CTRL1_PSEG2_SHIFT, 0x3);
	MskBit(CAN0->CTRL1, CAN_CTRL1_PSEG1_MASK, CAN_CTRL1_PSEG1_SHIFT, 0x6);
	MskBit(CAN0->CTRL1, CAN_CTRL1_RJW_MASK, CAN_CTRL1_RJW_SHIFT, 0x1);
	MskBit(CAN0->CTRL1, CAN_CTRL1_PRESDIV_MASK, CAN_CTRL1_PRESDIV_SHIFT, 0x04);

	CAN0->RXMGMASK = 0x1FFFFFFF;
	CAN0->RX14MASK = 0x1FFFFFFF;
	CAN0->RX15MASK = 0x1FFFFFFF;

	/* Exit and Disable freeze mode */
	ClrBit(CAN0->MCR, CAN_MCR_FRZ_SHIFT);
	ClrBit(CAN0->MCR, CAN_MCR_HALT_SHIFT);
	while (!ValBit(CAN0->MCR, CAN_MCR_FRZACK_SHIFT));

	/* Check Not Ready */
	while (!ValBit(CAN0->MCR, CAN_MCR_NOTRDY_SHIFT));

	for (i = 0; i < 128; i++) {
		CAN0->RAMn[i] = 0;
	}

	/******************************************/
	/* Enable Corresponding IRQ Handler       */
	/******************************************/
	INT_SYS_EnableIRQ(CAN0_ORed_0_15_MB_IRQn);
	INT_SYS_EnableIRQ(CAN0_ORed_16_31_MB_IRQn);
}

void FlexCanTxBufSend(UI8 *data, UI8 slotnum, UI32 id, UI8 dlc, UI8 esi, UI8 rtr, UI8 module)
{
	FLEXCANR0	flexcanR0;
	FLEXCANR1	flexcanR1;
	FLEXCANR2	flexcanR2;
	FLEXCANR3	flexcanR3;
	CAN_Type 	*CANx;

	switch (module) {

		case CAN_0:
			CANx = CAN0;
			break;

		case CAN_1:
			CANx = CAN1;
			break;

		case CAN_2:
			CANx = CAN2;
			break;

		default:
			break;
	}

	flexcanR0.R0 = 0;
	flexcanR1.R1 = 0;
	flexcanR2.R2 = 0;
	flexcanR3.R3 = 0;

	/* R1 */
	flexcanR1.BYTE.ID.TYPE.EXT = 0;
	flexcanR1.BYTE.ID.TYPE.STD = id;

	/* R2 */
	flexcanR2.BYTE.DB0 = *(data + 0);
	flexcanR2.BYTE.DB1 = *(data + 1);
	flexcanR2.BYTE.DB2 = *(data + 2);
	flexcanR2.BYTE.DB3 = *(data + 3);

	/* R3 */
	flexcanR3.BYTE.DB4 = *(data + 4);
	flexcanR3.BYTE.DB5 = *(data + 5);
	flexcanR3.BYTE.DB6 = *(data + 6);
	flexcanR3.BYTE.DB7 = *(data + 7);

	/* R0 */
	flexcanR0.BYTE.ESI = esi;
	flexcanR0.BYTE.RTR = rtr;
	flexcanR0.BYTE.DLC = dlc;
	flexcanR0.BYTE.SRR = 1;
	flexcanR0.BYTE.CODE = 0xC;

	SetBit(CANx->IFLAG1, slotnum);

	CANx->RAMn[slotnum * 4 + 1] = flexcanR1.R1;
	CANx->RAMn[slotnum * 4 + 2] = flexcanR2.R2;
	CANx->RAMn[slotnum * 4 + 3] = flexcanR3.R3;
	CANx->RAMn[slotnum * 4 + 0] = flexcanR0.R0;
}

void FlexCanRxBufRead(UI8 *data, UI8 slotnum, UI32 id, UI8 dlc, UI8 esi, UI8 xtd, UI8 rtr, UI8 module)
{
	FLEXCANR0	flexcanR0;
	FLEXCANR1	flexcanR1;
	FLEXCANR2	flexcanR2;
	FLEXCANR3	flexcanR3;
	UI32		dummy;
	UI32		mb_id = 0;
	CAN_Type 	*CANx;

	switch (module) {

		case CAN_0:
			CANx = CAN0;
			break;

		case CAN_1:
			CANx = CAN1;
			break;

		case CAN_2:
			CANx = CAN2;
			break;

		default:
			break;
	}

	flexcanR0.R0 = 0;
	flexcanR1.R1 = 0;
	flexcanR2.R2 = 0;
	flexcanR3.R3 = 0;

	if (ValBit(CANx->IFLAG1, slotnum)) {
		/* clear corresponding slot Interrupt mask flag */
		SetBit(CANx->IFLAG1, slotnum);

		flexcanR0.R0 = CANx->RAMn[slotnum * 4 + 0];
		flexcanR1.R1 = CANx->RAMn[slotnum * 4 + 1];
		flexcanR2.R2 = CANx->RAMn[slotnum * 4 + 2];
		flexcanR3.R3 = CANx->RAMn[slotnum * 4 + 3];

		switch (xtd) {

			case EXTEND:
				mb_id = flexcanR1.BYTE.ID.ID;
				break;

			case STANDARD:
				mb_id = flexcanR1.BYTE.ID.TYPE.STD;
				break;

			default:
				break;
		}

		if ((id == mb_id) && (dlc == flexcanR0.BYTE.DLC) && (esi == flexcanR0.BYTE.ESI) && (rtr == flexcanR0.BYTE.RTR)) {
			/* R2 read */
			*(data + 0) = flexcanR2.BYTE.DB0;
			*(data + 1) = flexcanR2.BYTE.DB1;
			*(data + 2) = flexcanR2.BYTE.DB2;
			*(data + 3) = flexcanR2.BYTE.DB3;

			/* R3 read */
			*(data + 4) = flexcanR3.BYTE.DB4;
			*(data + 5) = flexcanR3.BYTE.DB5;
			*(data + 6) = flexcanR3.BYTE.DB6;
			*(data + 7) = flexcanR3.BYTE.DB7;
		}

		/* Read TIMER to unlock message buffers */
		dummy = CANx->TIMER;
	}
}

/*================================================================================================*=
 *  END OF FILE
 *================================================================================================*/
