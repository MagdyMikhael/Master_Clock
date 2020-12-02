/*
 * TIMER_Cfg.h
 *
 *  Created on: Aug 19, 2020
 *      Author: Eng.Magdy_2
 */

#ifndef MCAL_GPT_GPT_CFG_H_
#define MCAL_GPT_GPT_CFG_H_

/*============================================================*/
/*==========               includes                 ==========*/
/*============================================================*/
#include <MCAL/GPT/GPT_Private.h>
#include <MCAL/GPT/GPT_Interface.h>
#include <UTL/STD_Types.h>
#include <UTL/Common_Func.h>
#include <UTL/utilites.h>
#include "tm4c123gh6pm.h"

/*============================================================*/
/*==========              Definitions               ==========*/
/*============================================================*/
//timers sysctl offsets
#define T0 0
#define T1 1
#define T2 2
#define T3 3
#define T4 4
#define T5 5


//timer mode
#define Periodic_Mode 0x11

#define T_A 1
#define T_B 2

/*============================================================*/
/*==========         Structures&Enumurations        ==========*/
/*============================================================*/
//base of timers
typedef enum{
    TIMER0 = 0x40030000,
    TIMER1 = 0x40031000,
    TIMER2 = 0x40032000,
    TIMER3 = 0x40033000,
    TIMER4 = 0x40034000,
    TIMER5 = 0x40035000
}GPT_Base;

typedef enum{
    T0A_TASK=0,
    T0B_TASK,
    T1A_TASK,
    T1B_TASK,
    T2A_TASK,
    T2B_TASK,
    T3A_TASK,
    T3B_TASK,
    T4A_TASK,
    TAB_TASK,
    T5A_TASK,
    T5B_TASK

}Periodic_Task_Num;



typedef struct{
    uint8 num;
    uint8 mode;
    GPT_Base base;
    uint32   EN_PIN;
    uint32 T_Val;
    IRQn_Type irqn_Type;
    void (*P_Task)(void);
    Periodic_Task_Num P_TaskNum;
}GPT;






/*============================================================*/
/*==========              ProtoTypes                ==========*/
/*============================================================*/
void GPT_Init(GPT s_GPT);


#endif /* MCAL_GPT_GPT_CFG_H_ */
