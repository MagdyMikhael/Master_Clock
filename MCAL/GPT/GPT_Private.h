/*
 * TIMER_Private.h
 *
 *  Created on: Aug 19, 2020
 *      Author: Eng.Magdy_2
 */

#ifndef MCAL_GPT_GPT_PRIVATE_H_
#define MCAL_GPT_GPT_PRIVATE_H_

/*============================================================*/
/*==========               includes                 ==========*/
/*============================================================*/
#include <UTL/STD_Types.h>
#include "tm4c123gh6pm.h"

/*============================================================*/
/*==========              Definitions               ==========*/
/*============================================================*/


/*============================================================*/
/*==========        Registers Definitions           ==========*/
/*============================================================*/


//sysctl reg
#define SYSCTL_RCGCTIMER 0x400FE604UL




//Offsets of registers
#define GPTMCTL_R       0x00C
#define GPTMCFG_R       0x000
#define GPTMTAMR_R      0x004
#define GPTMTBMR_R      0x008
#define GPTMTAILR_R     0x028
#define GPTMTBILR_R     0x02C
#define GPTMIMR_R       0x018
#define GPTMICR_R       0x024

#endif /* MCAL_GPT_GPT_PRIVATE_H_ */
