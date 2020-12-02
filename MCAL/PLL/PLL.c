/*
 * PLL.c
 *
 *  Created on: Nov 1, 2018
 *      Author: eng-magdy
 */

/*============================================================*/
/*==========               includes                 ==========*/
/*============================================================*/
#include <MCAL/PLL/PLL.h>

/*============================================================*/
/*==========             Functions Bodies           ==========*/
/*============================================================*/
void PLL_Enable(void)
{
    // 0) Use RCC2
    SET_D_BIT(SYSCTL_RCC2_R,USERCC2);                             // USERCC2
    // 1) bypass PLL while initializing
    SET_D_BIT(SYSCTL_RCC2_R,BYPASS2);                             // BYPASS2, PLL bypass
    // 2) select the crystal value and oscillator source
    SYSCTL_RCC_R = (SYSCTL_RCC_R &~0x000007C0)                  // clear XTAL field, bits 10-6
                     + 0x00000540;                              // 10101, configure for 16 MHz crystal
    SYSCTL_RCC2_R &= ~0x00000070;                               // configure for main oscillator source
    // 3) activate PLL by clearing PWRDN
    CLR_D_BIT(SYSCTL_RCC2_R,PWRDN2);
    // 4) set the desired system divider
    SET_D_BIT(SYSCTL_RCC2_R,DIV400);                              // use 400 MHz PLL
    SYSCTL_RCC2_R = (SYSCTL_RCC2_R&~ 0x1FC00000)                // clear system clock divider
                          + (4<<22);                            // configure for 80 MHz clock                            // configure for 80 MHz clock
    // 5) wait for the PLL to lock by polling PLLLRIS
    while(GET_DATA_BIT(SYSCTL_RIS_R,PLLLRIS)==FALSE);                // wait for PLLRIS bit
    // 6) enable use of PLL by clearing BYPASS
    CLR_D_BIT(SYSCTL_RCC2_R,BYPASS2);

}

