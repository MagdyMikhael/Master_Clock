/********************************************************************************
***** Includes                                                              *****
********************************************************************************/
#define    Debug
#include <MCAL/PLL/PLL.h>
#include <MCAL/UART/UART_CFG.h>
#include <MCAL/UART/UART_Interface.h>
#include <MCAL/CAN/CAN_Cfg.h>
#include <UTL/Common_Func.h>
#include <AppLayer/Display_Task/Display_Task.h>
#include <AppLayer/Remote_Task/Remote_Task.h>
#include <stdio.h>
/********************************************************************************
***** MAIN FUNCTION                                                         *****
********************************************************************************/


int main(){




    PLL_Enable();

    tCANBitClkParms BitTime = {5, 2, 2, 4};
    CAN_Cfg c={Port_E,CAN0,Real_Mode,&BitTime};

    CAN_Init(c);
    EnableInterrupts();
    //Remote_Task_Init();

    //Init_Display_Task();

    //Remote_Task_Operation();


    //UART_S s={Uart0,BR_9600,Uart0_base,_8Bits};
    //UART_Init(s);
    //UART0_DR_R |= 15;

    while(1){

        //UART_Write_String(Uart0_base, "magdy ");
        //printf("%s",UART_Read_String(Uart5));

    }
}

