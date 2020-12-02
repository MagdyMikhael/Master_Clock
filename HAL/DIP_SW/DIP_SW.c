/*
 * DIP_SW.c
 *
 *  Created on: Aug 23, 2020
 *      Author: Eng.Magdy_2
 */

/*============================================================*/
/*==========               includes                 ==========*/
/*============================================================*/
#include <HAL/DIP_SW/DIP_SW_CFG.h>


/*============================================================*/
/*==========             Functions Bodies           ==========*/
/*============================================================*/

void DIP_SW_Init(void){
    //define pins as input
    GPIO_WritePinDir(SW1,STD_LOW);
    GPIO_WritePinDir(SW2,STD_LOW);
    GPIO_WritePinDir(SW3,STD_LOW);
    GPIO_WritePinDir(SW4,STD_LOW);
    GPIO_WritePinDir(SW5,STD_LOW);
    GPIO_WritePinDir(SW6,STD_LOW);

}


uint8 DIP_SW_Read(void){

    //define local variables for each pin and for total data
    uint8 D1 = GPIO_ReadPinVal(SW1);
    uint8 D2 = GPIO_ReadPinVal(SW2);
    uint8 D3 = GPIO_ReadPinVal(SW3);
    uint8 D4 = GPIO_ReadPinVal(SW4);
    uint8 D5 = GPIO_ReadPinVal(SW5);
    uint8 D6 = GPIO_ReadPinVal(SW6);

    uint8 return_Data = (D1<<0)|(D2<<1)|(D3<<2)|(D4<<3)|(D5<<4)|(D6<<5);

    return return_Data;


}
