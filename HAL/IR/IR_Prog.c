/*
 * IR_Prog.c
 *
 *  Created on: Aug 11, 2020
 *      Author: Eng.Magdy_2
 */


/*============================================================*/
/*==========               includes                 ==========*/
/*============================================================*/
#include <HAL/IR/IR_CFG.h>

/*============================================================*/
/*==========              ProtoTypes                ==========*/
/*============================================================*/

/*============================================================*/
/*==========              GlobalVars                ==========*/
/*============================================================*/
uint64 Last_Code_Var=0;
/*============================================================*/
/*==========            Static Functions            ==========*/
/*============================================================*/


/*============================================================*/
/*==========             Functions Bodies           ==========*/
/*============================================================*/


/*
 * =============================================================
 * initialization function takes the pin number to enable it
 * =============================================================
 */
void IR_Receiver_Init(uint8 IPin){
    GPIO_WritePinDir(IPin, STD_LOW);
    MicroS_Init();
}


/*
 * =============================================================
 * analysis function takes the pin number and array to get the
 * intervals of time between the high signal and low one
 * =============================================================
 */
void IR_Receiver_Analysis(uint8 IPin,uint16 * arr){

    //initializing counter
    uint16 i = 0;

    //wait until IPin become zero
    while(GPIO_ReadPinVal(IPin)==1);

    //Start taking analysis of signal
    do{
        //setting timer to 10 uS
        MicroS_Set(10);

        //internal loop to get timerValue in uS when the signal is low
        do{
            arr[i]=MicroS_Get();

        }while((GPIO_ReadPinVal(IPin)==0)&&(arr[i]<20000));

        //setting timer to 10 uS
        MicroS_Set(10);

        //internal loop to get timerValue in uS when the signal is high
        do{
            arr[i+1]=MicroS_Get();
        }while((GPIO_ReadPinVal(IPin)==1)&&(arr[i+1]<20000));

        //increment counter by 2 elements
        i=i+2;
    }while((arr[i-2]<20000)&&(arr[i-1]<20000));
}
/*
 * =============================================================
 *
 * =============================================================
 */

uint64 IR_Receiver_Read(uint8 IPin){

    //Local variable necessary for operation like code variable
    //and counter i and array to pass for analysis function
    uint16 Code_Var = 0;
    uint16 i = 3;
    uint16 arr[128];

    //calling analysis function and pass array to it to get readings
    IR_Receiver_Analysis(IPin, arr);

    //Code of operation
    if (((arr[0]<9600)&&(arr[0]>8800))&&((arr[1]<4600)&&(arr[1]>4000)))
        {


            while (i<=128)
            {

            if ((arr[i]>100)&&(arr[i]<700))
            {
                Code_Var=(Code_Var<<1);

            }
            else if ((arr[i]>1200)&&(arr[i]<1800))
            {
                Code_Var=((Code_Var<<1)|(1));

            }
            else
            {
                break;
            }

           i=i+2;


        }
        if(Code_Var==0)
        {
            Code_Var=Last_Code_Var;
        }
        else
        {
            Last_Code_Var=Code_Var;
        }
            }
            else if(((arr[0]<9600)&&(arr[0]>8800))&&((arr[1]<2400)&&(arr[1]>1800)))
            {
                Code_Var=Last_Code_Var;
            }

            else if(((arr[0]<3930)&&(arr[0]>3330))&&((arr[1]<1880)&&(arr[1]>1280)))
            {
                while (i<=128)
                {

                    if ((arr[i]>30)&&(arr[i]<630))
                    {
                        Code_Var=(Code_Var<<1);

                    }
                    else if ((arr[i]>900)&&(arr[i]<1500))
                    {
                        Code_Var=((Code_Var<<1)|(1));

                    }
                    else
                    {
                        break;
                    }

                    i=i+2;

                }

            }
            else
            {
                Code_Var=0x00;
            }



    return Code_Var ;
}
