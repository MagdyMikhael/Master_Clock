/*
 * DIP_SW_CFG.h
 *
 *  Created on: Aug 23, 2020
 *      Author: Eng.Magdy_2
 */

#ifndef HAL_DIP_SW_DIP_SW_CFG_H_
#define HAL_DIP_SW_DIP_SW_CFG_H_

/*============================================================*/
/*==========               includes                 ==========*/
/*============================================================*/
#include <UTL/STD_Types.h>
#include <MCAL/GPIO/GPIO_CFG.h>
#include <MCAL/GPIO/GPIO_Interface.h>


/*============================================================*/
/*==========              Definitions               ==========*/
/*============================================================*/
#define SW1                         PA2
#define SW2                         PA3
#define SW3                         PA4
#define SW4                         PA5
#define SW5                         PA6
#define SW6                         PA7
/*============================================================*/
/*==========              ProtoTypes                ==========*/
/*============================================================*/

void DIP_SW_Init(void);
uint8 DIP_SW_Read(void);



#endif /* HAL_DIP_SW_DIP_SW_CFG_H_ */
