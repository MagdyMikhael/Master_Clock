/*
 * Real_Time.h
 *
 *  Created on: Aug 19, 2020
 *      Author: Eng.Magdy_2
 */

#ifndef HELPER_TASKS_REAL_TIME_REAL_TIME_H_
#define HELPER_TASKS_REAL_TIME_REAL_TIME_H_

/*============================================================*/
/*==========               includes                 ==========*/
/*============================================================*/
#include <MCAL/SysTick/SysTick.h>

/*============================================================*/
/*==========              Definitions               ==========*/
/*============================================================*/
#define Clock_Mode                  0x1
#define Stop_Watch_Mode_Up          0x2
#define Stop_Watch_Mode_Down        0x3

/*============================================================*/
/*==========              ProtoTypes                ==========*/
/*============================================================*/
void RealTime_Init(void);

//just called from communication task
void RealTime_Sync(uint8 arr[6]);
void Set_StopWatchValue(uint8  val);


//called from IR Task
void Set_Time_Mode(uint8 mode);

uint8 Get_Time_Mode(void);



void Stop_Watch_Start(void);
void Stop_Watch_Pause(void);
void Stop_Watch_Stop(void);

boolean Get_StopWatch_Status(void);

//get functions
uint8 Get_Sec_L(void);
uint8 Get_Sec_H(void);
uint8 Get_Min_L(void);
uint8 Get_Min_H(void);
uint8 Get_Hur_L(void);
uint8 Get_Hur_H(void);


#endif /* HELPER_TASKS_REAL_TIME_REAL_TIME_H_ */
