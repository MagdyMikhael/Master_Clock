/*
 * Seven_Seg_Prog.c
 *
 *  Created on: Aug 11, 2020
 *      Author: Eng.Magdy_2
 */

/*============================================================*/
/*==========               includes                 ==========*/
/*============================================================*/
#include <HAL/7Seg/Seven_Seg_CFG.h>

/*============================================================*/
/*==========              ProtoTypes                ==========*/
/*============================================================*/
void S_Seg_Write(uint8 SegNum,uint8 Data);
/*============================================================*/
/*==========              GlobalVars                ==========*/
/*============================================================*/



S_Seg s_Seg [4] ={
                 {S_SEG1_P0,S_SEG1_P1,S_SEG1_P2,S_SEG1_P3},
                 {S_SEG2_P0,S_SEG2_P1,S_SEG2_P2,S_SEG2_P3},
                 {S_SEG3_P0,S_SEG3_P1,S_SEG3_P2,S_SEG3_P3},
                 {S_SEG4_P0,S_SEG4_P1,S_SEG4_P2,S_SEG4_P3}

};
/*============================================================*/
/*==========            Static Functions            ==========*/
/*============================================================*/


/*============================================================*/
/*==========             Functions Bodies           ==========*/
/*============================================================*/

void S_Seg_Init(void){
    uint8 i = 0;
    for(i=0 ; i<4 ; i++){
        GPIO_WritePinDir(s_Seg[i].p1, STD_HIGH);
        GPIO_WritePinDir(s_Seg[i].p2, STD_HIGH);
        GPIO_WritePinDir(s_Seg[i].p3, STD_HIGH);
        GPIO_WritePinDir(s_Seg[i].p4, STD_HIGH);
    }
}



void S_Seg_Write(uint8 SegNum,uint8 Data){
    //Data = Data & 0x0f;

    GPIO_WritePinVal(s_Seg[SegNum].p1,GET_DATA_BIT(Data,0));
    GPIO_WritePinVal(s_Seg[SegNum].p2,GET_DATA_BIT(Data,1));
    GPIO_WritePinVal(s_Seg[SegNum].p3,GET_DATA_BIT(Data,2));
    GPIO_WritePinVal(s_Seg[SegNum].p4,GET_DATA_BIT(Data,3));
}

void S_Seg_Display(uint8 ML,uint8 MH,uint8 HL,uint8 HH){
    S_Seg_Write(0, ML);
    S_Seg_Write(1, MH);
    S_Seg_Write(2, HL);
    S_Seg_Write(3, HH);
}
