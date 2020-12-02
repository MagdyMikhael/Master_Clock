/*
 * GPIO_Private.h
 *
 *  Created on: Nov 18, 2018
 *      Author: eng-magdy
 */

#ifndef MCAL_GPIO_GPIO_PRIVATE_H_
#define MCAL_GPIO_GPIO_PRIVATE_H_
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
typedef enum{
    GPIO_A = 0x40004000,
    GPIO_B = 0x40005000,
    GPIO_C = 0x40006000,
    GPIO_D = 0x40007000,
    GPIO_E = 0x40024000,
    GPIO_F = 0x40025000
}GPIO_Base;

#define SYSCTL_RCGCGPIO 0x400FE608


#define GPIO_DATA_R         0x3FC
#define GPIO_DIR_R          0x400
#define GPIO_AFSEL_R        0x420
#define GPIO_PUR_R          0x510
#define GPIO_DEN_R          0x51C
#define GPIO_LOCK_R         0x520
#define GPIO_CR_R           0x524
#define GPIO_PCTL_R         0x52C


#endif /* MCAL_GPIO_GPIO_PRIVATE_H_ */
