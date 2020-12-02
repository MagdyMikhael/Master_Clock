/*
 * TC_Prog.c
 *
 *  Created on: Aug 19, 2020
 *      Author: Eng.Magdy_2
 */


/*============================================================*/
/*==========               includes                 ==========*/
/*============================================================*/
#include <Helper_Tasks/Timer_Counter/TC_Cfg.h>
/*============================================================*/
/*==========              GlobalVars                ==========*/
/*============================================================*/
static uint32 Micro_Count = 0;
static uint8 Display_Count = 0;
/*============================================================*/
/*==========              ProtoTypes                ==========*/
/*============================================================*/
void Time_Micro_Count(void);
void Display_Time_Count(void);


/*============================================================*/
/*==========             Functions Bodies           ==========*/
/*============================================================*/

//MicroSecond Functions

void MicroS_Init(void){
    // define the stucture for Timer0A
    GPT s={T0,Periodic_Mode,TIMER0,T_A,Micro_Count_Reg_Val,TIMER0A_IRQn,&Time_Micro_Count,T0A_TASK};
    //call init function and pass structure to it
    GPT_Init(s);
}


void MicroS_Set(uint32 uS){
    Micro_Count=uS;
}


uint32 MicroS_Get(void){

    return Micro_Count;
}

void Time_Micro_Count(void){
    Micro_Count++;
    if(Micro_Count == Million){
        Micro_Count = 0;
    }
}
/*
 *******************************************************************************************
 *******************************************************************************************
 *******************************************************************************************
 */

//Display timers
void Display_Timer_Init(void){
    /*
    // define the stucture for Timer0A
    GPT s={T1,Periodic_Mode,TIMER1,T_A,Display_Count_Reg_Val,TIMER1A_IRQn,&Display_Time_Count,T1A_TASK};
    //call init function and pass structure to it
    GPT_Init(s);
*/


}


boolean Display_Ready(void){
    boolean x = FALSE;
    if(Display_Count == 200){
        x = TRUE;
    }
    return x;
}

void Display_Time_Count(void){
    Display_Count = Display_Count + 5;
    if(Display_Count > 1000){
        Display_Count = 1;
    }

}
/*
void SysTick_Delay_ms(uint16 time){
    Systick_Reset(&im);
    boolean delay=TRUE;
    while(delay){
        if(im==time){
            delay=FALSE;
        }
    }
    im=1;

}


void SysTick_Delay_us(uint16 time){
    Systick_Reset(&iu);

    while(iu < time);
    iu=1;

}
void Systick_Reset(uint32 * i){
    *i = 1;
}
*/
