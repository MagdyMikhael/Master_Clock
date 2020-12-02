/*
 * Seven_Seg_CFG.h
 *
 *  Created on: Aug 10, 2020
 *      Author: Eng.Magdy_2
 */

#ifndef HAL_7SEG_SEVEN_SEG_CFG_H_
#define HAL_7SEG_SEVEN_SEG_CFG_H_

/*============================================================*/
/*==========               includes                 ==========*/
/*============================================================*/
#include <UTL/STD_Types.h>
#include <MCAL/GPIO/GPIO_CFG.h>
#include <MCAL/GPIO/GPIO_Interface.h>


/*============================================================*/
/*==========              Definitions               ==========*/
/*============================================================*/

// 7-SEG 1 PINs
#define S_SEG1_P0   PF3
#define S_SEG1_P1   PF0
#define S_SEG1_P2   PF1
#define S_SEG1_P3   PF2

// 7-SEG 2 PINs
#define S_SEG2_P0   PE0
#define S_SEG2_P1   PE3
#define S_SEG2_P2   PE2
#define S_SEG2_P3   PE1

// 7-SEG 3 PINs
#define S_SEG3_P0   PC4
#define S_SEG3_P1   PC7
#define S_SEG3_P2   PC6
#define S_SEG3_P3   PC5

// 7-SEG 4 PINs
#define S_SEG4_P0   PD3
#define S_SEG4_P1   PD0
#define S_SEG4_P2   PD1
#define S_SEG4_P3   PD2
/*============================================================*/
/*==========         Structures&Enumurations        ==========*/
/*============================================================*/

typedef struct{
    uint8 p1;
    uint8 p2;
    uint8 p3;
    uint8 p4;
}S_Seg;


/*============================================================*/
/*==========              ProtoTypes                ==========*/
/*============================================================*/
void S_Seg_Init(void);
void S_Seg_Display(uint8 ML,uint8 MH,uint8 HL,uint8 HH);

#endif /* HAL_7SEG_SEVEN_SEG_CFG_H_ */
