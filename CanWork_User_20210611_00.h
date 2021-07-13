/***********************************************************************************************//**
 * @file        Can Driver User.h
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

#ifndef CANDRIVER_USER_20200513_H_
#define CANDRIVER_USER_20200513_H_

/*================================================================================================*=
 * INCLUDE FILES
 *================================================================================================*/
#include "KYMCOSoftAndFirmWareDept.h"

/*================================================================================================*=
 * LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
 *================================================================================================*/
enum {
	FLEXCAN_0_TX_600_SLOT,			/* 0 */
	FLEXCAN_0_TX_630_SLOT,			/* 1 */
	FLEXCAN_0_TX_640_SLOT,			/* 2 */
	FLEXCAN_0_TX_650_SLOT,			/* 3 */
	FLEXCAN_0_TX_660_SLOT,			/* 4 */
	FLEXCAN_0_TX_670_SLOT,			/* 5 */
	FLEXCAN_0_TX_680_SLOT,			/* 6 */
	FLEXCAN_0_TX_690_SLOT,			/* 7 */
	FLEXCAN_0_TX_6A0_SLOT,			/* 8 */
	FLEXCAN_0_TX_6B0_SLOT,			/* 9 */
	FLEXCAN_0_TX_6C0_SLOT,			/* 10 */
	FLEXCAN_0_TX_6D0_SLOT,			/* 11 */
	FLEXCAN_0_TX_6E0_SLOT,			/* 12 */
	FLEXCAN_0_TX_6F0_SLOT,			/* 13 */
	FLEXCAN_0_RX_F00_SLOT,			/* 14 */
	FLEXCAN_0_TX_F00_SLOT,			/* 15 */
	FLEXCAN_0_RX_600_SLOT,			/* 16 */
	FLEXCAN_0_RX_200_SLOT,			/* 17 */
	FLEXCAN_0_RX_500_SLOT,			/* 18 */
	FLEXCAN_0_RX_501_SLOT,			/* 19 */
	FLEXCAN_0_RX_502_SLOT,			/* 20 */
	FLEXCAN_0_TOTAL_SLOT_NUM
};

/*================================================================================================*=
 * GLOBAL MACROS
 *================================================================================================*/
/* TX ID */
#define CAN0_ID600			0x600U
#define CAN0_ID630			0x630U
#define CAN0_ID640			0x640U
#define CAN0_ID650			0x650U
#define CAN0_ID660			0x660U
#define CAN0_ID670			0x670U
#define CAN0_ID680			0x680U
#define CAN0_ID690			0x690U
#define CAN0_ID6A0			0x6A0U
#define CAN0_ID6B0			0x6B0U
#define CAN0_ID6C0			0x6C0U
#define CAN0_ID6D0			0x6D0U
#define CAN0_ID6E0			0x6E0U
#define CAN0_ID6F0			0x6F0U

/* RX ID */
#define CAN0_IDF00			0xF00U
#define CAN0_ID200			0x200U

/*================================================================================================*=
 * GLOBAL CONSTANTS
 *================================================================================================*/

/*================================================================================================*=
 * GLOBAL VARIABLES
 *================================================================================================*/

/*================================================================================================*=
 * GLOBAL FUNCTIONS
 *================================================================================================*/
void CanApp_Init(void);
void Can_ErrorProcess_Ch0(CANESR);
void CanISR_Rx_Ch0(void);
void CanISR_Tx_Ch0(void);
void CanKWPTransmit(UI8 *);
void CanUrgentTransmit(UI8 *);
void Can10ms_Tx(void);
void Can50ms_Tx(void);
void Can1000ms_Tx(void);
void FlaKWPTransmit(UI8 *);

#endif /* CANDRIVER_USER_20200513_H_ */

/*================================================================================================*=
 * END OF FILE
 *================================================================================================*/
