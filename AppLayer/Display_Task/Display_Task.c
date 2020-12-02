/*
 * Display_Task.c
 *
 *  Created on: Aug 19, 2020
 *      Author: Eng.Magdy_2
 */
/*============================================================*/
/*==========               includes                 ==========*/
/*============================================================*/
#include <AppLayer/Display_Task/Display_Task.h>

/*============================================================*/
/*==========              ProtoTypes                ==========*/
/*============================================================*/
void Start_Display(void);
/*============================================================*/
/*==========             Functions Bodies           ==========*/
/*============================================================*/
void Init_Display_Task(void){

    //init 7-seg
    S_Seg_Init();

    //init Leds
    LED_Init();

    //init real time
    RealTime_Init();

    //Pass operation to systick
    Systick_PassFunc(&Start_Display);






}


void Start_Display(void){
    //Do Task

    //7-seg show
    S_Seg_Display(Get_Sec_L(), Get_Sec_H(), Get_Min_L(), Get_Min_H());


    //leds show
    if(Get_Time_Mode() == Clock_Mode){
        LED_TOGGLE(LED_Clock);
    }else if((Get_Time_Mode()==Stop_Watch_Mode_Up)||(Get_Time_Mode()==Stop_Watch_Mode_Down)){
        if(Get_StopWatch_Status()==TRUE){
            LED_On(LED_StopWatchOn);
            LED_Off(LED_StopWatchPaused);
        }else{
            LED_Off(LED_StopWatchOn);
            LED_On(LED_StopWatchPaused);
        }
    }else{

    }

}

