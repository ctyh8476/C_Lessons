/***********************************************************************************************//**
 * @file        Can Driver Author.h
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

#ifndef CANDRIVER_AUTHOR_20200513_H_
#define CANDRIVER_AUTHOR_20200513_H_

/*================================================================================================*=
 * INCLUDE FILES
 *================================================================================================*/
#include "KYMCOSoftAndFirmWareDept.h"

/*================================================================================================*=
 * LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
 *================================================================================================*/
typedef union {
	struct {
		UI8		Reserved_0		:1;
		UI8		ERRINT			:1;
		UI8		BOFFINT			:1;
		UI8		RX				:1;
		UI8		FLTCONF			:2;
		UI8		TX				:1;
		UI8		IDLE			:1;
		UI8		RXWRN			:1;
		UI8		TXWRN			:1;
		UI8		STFERR			:1;
		UI8		FRMERR			:1;
		UI8		CRCERR			:1;
		UI8		ACKERR			:1;
		UI8		BIT0ERR			:1;
		UI8		BIT1ERR			:1;
		UI8		RWRNINT			:1;
		UI8		TWRNINT			:1;
		UI8		SYNCH			:1;
		UI8		BOFFDONEINT		:1;
		UI8		ERRINT_FAST		:1;
		UI8		ERROVR			:1;
		UI8		Reserved_22_25	:4;
		UI8		STFERR_FAST		:1;
		UI8		FRMERR_FAST		:1;
		UI8		CRCERR_FAST		:1;
		UI8		Reserved_29		:1;
		UI8		BIT0ERR_FAST	:1;
		UI8		BIT1ERR_FAST	:1;
	} BIT;
	UI32		LONG;
} CANESR;

typedef union {
	struct {
		UI16	TIMESTAMP		:16;
		UI8		DLC				:4;
		UI8		RTR				:1;
		UI8		IDE				:1;
		UI8		SRR				:1;
		UI8		Reserve_1		:1;
		UI8		CODE			:4;
		UI8		Reserve_0		:1;
		UI8		ESI				:1;
		UI8		BRS				:1;
		UI8		EDL				:1;
	} BYTE;
	UI32		R0;
} FLEXCANR0;

typedef union {
	struct {
		UI32	EXT				:18;
		UI16	STD				:11;
	} TYPE;
	UI32		ID;
} FLEXCANID;

typedef union {
	struct {
		FLEXCANID	ID;
		UI8			PRIO		:3;
	} BYTE;
	UI32		R1;
} FLEXCANR1;

typedef union {
	struct {
		UI8		DB3;
		UI8		DB2;
		UI8		DB1;
		UI8		DB0;
	} BYTE;
	UI32		R2;
} FLEXCANR2;

typedef union {
	struct {
		UI8		DB7;
		UI8		DB6;
		UI8		DB5;
		UI8		DB4;
	} BYTE;
	UI32		R3;
} FLEXCANR3;

enum {
	CAN_0,							/* 0 */
	CAN_1,							/* 1 */
	CAN_2							/* 2 */
};

enum {
	ERROR_ACTIVE,					/* 0 */
	ERROR_PASSIVE,					/* 1 */
};

enum {
	STANDARD,						/* 0 */
	EXTEND,							/* 1 */
};

enum {
	DATAFRAME,						/* 0 */
	REMOTEFRAME						/* 1 */
};

/*================================================================================================*=
 * GLOBAL MACROS
 *================================================================================================*/

/*================================================================================================*=
 * GLOBAL CONSTANTS
 *================================================================================================*/

/*================================================================================================*=
 * GLOBAL VARIABLES
 *================================================================================================*/

/*================================================================================================*=
 * GLOBAL FUNCTIONS
 *================================================================================================*/
void CANInitial(void);
void FlexCanTxBufSend(UI8 *, UI8, UI32, UI8, UI8, UI8, UI8);
void FlexCanRxBufRead(UI8 *, UI8, UI32, UI8, UI8, UI8, UI8, UI8);

#endif /* CANDRIVER_AUTHOR_20200513_H_ */

/*================================================================================================*=
 * END OF FILE
 *================================================================================================*/
