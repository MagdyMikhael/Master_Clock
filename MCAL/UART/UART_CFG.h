/*
 * UART_CFG.h
 *
 *  Created on: Nov 17, 2018
 *      Author: eng-magdy
 */

#ifndef MCAL_UART_UART_CFG_H_
#define MCAL_UART_UART_CFG_H_

/*============================================================*/
/*==========               includes                 ==========*/
/*============================================================*/

#include <UTL/STD_Types.h>
#include <MCAL/UART/UART_Interface.h>
#include <MCAL/UART/UART_Private.h>
#include <stdint.h>
#include <UTL/Common_Func.h>
#include <UTL/utilites.h>
#include "tm4c123gh6pm.h"
#include <MCAL/GPIO/GPIO_CFG.h>
#include <MCAL/GPIO/GPIO_Private.h>
#include "string.h"
/*============================================================*/
/*==========              BaudRates                 ==========*/
/*============================================================*/
typedef enum {
    BR_110    = 110,
    BR_300    = 300,
    BR_600    = 600,
    BR_1200   = 1200,
    BR_2400   = 2400,
    BR_4800   = 4800,
    BR_9600   = 9600,
    BR_14400  = 14400,
    BR_19200  = 19200,
    BR_28800  = 28800,
    BR_38400  = 38400,
    BR_56000  = 56000,
    BR_57600  = 57600,
    BR_115200 = 115200,
    BR_128000 = 128000,
    BR_153600 = 153600,
    BR_230400 = 230400,
    BR_256000 = 256000,
    BR_460800 = 460800,
    BR_921600 = 921600
}UART_BAUDRATE_t;

/*============================================================*/
/*==========              structures                ==========*/
/*============================================================*/
typedef struct{
    uint8 U_NUM;
    UART_BAUDRATE_t baudRate;
    Uart_Base base;
    uint8 Bit_Num;
}UART_S;


/*============================================================*/
/*==========              ProtoTypes                ==========*/
/*============================================================*/
void UART_Init(UART_S CFG_S);
void UART_Transmit(uint32 base,uint8 DATA);
uint8 UART_Recieve(uint8 U_NUM);
void UART_Write_String(Uart_Base base,char * string);
char * UART_Read_String(uint8 U_NUM );
void Clear_Buffer(uint8 U_NUM);




/*============================================================*/
/*==========              Definitions               ==========*/
/*============================================================*/

#define UARTSysClk  80000000.0f
#define ClkDiv 16.0f
#define SYS_CLOCK 0
#define WLEN 0x3
#define WLEN_SHIFT 5

//data bits num
#define _5Bits 0x0
#define _6Bits 0x1
#define _7Bits 0x2
#define _8Bits 0x3
//PCMs Definitions

#define Uart_PCM0 0
#define Uart_PCM1 4
#define Uart_PCM2 8
#define Uart_PCM3 12
#define Uart_PCM4 16
#define Uart_PCM5 20
#define Uart_PCM6 24
#define Uart_PCM7 28

//#define Uart_PCM1 5
#define Uart0_Buffer_Length 20
#define Uart1_Buffer_Length 20
#define Uart2_Buffer_Length 10
#define Uart3_Buffer_Length 20
#define Uart4_Buffer_Length 20
#define Uart5_Buffer_Length 11
#define Uart6_Buffer_Length 20
#define Uart7_Buffer_Length 20




#endif /* MCAL_UART_UART_CFG_H_ */
