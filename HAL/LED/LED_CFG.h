/*
 * LED_CFG.h
 *
 *  Created on: Aug 16, 2020
 *      Author: Eng.Magdy_2
 */

#ifndef HAL_LED_LED_CFG_H_
#define HAL_LED_LED_CFG_H_

/*============================================================*/
/*==========               includes                 ==========*/
/*============================================================*/
#include <UTL/STD_Types.h>
#include <MCAL/GPIO/GPIO_CFG.h>
#include <MCAL/GPIO/GPIO_Interface.h>


/*============================================================*/
/*==========              Definitions               ==========*/
/*============================================================*/
#define LED_Clock                   PB6
#define LED_StopWatchOn             PB7
#define LED_StopWatchPaused         PD4
/*============================================================*/
/*==========              ProtoTypes                ==========*/
/*============================================================*/
void LED_Init(void);
void LED_On(uint8 PIN);
void LED_Off(uint8 PIN);
void LED_TOGGLE(uint8 PIN);

#endif /* HAL_LED_LED_CFG_H_ */
