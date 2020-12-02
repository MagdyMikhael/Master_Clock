/*
 * Common_Func.c
 *
 *  Created on: Nov 17, 2018
 *      Author: eng-magdy
 */

/*============================================================*/
/*==========               includes                 ==========*/
/*============================================================*/
#include <UTL/Common_Func.h>
#include <UTL/utilites.h>


/*============================================================*/
/*==========        Registers Definitions           ==========*/
/*============================================================*/
//Array of Enable interrupt registers
volatile uint32 * NVIC_Enable_Rs[5]={(volatile uint32*) 0xE000E100UL,
                                     (volatile uint32*) 0xE000E104UL,
                                     (volatile uint32*) 0xE000E108UL,
                                     (volatile uint32*) 0xE000E10CUL,
                                     (volatile uint32*) 0xE000E110UL
};

//Array of Disable interrupt registers
volatile uint32 * NVIC_Disable_Rs[5]={(volatile uint32*) 0xE000E180UL,
                                      (volatile uint32*) 0xE000E184UL,
                                      (volatile uint32*) 0xE000E188UL,
                                      (volatile uint32*) 0xE000E18CUL,
                                      (volatile uint32*) 0xE000E190UL,

};


/*============================================================*/
/*==========             Functions Bodies           ==========*/
/*============================================================*/
void DisableInterrupts(void){__asm (" CPSID  I\n");}
void EnableInterrupts(void){__asm  (" CPSIE  I\n");}

void NVIC_EnableIRQ(uint16 IRQNum){
    uint8 Intr_Position=IRQNum/32;
    uint8 Intr_Index=IRQNum%32;
    SET_D_BIT(*NVIC_Enable_Rs[Intr_Position],Intr_Index);

}


void NVIC_DisableIRQ(uint16 IRQNum){
    uint8 Intr_Position=IRQNum/32;
    uint8 Intr_Index=IRQNum%32;
    SET_D_BIT(*NVIC_Disable_Rs[Intr_Position],Intr_Index);
}
