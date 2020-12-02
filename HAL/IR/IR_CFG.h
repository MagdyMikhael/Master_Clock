/*
 * IR_CFG.h
 *
 *  Created on: Aug 11, 2020
 *      Author: Eng.Magdy_2
 */

#ifndef HAL_IR_RECEIVER_IR_CFG_H_
#define HAL_IR_RECEIVER_IR_CFG_H_


/*============================================================*/
/*==========               includes                 ==========*/
/*============================================================*/
#include <UTL/STD_Types.h>
#include <MCAL/GPIO/GPIO_CFG.h>
#include <MCAL/GPIO/GPIO_Interface.h>
#include <Helper_Tasks/Timer_Counter/TC_Cfg.h>

/*============================================================*/
/*==========              Definitions               ==========*/
/*============================================================*/
#define IR_PIN PD6


/*============================================================*/
/*==========              ProtoTypes                ==========*/
/*============================================================*/
void IR_Receiver_Init(uint8 IPin);
void IR_Receiver_Analysis(uint8 IPin,uint16 * arr);
uint64 IR_Receiver_Read(uint8 IPin);




#endif /* HAL_IR_RECEIVER_IR_CFG_H_ */
