/***********************************************************************************************//**
 * @file        Can Driver User.c
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
 *|1.0.0     |2020.05.18 |Mr.Isly        |00000000001    |ISR Change to Author                   |
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
STATIC_FUNC flexcan_data_info_t	canDataInfo;
STATIC_FUNC flexcan_msgbuff_t	rxDataBuff;
STATIC_FUNC	TARGETBOARD			TargetBoard;
STATIC_FUNC	FLA2000ST			Fla2000St;
STATIC_FUNC	UI8					CANRX_1[8];
STATIC_FUNC	UI8					CANRX_2[8];
STATIC_FUNC	UI8					CANRX_3[8];
STATIC_FUNC	UI8					ctxchk_1;
STATIC_FUNC	UI8					ctxchk_2;
STATIC_FUNC	UI8					ctxchk_3;

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
STATIC_FUNC void CanConfig(void);

/*================================================================================================*=
 * LOCAL FUNCTIONS
 *================================================================================================*/
/***********************************************************************************************//**
 * @brief
 *      CAN Driver configuration
 *      1. Set callback function prototype
 *      2. Slot information(STD/ETD, Remote frame/data frame, FD, data length...)
 *      3. RX Slot configuration(Slot number, ID)
 *      4. TX Slot configuration(Slot number, ID)
 **************************************************************************************************/
STATIC_FUNC void CanConfig(void)
{
	FLEXCANR0	flexcanR0;
	FLEXCANR1	flexcanR1;
	FLEXCANR2	flexcanR2;
	FLEXCANR3	flexcanR3;

	flexcanR0.R0 = 0;
	flexcanR1.R1 = 0;
	flexcanR2.R2 = 0;
	flexcanR3.R3 = 0;

	/* RX Slot configuration */
	flexcanR0.BYTE.IDE = 1;
	flexcanR0.BYTE.DLC = 8;
	flexcanR0.BYTE.CODE = 0x4;
	flexcanR1.BYTE.ID.ID = 0x500;
	CAN0->RAMn[4 * FLEXCAN_0_RX_500_SLOT + 0] = flexcanR0.R0;
	CAN0->RAMn[4 * FLEXCAN_0_RX_500_SLOT + 1] = flexcanR1.R1;
	SetBit(CAN0->IMASK1, FLEXCAN_0_RX_500_SLOT);

	flexcanR0.BYTE.IDE = 1;
	flexcanR0.BYTE.DLC = 8;
	flexcanR0.BYTE.CODE = 0x4;
	flexcanR1.BYTE.ID.ID = 0x501;
	CAN0->RAMn[4 * FLEXCAN_0_RX_501_SLOT + 0] = flexcanR0.R0;
	CAN0->RAMn[4 * FLEXCAN_0_RX_501_SLOT + 1] = flexcanR1.R1;
	SetBit(CAN0->IMASK1, FLEXCAN_0_RX_501_SLOT);

	flexcanR0.BYTE.IDE = 1;
	flexcanR0.BYTE.DLC = 8;
	flexcanR0.BYTE.CODE = 0x4;
	flexcanR1.BYTE.ID.ID = 0x502;
	CAN0->RAMn[4 * FLEXCAN_0_RX_502_SLOT + 0] = flexcanR0.R0;
	CAN0->RAMn[4 * FLEXCAN_0_RX_502_SLOT + 1] = flexcanR1.R1;
	SetBit(CAN0->IMASK1, FLEXCAN_0_RX_502_SLOT);

	/* TX Slot configuration */
	flexcanR0.BYTE.DLC = 8;
	flexcanR0.BYTE.IDE = 0;
	flexcanR0.BYTE.RTR = 0;
	flexcanR1.BYTE.ID.TYPE.STD = 0x630;
	CAN0->RAMn[4 * FLEXCAN_0_TX_630_SLOT + 0] = flexcanR0.R0;
	CAN0->RAMn[4 * FLEXCAN_0_TX_630_SLOT + 1] = flexcanR1.R1;
	SetBit(CAN0->IMASK1, FLEXCAN_0_TX_630_SLOT);

	flexcanR0.BYTE.DLC = 8;
	flexcanR0.BYTE.IDE = 0;
	flexcanR0.BYTE.RTR = 0;
	flexcanR1.BYTE.ID.TYPE.STD = 0x640;
	CAN0->RAMn[4 * FLEXCAN_0_TX_640_SLOT + 0] = flexcanR0.R0;
	CAN0->RAMn[4 * FLEXCAN_0_TX_640_SLOT + 1] = flexcanR1.R1;
	SetBit(CAN0->IMASK1, FLEXCAN_0_TX_640_SLOT);

	flexcanR0.BYTE.DLC = 8;
	flexcanR0.BYTE.IDE = 0;
	flexcanR0.BYTE.RTR = 0;
	flexcanR1.BYTE.ID.TYPE.STD = 0x650;
	CAN0->RAMn[4 * FLEXCAN_0_TX_650_SLOT + 0] = flexcanR0.R0;
	CAN0->RAMn[4 * FLEXCAN_0_TX_650_SLOT + 1] = flexcanR1.R1;
	SetBit(CAN0->IMASK1, FLEXCAN_0_TX_650_SLOT);
}

/*================================================================================================*=
 * GLOBAL FUNCTIONS
 *================================================================================================*/
/***********************************************************************************************//**
 * @brief
 *      CAN bus Channel 0 RX completed ISR
 **************************************************************************************************/
void CanISR_Rx_Ch0(void)
{
	/* Add your code here */
	FlexCanRxBufRead(&CANRX_1[0], FLEXCAN_0_RX_500_SLOT, 0x500, 8, ERROR_ACTIVE, EXTEND, DATAFRAME, CAN_0);
	FlexCanRxBufRead(&CANRX_2[0], FLEXCAN_0_RX_501_SLOT, 0x501, 8, ERROR_ACTIVE, EXTEND, DATAFRAME, CAN_0);
	FlexCanRxBufRead(&CANRX_3[0], FLEXCAN_0_RX_502_SLOT, 0x502, 8, ERROR_ACTIVE, EXTEND, DATAFRAME, CAN_0);
}

/***********************************************************************************************//**
 * @brief
 *      CAN bus Channel 0 TX completed ISR
 **************************************************************************************************/
void CanISR_Tx_Ch0(void)
{
	if (ValBit(CAN0->IFLAG1, FLEXCAN_0_TX_630_SLOT)) {
		/* clear corresponding slot Interrupt mask flag */
		SetBit(CAN0->IFLAG1, FLEXCAN_0_TX_630_SLOT);

		ctxchk_1++;
	}

	if (ValBit(CAN0->IFLAG1, FLEXCAN_0_TX_640_SLOT)) {
		/* clear corresponding slot Interrupt mask flag */
		SetBit(CAN0->IFLAG1, FLEXCAN_0_TX_640_SLOT);

		ctxchk_2++;
	}

	if (ValBit(CAN0->IFLAG1, FLEXCAN_0_TX_650_SLOT)) {
		/* clear corresponding slot Interrupt mask flag */
		SetBit(CAN0->IFLAG1, FLEXCAN_0_TX_650_SLOT);

		ctxchk_3++;
	}
}

/***********************************************************************************************//**
 * @brief
 *      CAN bus Error event
 *
 * @param[in]
 *      *CANESR
 *          Indicate the error status register
 *          refer to S32K1xx Series Reference Manual, Rev. 11, 06/2019(page. 1672)
 **************************************************************************************************/
void Can_ErrorProcess_Ch0(CANESR canesr)
{

}

/***********************************************************************************************//**
 * @brief
 *      CAN application initial
 **************************************************************************************************/
void CanApp_Init(void)
{
	CanConfig();

	if (SLOT_DET) {
		SLOT_L_flag = 1;
		SLOT_R_flag = 0;
	}

	else {
		SLOT_L_flag = 0;
		SLOT_R_flag = 1;
	}
}

/***********************************************************************************************//**
 * @brief
 *      KWP2000 Transmission driver
 *
 * @param[in]
 *      *cantx
 *          Indicate the KWP2000 TX array
 **************************************************************************************************/
void CanKWPTransmit(UI8 *cantx)
{
	FlexCanTxBufSend(cantx, FLEXCAN_0_TX_600_SLOT, 0x600, 8, ERROR_ACTIVE, DATAFRAME, CAN_0);
}

/***********************************************************************************************//**
 * @brief
 *      Urgent Transmission driver
 *
 * @param[in]
 *      *RECHT
 *          Indicate the Urgent TX array
 **************************************************************************************************/
void CanUrgentTransmit(UI8 *cantx)
{
	FlexCanTxBufSend(cantx, FLEXCAN_0_TX_6F0_SLOT, 0x6F0, 8, ERROR_ACTIVE, DATAFRAME, CAN_0);
}

/***********************************************************************************************//**
 * @brief
 *      KWP2000 Transmission driver
 *
 * @param[in]
 *      *cantx
 *          Indicate the KWP2000 TX array
 **************************************************************************************************/
void FlaKWPTransmit(UI8 *cantx)
{
	FlexCanTxBufSend(cantx, FLEXCAN_0_TX_F00_SLOT, 0xF00, 8, ERROR_ACTIVE, DATAFRAME, CAN_0);
}

/***********************************************************************************************//**
 * @brief
 *      10ms CAN Broadcast
 **************************************************************************************************/
void Can10ms_Tx(void)
{
	/* Add your code here */
	UI8		i, cantx[8];

	CANRX_1[7] = ctxchk_1;
	FlexCanTxBufSend(&CANRX_1[0], FLEXCAN_0_TX_630_SLOT, 0x630, 8, ERROR_ACTIVE, DATAFRAME, CAN_0);

	CANRX_2[7] = ctxchk_2;
	FlexCanTxBufSend(&CANRX_2[0], FLEXCAN_0_TX_640_SLOT, 0x640, 8, ERROR_ACTIVE, DATAFRAME, CAN_0);

	CANRX_3[7] = ctxchk_3;
	FlexCanTxBufSend(&CANRX_3[0], FLEXCAN_0_TX_650_SLOT, 0x650, 8, ERROR_ACTIVE, DATAFRAME, CAN_0);
}

/***********************************************************************************************//**
 * @brief
 *      50ms CAN Broadcast
 **************************************************************************************************/
void Can50ms_Tx(void)
{
	UI8		cantx[8];

	/* Add your code here */
}

/***********************************************************************************************//**
 * @brief
 *      1000ms CAN Broadcast
 **************************************************************************************************/
void Can1000ms_Tx(void)
{
	UI8		cantx[8];

	/* Add your code here */
}

/*================================================================================================*=
 *  END OF FILE
 *================================================================================================*/
