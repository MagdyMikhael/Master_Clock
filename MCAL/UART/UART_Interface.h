/*
 * UART_Interface.h
 *
 *  Created on: Nov 17, 2018
 *      Author: eng-magdy
 */


//UART Modules Pins
//UART0  TX  PA1     RX  PA0
//UART1  TX          RX
//UART2  TX  PD7     RX  PD6
//UART3  TX  PC7     RX  PC6
//UART4  TX  PC5     RX  PC4
//UART5  TX  PE5     RX  PE4
//UART6  TX  PD5     RX  PD4
//UART7  TX  PE1     RX  PE0

#ifndef MCAL_UART_UART_INTERFACE_H_
#define MCAL_UART_UART_INTERFACE_H_





/*============================================================*/
/*==========               includes                 ==========*/
/*============================================================*/


/*============================================================*/
/*==========              Definitions               ==========*/
/*============================================================*/
//RCGCUART PINs
#define R0 0
#define R1 1
#define R2 2
#define R3 3
#define R4 4
#define R5 5
#define R6 6
#define R7 7

//UARTCTL PINs
#define  UARTEN 0
#define  LPE 7
#define  TXE 8
#define  RXE 9

//UARTFR PINs
#define CTS 0
#define BUSY 3
#define RXFE 4
#define TXFF 5
#define RXFF 6
#define TXFE 7

//UARTRIS PINs
#define RTRIS 6

//UART’IS PINs
#define RXMIS 6

//
#define RXIM 4
#define RXIC (1UL<<4)
#define FEN 4
/*============================================================*/
#define Uart0 0
#define Uart1 1
#define Uart2 2
#define Uart3 3
#define Uart4 4
#define Uart5 5
#define Uart6 6
#define Uart7 7
/*============================================================*/
#define PORTA 0
#define PORTB 1
#define PORTC 2
#define PORTD 3
#define PORTE 4
#define PORTF 5
/*============================================================*/
#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7
/*============================================================*/




/*============================================================*/
/*==========         Structures&Enumurations        ==========*/
/*============================================================*/
typedef struct {
  uint8 UART_NUM;
  uint8 PORT_NUM;
  uint8 URx;
  uint8 UTx;
  uint8 PCLR_Rx;
  uint8 PCLR_Tx;
}UART_STRUCT;




#endif /* MCAL_UART_UART_INTERFACE_H_ */
