/*
 * TIMER_Prog.c
 *
 *  Created on: Aug 19, 2020
 *      Author: Eng.Magdy_2
 */
/*============================================================*/
/*==========               includes                 ==========*/
/*============================================================*/
#include <MCAL/GPT/GPT_Cfg.h>

/*============================================================*/
/*==========              ProtoTypes                ==========*/
/*============================================================*/
void TIMER0A_ISR(void);
void TIMER0B_ISR(void);
void TIMER1A_ISR(void);
void TIMER1B_ISR(void);
void TIMER2A_ISR(void);
void TIMER2B_ISR(void);
void TIMER3A_ISR(void);
void TIMER3B_ISR(void);
void TIMER4A_ISR(void);
void TIMER4B_ISR(void);
void TIMER5A_ISR(void);
void TIMER5B_ISR(void);
/*============================================================*/
/*==========              GlobalVars                ==========*/
/*============================================================*/
void (*Periodic_Task[20])(void);
uint8 TIMER[6]={
                0x01,
                0x02,
                0x04,
                0x08,
                0x10,
                0x20
};


/*============================================================*/
/*==========             Functions Bodies           ==========*/
/*============================================================*/

void GPT_Init(GPT s_GPT){

    //set clock for timer module
    SET_BIT(SYSCTL_RCGCTIMER,TIMER[s_GPT.num]);


    //for periodic timer mode
    if(s_GPT.mode == Periodic_Mode){

        //disable timer before initializations
        if(s_GPT.EN_PIN == T_A){
            CLR_BIT(s_GPT.base+GPTMCTL_R,TIMER_CTL_TAEN);
        }else if(s_GPT.EN_PIN == T_B){
            CLR_BIT(s_GPT.base+GPTMCTL_R,TIMER_CTL_TBEN);
        }

        //Write the GPTM Configuration Register (GPTMCFG) with a value of 0x0000.0000.
        WRITE_REG(s_GPT.base+GPTMCFG_R,TIMER_CFG_32_BIT_TIMER);

        //Configure the TnMR field in the GPTM Timer n Mode Register (GPTMTnMR):
        //Write a value of 0x2 for Periodic mode.
        if(s_GPT.EN_PIN == T_A){
            //Configure the TnMR field in the GPTM Timer n Mode Register (GPTMTnMR):
            //Write a value of 0x2 for Periodic mode.
            WRITE_REG(s_GPT.base+GPTMTAMR_R,TIMER_TAMR_TAMR_PERIOD);

            //Load the start value into the GPTM Timer n Interval Load Register (GPTMTnILR).
            WRITE_REG(s_GPT.base+GPTMTAILR_R,s_GPT.T_Val);

            //If interrupts are required, set the appropriate bits in the GPTM Interrupt Mask Register (GPTMIMR).
            SET_BIT(s_GPT.base+GPTMIMR_R,TIMER_IMR_TATOIM);

            //Enable interrupt IRQn
            NVIC_EnableIRQ(s_GPT.irqn_Type);

            //Set the TnEN bit in the GPTMCTL register to enable the timer and start counting.
            SET_BIT(s_GPT.base+GPTMCTL_R,TIMER_CTL_TAEN);


        }else if(s_GPT.EN_PIN == T_B){
            //Configure the TnMR field in the GPTM Timer n Mode Register (GPTMTnMR):
            //Write a value of 0x2 for Periodic mode.
            WRITE_REG(s_GPT.base+GPTMTBMR_R,TIMER_TBMR_TBMR_PERIOD);

            //Load the start value into the GPTM Timer n Interval Load Register (GPTMTnILR).
            WRITE_REG(s_GPT.base+GPTMTBILR_R,s_GPT.T_Val);

            //If interrupts are required, set the appropriate bits in the GPTM Interrupt Mask Register (GPTMIMR).
            SET_BIT(s_GPT.base+GPTMIMR_R,TIMER_IMR_TBTOIM);

            //Enable interrupt IRQn
            NVIC_EnableIRQ(s_GPT.irqn_Type);

            //Set the TnEN bit in the GPTMCTL register to enable the timer and start counting.
            SET_BIT(s_GPT.base+GPTMCTL_R,TIMER_CTL_TBEN);


        }else{

        }


        //Set periodic task
        Periodic_Task[s_GPT.P_TaskNum] = s_GPT.P_Task;



    }




}




/*
 **********************************************************************************************************
 ************************************            ISRs             *****************************************
 **********************************************************************************************************
 */
void TIMER0A_ISR(void){
    //the status flags are cleared by writing a 1 to the appropriate bit of the GPTM Interrupt Clear Register (GPTMICR).
    SET_BIT(TIMER0+GPTMICR_R,TIMER_ICR_TATOCINT);

    //do periodic Task
    (*Periodic_Task[T0A_TASK])();
}


void TIMER0B_ISR(void){
    //the status flags are cleared by writing a 1 to the appropriate bit of the GPTM Interrupt Clear Register (GPTMICR).
    SET_BIT(TIMER0+GPTMICR_R,TIMER_ICR_TBTOCINT);

    //do periodic Task
    (*Periodic_Task[T0A_TASK])();
}


void TIMER1A_ISR(void){
    //the status flags are cleared by writing a 1 to the appropriate bit of the GPTM Interrupt Clear Register (GPTMICR).
    SET_BIT(TIMER1+GPTMICR_R,TIMER_ICR_TATOCINT);

    //do periodic Task
    (*Periodic_Task[T1A_TASK])();
}


void TIMER1B_ISR(void){
    //the status flags are cleared by writing a 1 to the appropriate bit of the GPTM Interrupt Clear Register (GPTMICR).
    SET_BIT(TIMER1+GPTMICR_R,TIMER_ICR_TBTOCINT);

    //do periodic Task
    (*Periodic_Task[T1A_TASK])();
}


void TIMER2A_ISR(void){
    //the status flags are cleared by writing a 1 to the appropriate bit of the GPTM Interrupt Clear Register (GPTMICR).
    SET_BIT(TIMER2+GPTMICR_R,TIMER_ICR_TATOCINT);

    //do periodic Task
    (*Periodic_Task[T2A_TASK])();
}


void TIMER2B_ISR(void){
    //the status flags are cleared by writing a 1 to the appropriate bit of the GPTM Interrupt Clear Register (GPTMICR).
    SET_BIT(TIMER2+GPTMICR_R,TIMER_ICR_TBTOCINT);

    //do periodic Task
    (*Periodic_Task[T2A_TASK])();
}


void TIMER3A_ISR(void){
    //the status flags are cleared by writing a 1 to the appropriate bit of the GPTM Interrupt Clear Register (GPTMICR).
    SET_BIT(TIMER3+GPTMICR_R,TIMER_ICR_TATOCINT);

    //do periodic Task
    (*Periodic_Task[T3A_TASK])();
}


void TIMER3B_ISR(void){
    //the status flags are cleared by writing a 1 to the appropriate bit of the GPTM Interrupt Clear Register (GPTMICR).
    SET_BIT(TIMER3+GPTMICR_R,TIMER_ICR_TBTOCINT);

    //do periodic Task
    (*Periodic_Task[T3A_TASK])();
}


void TIMER4A_ISR(void){
    //the status flags are cleared by writing a 1 to the appropriate bit of the GPTM Interrupt Clear Register (GPTMICR).
    SET_BIT(TIMER4+GPTMICR_R,TIMER_ICR_TATOCINT);

    //do periodic Task
    (*Periodic_Task[T4A_TASK])();
}


void TIMER4B_ISR(void){
    //the status flags are cleared by writing a 1 to the appropriate bit of the GPTM Interrupt Clear Register (GPTMICR).
    SET_BIT(TIMER4+GPTMICR_R,TIMER_ICR_TBTOCINT);

    //do periodic Task
    (*Periodic_Task[T4A_TASK])();
}


void TIMER5A_ISR(void){
    //the status flags are cleared by writing a 1 to the appropriate bit of the GPTM Interrupt Clear Register (GPTMICR).
    SET_BIT(TIMER5+GPTMICR_R,TIMER_ICR_TATOCINT);

    //do periodic Task
    (*Periodic_Task[T5A_TASK])();
}


void TIMER5B_ISR(void){
    //the status flags are cleared by writing a 1 to the appropriate bit of the GPTM Interrupt Clear Register (GPTMICR).
    SET_BIT(TIMER5+GPTMICR_R,TIMER_ICR_TBTOCINT);

    //do periodic Task
    (*Periodic_Task[T5A_TASK])();
}


