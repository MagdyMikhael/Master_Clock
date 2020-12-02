/*
 * Real_Time.c
 *
 *  Created on: Aug 19, 2020
 *      Author: Eng.Magdy_2
 */

/*============================================================*/
/*==========               includes                 ==========*/
/*============================================================*/
#include <Helper_Tasks/Real_Time/Real_Time.h>


/*============================================================*/
/*==========              GlobalVars                ==========*/
/*============================================================*/

static uint8 Sec_L = 0;
static uint8 Sec_H = 0;
static uint8 Min_L = 0;
static uint8 Min_H = 0;
static uint8 Hur_L = 0;
static uint8 Hur_H = 0;

static uint8 Stop_SL = 0;
static uint8 Stop_SH = 0;
static uint8 Stop_ML = 0;
static uint8 Stop_MH = 0;
static uint8 Stop_HL = 0;
static uint8 Stop_HH = 0;
static uint8 UpCount = 0;

static uint8 Mode = Clock_Mode;
static uint8 StopWatchConst = 0;
static uint8 StopWatchOppVal = 0;

boolean Start = FALSE;
boolean Stop = TRUE;


/*============================================================*/
/*==========              ProtoTypes                ==========*/
/*============================================================*/

void RealTime_Operation(void);
/*============================================================*/
/*==========             Functions Bodies           ==========*/
/*============================================================*/
void RealTime_Init(void){
    SysTick_Init(&RealTime_Operation);

}

//will be called from communication task
void RealTime_Sync(uint8 arr[6]){
    Hur_H = arr[0];
    Hur_L = arr[1];
    Min_H = arr[2];
    Min_L = arr[3];
    Sec_H = arr[4];
    Sec_L = arr[5];

}


//static functions
///////////////////////////////////////////////////////////////////////////////////////////////
void RealTime_Operation(void){

    //real time
    if(Sec_L <= 9){Sec_L++;}
    if(Sec_L > 9 ){Sec_H++; Sec_L = 0;}
    if(Sec_H > 5 ){Min_L++; Sec_H = 0;}
    if(Min_L > 9 ){Min_H++; Min_L = 0;}
    if(Min_H > 5 ){Hur_L++; Min_H = 0;}
    if((Hur_L > 9) && (Hur_H < 1))
    {
        Hur_L = 0;
        Hur_H++;
    }else if((Hur_L > 2) && (Hur_H == 1))
    {
        Hur_L = 1;
        Hur_H++;
    }
    if(Hur_H > 1 ){Hur_H = 0;}


    //if Stop watch
    ////////////////////////////////////////////////////////////////////////////////////////
    if(Start == TRUE){
        if(Mode == Stop_Watch_Mode_Up){
            Stop_SL++;
            if(Stop_SL > 9){Stop_SL = 0; Stop_SH++;}
            if(Stop_SH > 5){
                Stop_SH = 0; UpCount++;
            }

            Stop_ML = ( UpCount % 60 ) % 10 ;
            Stop_MH = ( UpCount % 60 ) / 10 ;
            Stop_HL = ( UpCount / 60 ) % 10 ;
            Stop_HH = ( UpCount / 60 ) / 10 ;
            if(StopWatchConst == UpCount){
                Stop_Watch_Stop();
            }
        }else if(Mode == Stop_Watch_Mode_Down){
            if(StopWatchOppVal > 0){
                Stop_ML = ( StopWatchOppVal % 60 ) % 10 ;
                Stop_MH = ( StopWatchOppVal % 60 ) / 10 ;
                Stop_HL = ( StopWatchOppVal / 60 ) % 10 ;
                Stop_HH = ( StopWatchOppVal / 60 ) / 10 ;
                Stop_SL++;
                if(Stop_SL > 9){
                    Stop_SL = 0;
                    Stop_SH++;
                }

                if(Stop_SH > 5){
                    Stop_SH = 0;
                    StopWatchOppVal--;
                }

            }else{
                Stop_Watch_Stop();
            }

        }else{
            Mode = Clock_Mode;
        }
    }

    if(Stop == TRUE){
        Stop_SL = 0;
        Stop_SH = 0;
        Stop_ML = 0;
        Stop_MH = 0;
        Stop_HL = 0;
        Stop_HH = 0;

        Start = FALSE;
        Stop = FALSE;
    }


}



//called from Ir task
void Set_Time_Mode(uint8 mode){
    Mode = mode;
}


uint8 Get_Time_Mode(void){
    return Mode;
}

//called from communication task
void Set_StopWatchValue(uint8  val){
    StopWatchConst = val;

}

//Get functions
// will called from 7-Seg task
///////////////////////////////////////////////////////////////////////////////////////////////
uint8 Get_Sec_L(void){
    uint8 x = 0;
    if(Mode == Clock_Mode){
        x = Sec_L;
    }else if((Mode == Stop_Watch_Mode_Up) || (Mode == Stop_Watch_Mode_Down)){
        x = Stop_SL;
    }
    return x;
}

uint8 Get_Sec_H(void){
    uint8 x = 0;
    if(Mode == Clock_Mode){
        x = Sec_H;
    }else if((Mode == Stop_Watch_Mode_Up) || (Mode == Stop_Watch_Mode_Down)){
        x = Stop_SH;
    }
    return x;
}

uint8 Get_Min_L(void){
    uint8 x = 0;
    if(Mode == Clock_Mode){
        x = Min_L;
    }else if((Mode == Stop_Watch_Mode_Up) || (Mode == Stop_Watch_Mode_Down)){
        x = Stop_ML;
    }
    return x;
}

uint8 Get_Min_H(void){
    uint8 x = 0;
    if(Mode == Clock_Mode){
        x = Min_H;
    }else if((Mode == Stop_Watch_Mode_Up) || (Mode == Stop_Watch_Mode_Down)){
        x = Stop_MH;
    }
    return x;
}

uint8 Get_Hur_L(void){
    uint8 x = 0;
    if(Mode == Clock_Mode){
        x = Hur_L;
    }else if((Mode == Stop_Watch_Mode_Up) || (Mode == Stop_Watch_Mode_Down)){
        x = Stop_HL;
    }
    return x;
}

uint8 Get_Hur_H(void){
    uint8 x = 0;
    if(Mode == Clock_Mode){
        x = Hur_H;
    }else if((Mode == Stop_Watch_Mode_Up) || (Mode == Stop_Watch_Mode_Down)){
        x = Stop_HH;
    }
    return x;
}


////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

void Stop_Watch_Start(void){
    Start = TRUE;
}
void Stop_Watch_Pause(void){
    Start = FALSE;
}
void Stop_Watch_Stop(void){
    Start = FALSE;
    Stop = TRUE;
    StopWatchOppVal = StopWatchConst;

    Mode = Clock_Mode;
}


boolean Get_StopWatch_Status(void){
    return Start;
}
