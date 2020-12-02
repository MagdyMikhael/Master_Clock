


/*============================================================*/
/*==========               includes                 ==========*/
/*============================================================*/
#include <MCAL/SysTick/SysTick.h>

/*============================================================*/
/*==========              GlobalVars                ==========*/
/*============================================================*/
uint16 i=0;

void (*CallBack)(void);
void (*CallBackPassed)(void);
/*============================================================*/
/*==========              ProtoTypes                ==========*/
/*============================================================*/
void SysTick_ISR(void);

/*============================================================*/
/*==========             Functions Bodies           ==========*/
/*============================================================*/


void SysTick_Init(void(*func)(void))
{


    // disable SysTick during setup
    NVIC_ST_CTRL_R = 0x00000000;
    // enable SysTick with core clock 0x00000005;
    SET_THREE_BITS(NVIC_ST_CTRL,Enable,Inten,CLK_SRC);
    NVIC_ST_CURRENT_R = 0;
#ifdef PreS_1000
    NVIC_ST_RELOAD_R =(CPU_Clk/PreS_1000)-1;
#elif defined(PreS_M)
    NVIC_ST_RELOAD_R =(CPU_Clk/PreS_M)-1;
#elif defined(PreS_2)
    NVIC_ST_RELOAD_R =(CPU_Clk/PreS_2)-1;
#endif
    //NVIC_EnableIRQ(SysTick_IRQn);

    CallBack=func;
	
}



void SysTick_ISR(){


    if(i>PreS_1000){
        (*CallBack)();
        (*CallBackPassed)();
        i=1;
    }
    i++;
}

void Systick_PassFunc(void(*func)(void)){
    CallBackPassed = func;
}




