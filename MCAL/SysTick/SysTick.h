#ifndef Systick_H_
#define Systick_H_

/*============================================================*/
/*==========               includes                 ==========*/
/*============================================================*/
#include <MCAL/GPIO/GPIO_CFG.h>
#include <MCAL/GPIO/GPIO_Interface.h>
#include <UTL/STD_Types.h>
#include <UTL/Common_Func.h>
#include <UTL/utilites.h>
#include "tm4c123gh6pm.h"
#include "stdio.h"
/*============================================================*/
/*==========              Definitions               ==========*/
/*============================================================*/

#define NVIC_ST_CTRL 0xE000E010ul
//PreScaler definition

//#define No_PreS 1UL
//#define PreS_2 2UL
//#define PreS_4 4UL
//#define PreS_100 100UL
#define PreS_1000 1000UL
//#define PreS_M 1000000UL

////////////////////////////////////////////////////////


//STCTRL PINs
#define Enable   0
#define Inten     1
#define CLK_SRC 2
#define Count     16

/*============================================================*/
/*==========              ProtoTypes                ==========*/
/*============================================================*/


void SysTick_Init(void(*func)(void));
void Systick_PassFunc(void(*func)(void));




#endif  //Systick_H_
