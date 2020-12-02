/*
 * CAN_Cfg.h
 *
 *  Created on: Aug 16, 2020
 *      Author: Eng.Magdy_2
 */

#ifndef MCAL_CAN_CAN_CFG_H_
#define MCAL_CAN_CAN_CFG_H_

/*============================================================*/
/*==========               includes                 ==========*/
/*============================================================*/
#include <MCAL/CAN/CAN_Private.h>
#include <MCAL/CAN/CAN_Ports.h>
#include <MCAL/GPIO/GPIO_Interface.h>
#include <UTL/STD_Types.h>
#include <UTL/utilites.h>
#include "tm4c123gh6pm.h"

/*============================================================*/
/*==========              Definitions               ==========*/
/*============================================================*/
// for mode config
#define Obj_Cfg



///////////////////////////////////////////////////////

#define CAN_MAX_STANDARD_ID             0x7FF
#define CAN_MAX_EXTENDED_ID             0x1FFFFFFF
#define CAN_MAX_DATA_LENGTH             8



#define CAN_INT_ERROR                   CAN_CTL_EIE
#define CAN_INT_MASTER                  CAN_CTL_IE
#define CAN_INT_STATUS                  CAN_CTL_SIE
#define CAN_STATUS_BUS_OFF              CAN_STS_BOFF
#define CAN_STATUS_EPASS                CAN_STS_EPASS
#define CAN_STATUS_EWARN                CAN_STS_EWARN
#define CAN_STATUS_LEC_ACK              CAN_STS_LEC_ACK
#define CAN_STATUS_LEC_BIT0             CAN_STS_LEC_BIT0
#define CAN_STATUS_LEC_BIT1             CAN_STS_LEC_BIT1
#define CAN_STATUS_LEC_CRC              CAN_STS_LEC_CRC
#define CAN_STATUS_LEC_FORM             CAN_STS_LEC_FORM
#define CAN_STATUS_LEC_MASK             CAN_STS_LEC_M
#define CAN_STATUS_LEC_MSK
#define CAN_STATUS_LEC_NONE             CAN_STS_LEC_NONE
#define CAN_STATUS_LEC_STUFF            CAN_STS_LEC_STUFF
#define CAN_STATUS_RXOK                 CAN_STS_RXOK
#define CAN_STATUS_TXOK                 CAN_STS_TXOK
#define MSG_OBJ_DATA_LOST               CAN_IF1MCTL_MSGLST
#define MSG_OBJ_EXTENDED_ID             CAN_IF1ARB2_XTD
#define MSG_OBJ_FIFO                    1
#define MSG_OBJ_NEW_DATA                CAN_IF1MCTL_NEWDAT
#define MSG_OBJ_NO_FLAGS                0
#define MSG_OBJ_REMOTE_FRAME            CAN_IF1MCTL_RMTEN
#define MSG_OBJ_RX_INT_ENABLE           CAN_IF1MCTL_RXIE
#define MSG_OBJ_STATUS_MASK
#define MSG_OBJ_TX_INT_ENABLE           CAN_IF1MCTL_TXIE
#define MSG_OBJ_USE_DIR_FILTER          CAN_IF1MSK2_MDIR
#define MSG_OBJ_USE_EXT_FILTER          CAN_IF1MSK2_MXTD
#define MSG_OBJ_USE_ID_FILTER           CAN_IF1MCTL_UMASK


/*
    Enumerations to contrust on demand:
*/


typedef enum {
    CAN_INT_STS_CAUSE,
    CAN_INT_STS_OBJECT
}tCANIntStsReg;

typedef enum  {
    CAN_STS_CONTROL = 0,        //the main controller status
    CAN_STS_TXREQUEST = 1,      //bit mask of objects pending transmission
    CAN_STS_NEWDAT = 2,         //bit mask of objects with new data
    CAN_STS_MSGVAL = 3,         //bit mask of objects with valid configuration
}tCANStsReg;

typedef enum {

    CAN_MSG_OBJ_TYPE_TX = 0,
    CAN_MSG_OBJ_TYPE_RX = 1

}tMsgObjType;

typedef enum {
    ZERO_BYTE   = 0,
    ONE_BYTE    = 1,
    TWO_BYTE    = 2,
    THREE_BYTE  = 3,
    FOUR_BYTE   = 4,
    FIVE_BYTE   = 5,
    SIX_BYTE    = 6,
    SEVEN_BYTE  = 7,
    EIGHT_BYTE  = 8,
}tCAN_MSG_LENGTH;

typedef struct {
    uint32 ui32SyncPropPhase1Seg;
    uint32 ui32Phase2Seg;
    uint32 ui32SJW;
    uint32 prescaler ;
}tCANBitClkParms;

typedef struct {

    uint32 Msg_ID;
    uint32 Flags;
    tCAN_MSG_LENGTH Msg_Length;
    uint8 *Msg_Data;      // Array

}tCANConfigTXMsgObj;


typedef struct {

    uint32 Msg_ID;
    uint32 Msg_ID_MSK;
    uint32 Flags;

}tCANConfigRXMsgObj;


typedef struct {

    tCAN_MSG_LENGTH Msg_Length;
    uint8 Msg_Data[CAN_MAX_DATA_LENGTH];      // Array

}tCANReadRXData;


typedef enum {
    STANDARD_FRAME = 0,
    EXTENDED_FRAME = 1
}tCANFRAME_TYPE;

typedef enum {
    Msg_Obj_1  = 0x01,
    Msg_Obj_2  = 0x02,
    Msg_Obj_3  = 0x03,
    Msg_Obj_4  = 0x04,
    Msg_Obj_5  = 0x05,
    Msg_Obj_6  = 0x06,
    Msg_Obj_7  = 0x07,
    Msg_Obj_8  = 0x08,
    Msg_Obj_9  = 0x09,
    Msg_Obj_10 = 0x0A,
    Msg_Obj_11 = 0x0B,
    Msg_Obj_12 = 0x0C,
    Msg_Obj_13 = 0x0D,
    Msg_Obj_14 = 0x0E,
    Msg_Obj_15 = 0x0F,
    Msg_Obj_16 = 0x10,
    Msg_Obj_17 = 0x11,
    Msg_Obj_18 = 0x12,
    Msg_Obj_19 = 0x13,
    Msg_Obj_20 = 0x14,
    Msg_Obj_21 = 0x15,
    Msg_Obj_22 = 0x16,
    Msg_Obj_23 = 0x17,
    Msg_Obj_24 = 0x18,
    Msg_Obj_25 = 0x19,
    Msg_Obj_26 = 0x1A,
    Msg_Obj_27 = 0x1B,
    Msg_Obj_28 = 0x1C,
    Msg_Obj_29 = 0x1D,
    Msg_Obj_30 = 0x1E,
    Msg_Obj_31 = 0x1F,
    Msg_Obj_32 = 0x20,

}Msg_Obj_ID;


//Configuration Struct
typedef struct{
    Port_Name Port_Base;
    CAN_Base Base;
    uint8 Mode;
    tCANBitClkParms *psClkParms;
}CAN_Cfg;

/*============================================================*/
/*==========              ProtoTypes                ==========*/
/*============================================================*/
void CAN_Init(CAN_Cfg Cfg);
void CAN_Enable (CAN_Base Base);
void CAN_Disable (CAN_Base Base);

void CAN_TX_MSG_SetUp(CAN_Base Base, Msg_Obj_ID ObjID, tCANConfigTXMsgObj *MsgObject);
void CAN_RX_MSG_SetUp(CAN_Base Base, Msg_Obj_ID ObjID, tCANConfigRXMsgObj *MsgObject);
void CAN_Message_Get (CAN_Base Base, Msg_Obj_ID ObjID, tCANReadRXData *psMsgObject, bool bClrPendingInt);

void CAN_Message_Clear(CAN_Base Base, uint32 ObjID);
bool CAN_Retry_Get(CAN_Base Base);
void CAN_Retry_Set(CAN_Base Base, bool bAutoRetry);
uint32 CAN_Status_Get(CAN_Base Base, tCANStsReg eStatusReg);

void CAN_Write(CAN_Base Base, Msg_Obj_ID ObjID, tCANConfigTXMsgObj *MsgObject);
tCANReadRXData CAN_Read(Msg_Obj_ID ObjID);

#endif /* MCAL_CAN_CAN_CFG_H_ */
