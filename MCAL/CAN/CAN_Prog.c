/*
 * CAN_Prog.c
 *
 *  Created on: Aug 16, 2020
 *      Author: Eng.Magdy_2
 */



/*============================================================*/
/*==========               includes                 ==========*/
/*============================================================*/
#include <MCAL/CAN/CAN_Cfg.h>


/*============================================================*/
/*==========              GlobalVars                ==========*/
/*============================================================*/

tCANReadRXData ReceivedData[32];

/*============================================================*/
/*==========              ProtoTypes                ==========*/
/*============================================================*/
void CAN_Int_Enable (CAN_Base Base, uint32 ui32IntFlags);

void CAN0_ISR(void);
void CAN1_ISR(void);
/*============================================================*/
/*==========             Functions Bodies           ==========*/
/*============================================================*/


void CAN_Init(CAN_Cfg Cfg){

    //GPIO INIT
    //=============================================================================================
    //=============================================================================================
    if(Cfg.Port_Base == Port_A) SET_BIT(SYSCTL_RCGC2,GPIOA); // Clock For Port A
    if(Cfg.Port_Base == Port_B) SET_BIT(SYSCTL_RCGC2,GPIOB); // clock For Port B
    if(Cfg.Port_Base == Port_E) SET_BIT(SYSCTL_RCGC2,GPIOE); // clock For Port E
    if(Cfg.Port_Base == Port_F) SET_BIT(SYSCTL_RCGC2,GPIOF); // clock For Port F

    //Unlock PORTS
    ACCESS_REG(Cfg.Port_Base+LOCK_R) = GPIO_LOCK_KEY ;
    ACCESS_REG(Cfg.Port_Base+CR_R)   = 0xFF;


    // PCTL ,DIR , AFSEL ,DEN :
    if ( Cfg.Port_Base == Port_A ){

        //Port Control
        ACCESS_REG(Cfg.Port_Base+PCTL_R) &= ~(0xFF);
        ACCESS_REG(Cfg.Port_Base+PCTL_R) |= GPIO_PCTL_PA0_CAN1RX; // PMC0 control CAN1RX
        ACCESS_REG(Cfg.Port_Base+PCTL_R) |= GPIO_PCTL_PA1_CAN1TX; // PMC1 control CAN1TX
        //Direction Bit :
        CLR_BIT((Cfg.Port_Base+DIR_R) ,   (1<<BIT0)); // RX >> Input
        SET_BIT((Cfg.Port_Base+DIR_R)  ,   (1<<BIT1)); // TX >> Output
        //Alternate Function :
        SET_BIT((Cfg.Port_Base+AFSEL_R),   (1<<BIT0)); // Enable Alternate Fun Pin0
        SET_BIT((Cfg.Port_Base+AFSEL_R),   (1<<BIT1)); // Enable Alternate Fun Pin1
        //Digital Enable:
        SET_BIT((Cfg.Port_Base+DEN_R), (1<<BIT0)); // Enable Digital Pin0
        SET_BIT((Cfg.Port_Base+DEN_R), (1<<BIT1)); // Enable Digital Pin1

    }else if((Cfg.Port_Base == Port_B) || (Cfg.Port_Base == Port_E)){

        ACCESS_REG(Cfg.Port_Base+PCTL_R) &= ~(0xFF0000);
        //Disable Analog Mode :
        CLR_BIT((Cfg.Port_Base+AMSEL_R),(1<<BIT4));
        CLR_BIT((Cfg.Port_Base+AMSEL_R),(1<<BIT5));

        //Port Control :
        ACCESS_REG(Cfg.Port_Base+PCTL_R) |= GPIO_PCTL_PB4_CAN0RX; // PMC4 control CAN0RX
        ACCESS_REG(Cfg.Port_Base+PCTL_R) |= GPIO_PCTL_PB5_CAN0TX; // PMC5 control CAN0TX
        //Direction Bit :
        CLR_BIT((Cfg.Port_Base+DIR_R) ,   (1<<BIT4)); // RX >> Input
        SET_BIT ((Cfg.Port_Base+DIR_R)  ,   (1<<BIT5)); // TX >> Output

        //Alternate Function :
        SET_BIT((Cfg.Port_Base+AFSEL_R),   (1<<BIT4)); // Enable Alternate Fun Pin4
        SET_BIT((Cfg.Port_Base+AFSEL_R),   (1<<BIT5)); // Enable Alternate Fun Pin5
        //Digital Enable:
        SET_BIT((Cfg.Port_Base+DEN_R), (1<<BIT4)); // Enable Digital Pin4
        SET_BIT((Cfg.Port_Base+DEN_R), (1<<BIT5)); // Enable Digital Pin5

    }else { // Port_F
        //Port Control :
        ACCESS_REG(Cfg.Port_Base+PCTL_R) &= ~(0xF00F);
        ACCESS_REG(Cfg.Port_Base+PCTL_R) |= GPIO_PCTL_PF0_CAN0RX; // PMC0 control CAN0RX
        ACCESS_REG(Cfg.Port_Base+PCTL_R) |= GPIO_PCTL_PF3_CAN0TX;// PMC3 control CAN0TX
        //Direction Bit :
        CLR_BIT((Cfg.Port_Base+DIR_R),    (1<<BIT0)); // RX >> Input
        SET_BIT ((Cfg.Port_Base+DIR_R) ,    (1<<BIT3)); // TX >> Output
        //Alternate Function
        SET_BIT((Cfg.Port_Base+AFSEL_R),   (1<<BIT0)); // Enable Alternate Fun Pin0
        SET_BIT((Cfg.Port_Base+AFSEL_R),   (1<<BIT3)); // Enable Alternate Fun Pin3
        //Digital Enable:
        SET_BIT((Cfg.Port_Base+DEN_R), (1<<BIT0)); // Enable Digital Pin0
        SET_BIT((Cfg.Port_Base+DEN_R), (1<<BIT3)); // Enable Digital Pin3
    }

    //=============================================================================================
    //=============================================================================================



    //Enable CAN
    //=============================================================================================
    //=============================================================================================
    if(Cfg.Base == CAN0){
        //Enable Clock :
        SET_BIT(SYSCTL_RCGC0 , SYSCTL_RCGC0_CAN0 ) ;                 // Clock For CAN0
    }else{
        SET_BIT(SYSCTL_RCGC0 , SYSCTL_RCGC0_CAN1 ) ;             // Clock For CAN1

    }

    //CAN CONFIGURATION :
    SET_BIT((Cfg.Base+CAN_CTL_R) , CAN_CTL_INIT);

    while(CAN0_IF1CRQ_R & CAN_IF1CRQ_BUSY) ; //wait while CAN0 Module is BUSY,set Flag .

    // Check Mode :

    if(Cfg.Mode == Test_Mode){
        SET_BIT((Cfg.Base+CAN_CTL_R) , CAN_CTL_TEST);    // Enable Test Mode
        SET_BIT((Cfg.Base+CAN_TST_R) , CAN_TST_LBACK );  // Enable LoopBack
    }else{
        CLR_BIT((Cfg.Base+CAN_CTL_R) , CAN_CTL_TEST);  // Disable Test Mode
        CLR_BIT((Cfg.Base+CAN_CTL_R) , CAN_TST_LBACK); // Disable LoopBack
    }
    //=============================================================================================
    //=============================================================================================

    //CAN BIT Config
    //=============================================================================================
    //=============================================================================================
#ifdef Obj_Cfg
    //Enable Access CANBIT
    SET_BIT((Cfg.Base+CAN_CTL_R) , CAN_CTL_CCE) ;

    ACCESS_REG((Cfg.Base+CAN_BIT_R))&= ~(0xFFFF);

    ACCESS_REG((Cfg.Base+CAN_BIT_R))|= (Cfg.psClkParms-> prescaler -1); //BRP_SEG SET
    ACCESS_REG((Cfg.Base+CAN_BIT_R))|= ((Cfg.psClkParms -> ui32SJW-1) << 6); //Phase2_SEG SET
    ACCESS_REG((Cfg.Base+CAN_BIT_R))|= ((Cfg.psClkParms -> ui32SyncPropPhase1Seg-1) << 8); //Prop_SEG + Phase1_SEG SET
    ACCESS_REG((Cfg.Base+CAN_BIT_R))|= ((Cfg.psClkParms -> ui32Phase2Seg-1) << 12); //SJW_SEG SET

    //Disable Access CANBIT
    CLR_BIT((Cfg.Base+CAN_CTL_R) , CAN_CTL_CCE) ;
#endif
    //=============================================================================================
    //=============================================================================================


    // Interrupt enable
    //=============================================================================================
    //=============================================================================================
    uint32 IntEnableFlags = CAN_INT_MASTER | CAN_INT_STATUS;
    CAN_Int_Enable(Cfg.Base, IntEnableFlags);


}


/*********************************************************************************************************/
/*********************************************************************************************************/
/*********************************************************************************************************/

void CAN_Enable(CAN_Base Base){

    //Out From Initialization Mode To Start Transmit :
    CLR_BIT((Base+CAN_CTL_R) , CAN_CTL_INIT);

}

/*********************************************************************************************************/
/*********************************************************************************************************/
/*********************************************************************************************************/
void CAN_Disable(CAN_Base Base){

    if(Base == CAN0){
        //Disable Clock :
        CLR_BIT(SYSCTL_RCGC0_R , SYSCTL_RCGC0_CAN0 ) ;               // Clock For CAN0
    }else{
        CLR_BIT(SYSCTL_RCGC0_R , SYSCTL_RCGC0_CAN1 ) ;               // Clock For CAN1
    }
    /*Enter Initialization Mode :
    SET_BIT((Base+CAN_CTL_R) , CAN_CTL_INIT);
    */
}


/*********************************************************************************************************/
/**********************************        CAN_TX_MSG_SetUp             **********************************/
/*********************************************************************************************************/

void CAN_TX_MSG_SetUp(CAN_Base Base, Msg_Obj_ID ObjID, tCANConfigTXMsgObj *MsgObject){

    CLR_BIT((Base + CAN_IF1ARB2_R), CAN_IF1ARB2_MSGVAL);

    tCANFRAME_TYPE Frame_Type = STANDARD_FRAME;

    //Check the message ID
    if(((MsgObject -> Msg_ID) > CAN_MAX_STANDARD_ID) && ((MsgObject -> Msg_ID) < CAN_MAX_EXTENDED_ID) && (MsgObject->Flags & MSG_OBJ_EXTENDED_ID)){

        Frame_Type = EXTENDED_FRAME;

    }else if((MsgObject -> Msg_ID) > CAN_MAX_EXTENDED_ID){
        return;    //UNValid Msg ID
    }

    //Set WRNRD bit = 1
    SET_BIT((Base + CAN_IF1CMSK_R), CAN_IF1CMSK_WRNRD);

    //Set ARB bit to enable access arbitration bits
    SET_BIT((Base + CAN_IF1CMSK_R), CAN_IF1CMSK_ARB);

    //Set Control bit to enable access control bits
    SET_BIT((Base + CAN_IF1CMSK_R), CAN_IF1CMSK_CONTROL);

    //Clear Interrupt Pending Bit
    //SET_BIT((Base + CAN_IF1CMSK_R), CAN_IF1CMSK_CLRINTPND);

    //Access Transmision request
    //SET_BIT((Base + CAN_IF1CMSK_R), CAN_IF1CMSK_TXRQST);

    //Access Data Bytes 0 to 3
    SET_BIT((Base + CAN_IF1CMSK_R), CAN_IF1CMSK_DATAA);

    //Access Data Bytes 4 to 7
    SET_BIT((Base + CAN_IF1CMSK_R), CAN_IF1CMSK_DATAB);


    /*******************STANDARD FRAME*******************/
    if(Frame_Type == STANDARD_FRAME){

        CLR_BIT((Base + CAN_IF1ARB2_R), CAN_IF1ARB2_XTD);
        CLR_BIT((Base + CAN_IF1MSK2_R), CAN_IF1MSK2_MXTD);

        //First clear ARB2 Field
        ACCESS_REG(Base + CAN_IF1ARB2_R) &= ~(0x1FFF);

        //Write the message ID
        ACCESS_REG(Base + CAN_IF1ARB2_R) |= ((MsgObject->Msg_ID) << 2);


    }

    /*******************EXTENDED FRAME*******************/
    else if (Frame_Type == EXTENDED_FRAME){

        SET_BIT((Base + CAN_IF1ARB2_R), CAN_IF1ARB2_XTD);
        CLR_BIT((Base + CAN_IF2MSK2_R), CAN_IF2MSK2_MXTD);

        //First clear ARB1 Field
        ACCESS_REG(Base + CAN_IF1ARB1_R) &= ~(0xFFFF);

        //Write first part of ID
        ACCESS_REG(Base + CAN_IF1ARB1_R) |= (MsgObject->Msg_ID & 0x0000FFFF);

        //First clear ARB2 Field
        ACCESS_REG(Base + CAN_IF1ARB2_R) &= ~(0x1FFF);

        //Write Second part of ID
        ACCESS_REG(Base + CAN_IF1ARB2_R) |= ((MsgObject->Msg_ID & 0x1FFF0000) >> 16);

    }


    // Set Direction bit to indicate transmit message object
    SET_BIT((Base + CAN_IF1ARB2_R), CAN_IF1ARB2_DIR);


    if(MsgObject->Flags & MSG_OBJ_TX_INT_ENABLE){

        //enable interrupt on successful transmission
        SET_BIT((Base + CAN_IF1MCTL_R), CAN_IF1MCTL_TXIE);

    }



    // Set message Valid bit
    SET_BIT((Base + CAN_IF1ARB2_R), CAN_IF1ARB2_MSGVAL);

    // Mark this bit as end of buffer because no use of FIFOs in transmit mode
    SET_BIT((Base + CAN_IF1MCTL_R), CAN_IF1MCTL_EOB);


    //First clear DLC Field
    ACCESS_REG((Base + CAN_IF1MCTL_R)) &= ~(0xF);

    //Write the message length code
    ACCESS_REG((Base + CAN_IF1MCTL_R)) |= MsgObject->Msg_Length;

    //Write Message number into MNUM field to start transfer
    ACCESS_REG((Base + CAN_IF1CRQ_R)) = ObjID;
}

/*********************************************************************************************************/
/***************************             CAN_RX_MSG_SetUp              ***********************************/
/*********************************************************************************************************/

void CAN_RX_MSG_SetUp(CAN_Base Base, Msg_Obj_ID ObjID, tCANConfigRXMsgObj *MsgObject){
    CLR_BIT((Base + CAN_IF2ARB2_R), CAN_IF2ARB2_MSGVAL);

    tCANFRAME_TYPE Frame_Type = STANDARD_FRAME;

    //Check the message ID
    if(((MsgObject -> Msg_ID) > CAN_MAX_STANDARD_ID) && ((MsgObject -> Msg_ID) < CAN_MAX_EXTENDED_ID) && (MsgObject->Flags & MSG_OBJ_EXTENDED_ID)){

        Frame_Type = EXTENDED_FRAME;

    }else if((MsgObject -> Msg_ID) > CAN_MAX_EXTENDED_ID){

        return;    //UNValid Msg ID
    }


    //Check using mask or not
    if(MsgObject->Flags & MSG_OBJ_USE_ID_FILTER){

        //Set Mask bit
        SET_BIT((Base+CAN_IF2MCTL_R), CAN_IF2MCTL_UMASK);
        SET_BIT((Base + CAN_IF2CMSK_R), CAN_IF2CMSK_MASK);

    }

    //Set WRNRD bit = 1
    SET_BIT((Base + CAN_IF2CMSK_R), CAN_IF2CMSK_WRNRD);

    //Set ARB bit to enable access arbitration bits
    SET_BIT((Base + CAN_IF2CMSK_R), CAN_IF2CMSK_ARB);

    //Set Control bit to enable access control bits
    SET_BIT((Base + CAN_IF2CMSK_R), CAN_IF2CMSK_CONTROL);

    //Clear Interrupt Pending Bit
    //SET_BIT((Base + CAN_IF2CMSK_R), CAN_IF2CMSK_CLRINTPND);

    //Access Transmision request
    //SET_BIT((Base + CAN_IF2CMSK_R), CAN_IF2CMSK_TXRQST);

    //Access Data Bytes 0 to 3
    SET_BIT((Base + CAN_IF2CMSK_R), CAN_IF2CMSK_DATAA);

    //Access Data Bytes 4 to 7
    SET_BIT((Base + CAN_IF2CMSK_R), CAN_IF2CMSK_DATAB);


    /*******************STANDARD FRAME*******************/

    if(Frame_Type == STANDARD_FRAME){


        CLR_BIT((Base + CAN_IF2ARB2_R), CAN_IF2ARB2_XTD);

        if(MsgObject->Flags & MSG_OBJ_USE_ID_FILTER){

            //First clear Mask2 Field
            ACCESS_REG(Base + CAN_IF2MSK2_R) &= ~(0x1FFF);

            //Write the ID mask
            ACCESS_REG(Base + CAN_IF2MSK2_R) |= ((MsgObject->Msg_ID_MSK) << 2);

            //Clear MXTD Bit
            CLR_BIT(Base + CAN_IF2MSK2_R, CAN_IF2MSK2_MXTD);

            //The message direction DIR bit is used for acceptance filtering
            SET_BIT(Base + CAN_IF2MSK2_R, CAN_IF2MSK2_MDIR);

        }

        //First clear ARB2 Field
        ACCESS_REG(Base + CAN_IF2ARB2_R) &= ~(0x1FFF);

        //Write the message ID
        ACCESS_REG(Base + CAN_IF2ARB2_R) |= ((MsgObject->Msg_ID) << 2);

    }

    /*******************EXTENDED FRAME*******************/

    else if (Frame_Type == EXTENDED_FRAME){


        SET_BIT((Base + CAN_IF2ARB2_R), CAN_IF2ARB2_XTD);

        if(MsgObject->Flags & MSG_OBJ_USE_ID_FILTER){

            //First clear Mask1 Field
            ACCESS_REG(Base + CAN_IF2MSK1_R) &= ~(0xFFFF);

            //Write first part of ID_MSK
            ACCESS_REG(Base + CAN_IF2MSK1_R) |= (MsgObject->Msg_ID_MSK & 0x0000FFFF);

            //First clear Mask2 Field
            ACCESS_REG(Base + CAN_IF2MSK2_R) &= ~(0x1FFF);

            //Write Second part of ID_MSK
            ACCESS_REG(Base + CAN_IF2MSK2_R) |= ((MsgObject->Msg_ID_MSK & 0x1FFF0000) >> 16);

            //Set MXTD Bit
            SET_BIT(Base + CAN_IF2MSK2_R, CAN_IF2MSK2_MXTD);

            //The message direction DIR bit is used for acceptance filtering
            SET_BIT(Base + CAN_IF2MSK2_R, CAN_IF2MSK2_MDIR);

        }

        //First clear ARB1 Field
        ACCESS_REG(Base + CAN_IF2ARB1_R) &= ~(0xFFFF);

        //Write first part of ID
        ACCESS_REG(Base + CAN_IF2ARB1_R) |= (MsgObject->Msg_ID & 0x0000FFFF);

        //First clear ARB2 Field
        ACCESS_REG(Base + CAN_IF2ARB2_R) &= ~(0x1FFF);

        //Write Second part of ID
        ACCESS_REG(Base + CAN_IF2ARB2_R) |= ((MsgObject->Msg_ID & 0x1FFF0000) >> 16);

    }


    //Clear Direction bit to indicate Receive message object
    CLR_BIT((Base + CAN_IF2ARB2_R), CAN_IF2ARB2_DIR);

    if(MsgObject->Flags & MSG_OBJ_RX_INT_ENABLE){

        //enable interrupt on successful reception
        SET_BIT((Base + CAN_IF2MCTL_R), CAN_IF2MCTL_RXIE);
    }

    //Set message Valid bit
    SET_BIT((Base + CAN_IF2ARB2_R), CAN_IF2ARB2_MSGVAL);


    //Check using FIFO or not
    if(MsgObject->Flags & MSG_OBJ_FIFO){
        CLR_BIT((Base + CAN_IF2MCTL_R), CAN_IF2MCTL_EOB);
    }else{
        SET_BIT((Base + CAN_IF2MCTL_R), CAN_IF2MCTL_EOB);

    }

    //Write Message number into MNUM field to start transfer
    ACCESS_REG((Base + CAN_IF2CRQ_R)) = ObjID;


}


/*********************************************************************************************************/
/********************************           CAN_Message_Get         **************************************/
/*********************************************************************************************************/
void CAN_Message_Get (CAN_Base Base, Msg_Obj_ID ObjID, tCANReadRXData *psMsgObject, bool bClrPendingInt){

    //clear WRNRD bit = 0
    CLR_BIT((Base + CAN_IF2CMSK_R), CAN_IF2CMSK_WRNRD);

    //Set the MNUM field to the Message object ID
    ACCESS_REG((Base + CAN_IF2CRQ_R)) = ObjID;

    //while(BIT_IS_SET((Base+ CAN_IF2MCTL_R), CAN_IF2MCTL_NEWDAT)){}


    //Reading data and store it into the message objsct data field

    psMsgObject->Msg_Data[0] = (ACCESS_REG((Base + CAN_IF2DA1_R)) & 0x000000FF);
    psMsgObject->Msg_Data[1] = ((ACCESS_REG((Base + CAN_IF2DA1_R)) &0x0000FF00) >> 8);
    psMsgObject->Msg_Data[2] = (ACCESS_REG((Base + CAN_IF2DA2_R)) & 0x000000FF);
    psMsgObject->Msg_Data[3] = ((ACCESS_REG((Base + CAN_IF2DA2_R)) & 0x0000FF00) >> 8);
    psMsgObject->Msg_Data[4] = (ACCESS_REG((Base + CAN_IF2DB1_R)) & 0x000000FF);
    psMsgObject->Msg_Data[5] = ((ACCESS_REG((Base + CAN_IF2DB1_R)) & 0x0000FF00) >> 8);
    psMsgObject->Msg_Data[6] = (ACCESS_REG((Base + CAN_IF2DB2_R)) & 0x000000FF);
    psMsgObject->Msg_Data[7] = ((ACCESS_REG((Base + CAN_IF2DB2_R)) & 0x0000FF00) >> 8);


    //Message Length
    psMsgObject-> Msg_Length = (tCAN_MSG_LENGTH)(ACCESS_REG((Base + CAN_IF2MCTL_R)) & 0xF);
    if(bClrPendingInt == TRUE){
        CLR_BIT((Base + CAN_IF2MCTL_R), CAN_IF2MCTL_INTPND);
    }

}


/*********************************************************************************************************/
/*******************************           CAN_Message_Clear         *************************************/
/*********************************************************************************************************/
void CAN_Message_Clear(CAN_Base Base, uint32 ObjID){
    //Set WRNRD bit = 1
    SET_BIT((Base + CAN_IF1CMSK_R), CAN_IF1CMSK_WRNRD);

    //Set ARB bit to enable access arbitration bits
    SET_BIT((Base + CAN_IF1CMSK_R), CAN_IF1CMSK_ARB);

    //Set Control bit to enable access control bits
    SET_BIT((Base + CAN_IF1CMSK_R), CAN_IF1CMSK_CONTROL);

    //Clear Interrupt Pending Bit
    SET_BIT((Base + CAN_IF1CMSK_R), CAN_IF1CMSK_CLRINTPND);

    //Access Data Bytes 0 to 3
    SET_BIT((Base + CAN_IF1CMSK_R), CAN_IF1CMSK_DATAA);

    //Access Data Bytes 4 to 7
    SET_BIT((Base + CAN_IF1CMSK_R), CAN_IF1CMSK_DATAB);


    //Clear Mask1 Field
    ACCESS_REG(Base + CAN_IF1MSK1_R) &= ~(0xFFFF);

    //Clear Mask2 Field
    ACCESS_REG(Base + CAN_IF1MSK2_R) &= ~(0x1FFF);

    //Clear ARB1 Field
    ACCESS_REG(Base + CAN_IF1ARB1_R) &= ~(0xFFFF);

    //Clear ARB2 Field
    ACCESS_REG(Base + CAN_IF1ARB2_R) &= ~(0x1FFF);

    //Clear DLC Field
    ACCESS_REG((Base + CAN_IF1MCTL_R)) &= ~(0xF);

    //Clear Data Registers
    ACCESS_REG((Base + CAN_IF1DA1_R)) = 0;
    ACCESS_REG((Base + CAN_IF1DA2_R)) = 0;
    ACCESS_REG((Base + CAN_IF1DB1_R)) = 0;
    ACCESS_REG((Base + CAN_IF1DB2_R)) = 0;

    //Clear message Valid bit
    CLR_BIT((Base + CAN_IF1ARB2_R), CAN_IF1ARB2_MSGVAL);

    ACCESS_REG((Base + CAN_IF1CRQ_R)) = ObjID;
}

/*********************************************************************************************************/
/********************************            CAN_Retry_Get          **************************************/
/*********************************************************************************************************/
bool CAN_Retry_Get(CAN_Base Base){
    bool Return_Val = BIT_IS_CLR((Base + CAN_CTL_R), CAN_CTL_DAR);
    return Return_Val;
}
/*********************************************************************************************************/
/********************************           CAN_Retry_Set           **************************************/
/*********************************************************************************************************/
void CAN_Retry_Set(CAN_Base Base, bool bAutoRetry){

    if(bAutoRetry == TRUE){
        //Enable Retransmission mode
        CLR_BIT((Base + CAN_CTL_R), CAN_CTL_DAR);
    }
    else if(bAutoRetry == FALSE){
        //Disable Retransmission mode
        SET_BIT((Base + CAN_CTL_R), CAN_CTL_DAR);
    }
}
/*********************************************************************************************************/
/********************************           CAN_Status_Get          **************************************/
/*********************************************************************************************************/
uint32 CAN_Status_Get(CAN_Base Base, tCANStsReg eStatusReg){

    uint32 Return_Val;
    if(eStatusReg == CAN_STS_CONTROL){
        Return_Val = (ACCESS_REG(Base + CAN_STS_R) & 0xFF);
    }else if(eStatusReg == CAN_STS_TXREQUEST){
        Return_Val = (ACCESS_REG(Base + CAN_TXRQ1_R) & 0xFFFF) | ((ACCESS_REG(Base + CAN_TXRQ2_R) & 0xFFFF) << 16);
    }else if(eStatusReg == CAN_STS_NEWDAT){
        Return_Val = (ACCESS_REG(Base + CAN_NWDA1_R) & 0xFFFF) | ((ACCESS_REG(Base + CAN_NWDA2_R) & 0xFFFF) << 16);
    }else if(eStatusReg == CAN_STS_MSGVAL){
        Return_Val = (ACCESS_REG(Base + CAN_MSG1VAL_R) & 0xFFFF) | ((ACCESS_REG(Base + CAN_MSG2VAL_R) & 0xFFFF) << 16);
    }
    return Return_Val;
}

/*********************************************************************************************************/
/********************************               CAN_Write           **************************************/
/*********************************************************************************************************/
void CAN_Write(CAN_Base Base, Msg_Obj_ID ObjID, tCANConfigTXMsgObj *MsgObject){
    //Set WRNRD bit = 0
    CLR_BIT((Base + CAN_IF1CMSK_R), CAN_IF1CMSK_WRNRD);

    ACCESS_REG((Base + CAN_IF1CRQ_R)) = ObjID;

    //Set WRNRD bit = 1
    SET_BIT((Base + CAN_IF1CMSK_R), CAN_IF1CMSK_WRNRD);
    SET_BIT((Base + CAN_IF1CMSK_R), CAN_IF1CMSK_CONTROL);

    //Access Data Bytes 0 to 3
    SET_BIT((Base + CAN_IF1CMSK_R), CAN_IF1CMSK_DATAA);

    //Access Data Bytes 4 to 7
    SET_BIT((Base + CAN_IF1CMSK_R), CAN_IF1CMSK_DATAB);

    //First clear DLC Field
    ACCESS_REG((Base + CAN_IF1MCTL_R)) &= ~(0xF);

    //Write the message length code
    ACCESS_REG((Base + CAN_IF1MCTL_R)) |= MsgObject->Msg_Length;

    //Data
    ACCESS_REG((Base + CAN_IF1DA1_R)) = (MsgObject -> Msg_Data[0]);
    ACCESS_REG((Base + CAN_IF1DA1_R)) |= ((MsgObject -> Msg_Data[1]) << 8);
    ACCESS_REG((Base + CAN_IF1DA2_R)) = (MsgObject -> Msg_Data[2]);
    ACCESS_REG((Base + CAN_IF1DA2_R)) |= ((MsgObject -> Msg_Data[3]) << 8);
    ACCESS_REG((Base + CAN_IF1DB1_R)) = (MsgObject -> Msg_Data[4]);
    ACCESS_REG((Base + CAN_IF1DB1_R)) |= ((MsgObject -> Msg_Data[5]) << 8);
    ACCESS_REG((Base + CAN_IF1DB2_R)) = (MsgObject -> Msg_Data[6]);
    ACCESS_REG((Base + CAN_IF1DB2_R)) |= ((MsgObject -> Msg_Data[7]) << 8);

    //Request transmission of this message object and Set the NEWDATA Bit
    //Look up datasheet page 17.3.5
    ACCESS_REG( (CAN0 + CAN_IF1MCTL_R) ) |= (CAN_IF1MCTL_TXRQST | CAN_IF1MCTL_NEWDAT);

    //Write Message number into MNUM field to start transfer
    ACCESS_REG((Base + CAN_IF1CRQ_R)) = ObjID;

}

/*********************************************************************************************************/
/********************************               CAN_Read            **************************************/
/*********************************************************************************************************/

tCANReadRXData CAN_Read(Msg_Obj_ID ObjID){
    return ReceivedData[ObjID-1];
}
/*
 * =================================================================================================
 * ************************************************************************************************
 * ************************************************************************************************
 * =================================================================================================
 */
// flags -> CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS

void CAN_Int_Enable (CAN_Base Base, uint32 ui32IntFlags){

    if(Base == CAN0){
        NVIC_EN1_R |= (1<<7);
    }else if(Base == CAN1){
        NVIC_EN1_R |= (1<<8);
    }

    SET_BIT((Base+ CAN_CTL_R) , ui32IntFlags);

}


/*
 * =================================================================================================
 * ************************************************************************************************
 * ************************************************************************************************
 * =================================================================================================
 */

// Will be Edited

void CAN0_ISR(){
    if(BIT_IS_SET((CAN0 + CAN_MSG1INT_R), 1 << (Msg_Obj_3-1))){
            CAN0_IF2CMSK_R = 0x007F;
            CAN_Message_Get(CAN0, Msg_Obj_3, &ReceivedData[1], TRUE);
            CLR_BIT((CAN0+ CAN_STS_R), CAN_STS_RXOK);
    }

    if(BIT_IS_SET((CAN0 + CAN_MSG1INT_R), 1 << (Msg_Obj_4-1))){
            CAN0_IF2CMSK_R = 0x007F;
            CAN_Message_Get(CAN0, Msg_Obj_4, &ReceivedData[0], TRUE);
            CLR_BIT((CAN0 + CAN_STS_R), CAN_STS_RXOK);
    }


    if(BIT_IS_SET((CAN0 + CAN_MSG1INT_R), 1 << (Msg_Obj_1-1))){
            CLR_BIT((CAN0 + CAN_IF1MCTL_R), CAN_IF1MCTL_INTPND);
            CLR_BIT((CAN0 + CAN_STS_R), CAN_STS_TXOK);
    }
     if(BIT_IS_SET((CAN0 + CAN_MSG1INT_R), 1 << (Msg_Obj_2-1))){
            CLR_BIT((CAN0 + CAN_IF1MCTL_R), CAN_IF1MCTL_INTPND);
            CLR_BIT((CAN0 + CAN_STS_R), CAN_STS_TXOK);
    }
}


void CAN1_ISR(){
    if(BIT_IS_SET((CAN1 + CAN_MSG1INT_R), 1 << (Msg_Obj_3-1))){
            CAN1_IF2CMSK_R = 0x007F;
            CAN_Message_Get(CAN1, Msg_Obj_3, &ReceivedData[2], TRUE);
            CLR_BIT((CAN1 + CAN_STS_R), CAN_STS_RXOK);
    }

    if(BIT_IS_SET((CAN1 + CAN_MSG1INT_R), 1 << (Msg_Obj_4-1))){
            CAN1_IF2CMSK_R = 0x007F;
            CAN_Message_Get(CAN1, Msg_Obj_4, &ReceivedData[3], TRUE);
            CLR_BIT((CAN1 + CAN_STS_R), CAN_STS_RXOK);
    }


    if(BIT_IS_SET((CAN1 + CAN_MSG1INT_R), 1 << (Msg_Obj_1-1))){
            CLR_BIT((CAN1 + CAN_IF1MCTL_R), CAN_IF1MCTL_INTPND);
            CLR_BIT((CAN1 + CAN_STS_R), CAN_STS_TXOK);
    }
     if(BIT_IS_SET((CAN1 + CAN_MSG1INT_R), 1 << (Msg_Obj_2-1))){
            CLR_BIT((CAN1 + CAN_IF1MCTL_R), CAN_IF1MCTL_INTPND);
            CLR_BIT((CAN1 + CAN_STS_R), CAN_STS_TXOK);
    }

}
