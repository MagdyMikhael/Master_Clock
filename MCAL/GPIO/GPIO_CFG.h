/*
 * GPIO_CFG.h
 *
 *  Created on: Nov 20, 2018
 *      Author: eng-magdy
 */

#ifndef MCAL_GPIO_GPIO_CFG_H_
#define MCAL_GPIO_GPIO_CFG_H_

/*============================================================*/
/*==========               includes                 ==========*/
/*============================================================*/
#include <MCAL/GPIO/GPIO_Interface.h>
#include <MCAL/GPIO/GPIO_Private.h>
#include <UTL/STD_Types.h>
#include <UTL/utilites.h>
#include "tm4c123gh6pm.h"
/*============================================================*/
/*==========              ProtoTypes                ==========*/
/*============================================================*/
void GPIO_WritePinDir(uint8 PIN_NUM,uint8 Val);
void GPIO_WritePinVal(uint8 PIN_NUM,uint8 Val);
uint8 GPIO_ReadPinVal(uint8 PIN_NUM);
void GPIO_TogglePinVal(uint8 PIN_NUM);

/*============================================================*/
/*==========              Definitions               ==========*/
/*============================================================*/
#define UN_LOCK 0x4C4F434BUL;
#define CR_VALUE 0xff

#define PORT_DIR_OUT 0xff
#define PORT_DIR_IN 0x00

#define PORT_DEN 0xff

#define PORT_AFSEL 0x00

#define PORT_PUR 0xff
#endif /* MCAL_GPIO_GPIO_CFG_H_ */
