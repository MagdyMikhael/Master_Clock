/*
 * Password_Task.c
 *
 *  Created on: Aug 23, 2020
 *      Author: Eng.Magdy_2
 */


/*============================================================*/
/*==========               includes                 ==========*/
/*============================================================*/
#include <AppLayer/Clock_Configuration_Task/Clock_Configuration_Task.h>


/*============================================================*/
/*==========             Functions Bodies           ==========*/
/*============================================================*/
void Clock_Configuration_Init(void){
    DIP_SW_Init();
}


// the operation depend on communication stack
