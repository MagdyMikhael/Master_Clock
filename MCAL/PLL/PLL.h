/*
 * PLL.h
 *
 *  Created on: Nov 1, 2018
 *      Author: eng-magdy
 */

#ifndef MCAL_PLL_PLL_H_
#define MCAL_PLL_PLL_H_
/*============================================================*/
/*==========               includes                 ==========*/
/*============================================================*/
#include <UTL/STD_Types.h>
#include <UTL/utilites.h>
#include "tm4c123gh6pm.h"
/*============================================================*/
/*==========              ProtoTypes                ==========*/
/*============================================================*/
void PLL_Enable(void);

/*============================================================*/
/*==========              definitions               ==========*/
/*============================================================*/
#define XTAL_Value (uint8_t)(0x15<<6)
#define SYSDIV2_Value (uint8_t)(4<<22)

//RCC2 BITs

#define BYPASS2 11U
#define PWRDN2  13U
#define DIV400  30U
#define USERCC2 31UL


//SYSCTL_RIS_R BITs
#define PLLLRIS 6U

#endif /* MCAL_PLL_PLL_H_ */
