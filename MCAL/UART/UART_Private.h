/*
 * UART_Private.h
 *
 *  Created on: Nov 17, 2018
 *      Author: eng-magdy
 */

#ifndef MCAL_UART_UART_PRIVATE_H_
#define MCAL_UART_UART_PRIVATE_H_
/*============================================================*/
/*==========               includes                 ==========*/
/*============================================================*/
#include <UTL/STD_Types.h>


/*============================================================*/
/*==========        Registers Definitions           ==========*/
/*============================================================*/
#define SYSCTL_RCGCUART 0x400FE618

typedef enum{
    Uart0_base = 0x4000C000,
    Uart1_base = 0x4000D000,
    Uart2_base = 0x4000E000,
    Uart3_base = 0x4000F000,
    Uart4_base = 0x40010000,
    Uart5_base = 0x40011000,
    Uart6_base = 0x40012000,
    Uart7_base = 0x40013000
}Uart_Base;


//registers index
#define UART_DR_R       0x000
#define UART_FR_R       0x018
#define UART_IBRD_R     0x024
#define UART_FBRD_R     0x028
#define UART_LCRH_R     0x02C
#define UART_CTL_R      0x030
#define UART_IM_R       0x038
#define UART_ICR_R      0x044
#define UART_CC_R       0xFC8

#endif /* MCAL_UART_UART_PRIVATE_H_ */
