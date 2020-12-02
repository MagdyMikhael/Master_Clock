/*
 * LED_Prog.c
 *
 *  Created on: Aug 16, 2020
 *      Author: Eng.Magdy_2
 */

/*============================================================*/
/*==========               includes                 ==========*/
/*============================================================*/
#include <HAL/LED/LED_CFG.h>


/*============================================================*/
/*==========             Functions Bodies           ==========*/
/*============================================================*/
void LED_Init(void){

    GPIO_WritePinDir(LED_Clock, STD_HIGH);
    GPIO_WritePinDir(LED_StopWatchOn, STD_HIGH);
    GPIO_WritePinDir(LED_StopWatchPaused, STD_HIGH);

}


void LED_On(uint8 PIN){
    GPIO_WritePinVal(PIN,STD_HIGH);
}


void LED_Off(uint8 PIN){
    GPIO_WritePinVal(PIN,STD_LOW);
}


void LED_TOGGLE(uint8 PIN){
    GPIO_TogglePinVal(PIN);
}


