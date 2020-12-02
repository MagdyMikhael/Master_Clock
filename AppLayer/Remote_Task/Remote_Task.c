/*
 * Remote_Task.c
 *
 *  Created on: Aug 11, 2020
 *      Author: Eng.Magdy_2
 */

/*============================================================*/
/*==========               includes                 ==========*/
/*============================================================*/
#include <AppLayer/Remote_Task/Remote_Task.h>


/*============================================================*/
/*==========             Functions Bodies           ==========*/
/*============================================================*/

void Remote_Task_Init(void){

   IR_Receiver_Init(IR_PIN);
}


void Remote_Task_Operation(void){
    while(1){
        uint64 x=IR_Receiver_Read(IR_PIN);
        switch (x) {

        case 0xA25D:
            //Serial.println("1");
            break;
        case 0x629D:
            //Serial.println("2");
            break;
        case 0xE21D:
            //Serial.println("3");
            break;
        case 0x22DD:
            //Serial.println("4");
            break;
        case 0x02FD:
            //Serial.println("5");
            break ;
        case 0xC23D:
            //Serial.println("6");
            break ;
        case 0xE01F:
            //Serial.println("7");
            break ;
        case 0xA857:
            //Serial.println("8");
            break ;
        case 0x906F:
            //Serial.println("9");
            break ;
        case 0x6897:
            //Serial.println("*");
            Stop_Watch_Pause();
            break ;
        case 0x9867:
            //Serial.println("0");
            break ;
        case 0xB04F:
            //Serial.println("#");
            Stop_Watch_Stop();
            break ;
        case 0x30CF:
            //Serial.println("");
            break ;
        case 0x18E7:
            //Serial.println("up");
            Set_Time_Mode(Stop_Watch_Mode_Up);
            break ;
        case 0x38C7:
            //Serial.println("ok");
            Stop_Watch_Start();
            break ;
        case 0x10EF:
            //Serial.println("<");
            break ;
        case 0x5AA5:
            //Serial.println(">");
            break ;
        case 0x42BD:
            //Serial.println("7");
            break ;
        case 0x4AB5:
            //Serial.println("down");
            Set_Time_Mode(Stop_Watch_Mode_Down);
            break ;
        case 0x52AD:
            //Serial.println("9");
            break ;
        default:
            break;

        }
    }
}

