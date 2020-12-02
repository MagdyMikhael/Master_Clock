/*
 * TC_Cfg.h
 *
 *  Created on: Aug 19, 2020
 *      Author: Eng.Magdy_2
 */

#ifndef HELPER_TASKS_TIMER_COUNTER_TC_CFG_H_
#define HELPER_TASKS_TIMER_COUNTER_TC_CFG_H_

/*============================================================*/
/*==========               includes                 ==========*/
/*============================================================*/
#include <MCAL/GPT/GPT_Cfg.h>
#include <UTL/STD_Types.h>

/*============================================================*/
/*==========              Definitions               ==========*/
/*============================================================*/
#define Micro_Count_Reg_Val         79UL
#define Million                     1000000UL
#define Display_Count_Reg_Val       400000UL
/*============================================================*/
/*==========              ProtoTypes                ==========*/
/*============================================================*/
void MicroS_Init(void);
void MicroS_Set(uint32 uS);
uint32 MicroS_Get(void);

void Display_Timer_Init(void);

boolean Display_Ready(void);

#endif /* HELPER_TASKS_TIMER_COUNTER_TC_CFG_H_ */
