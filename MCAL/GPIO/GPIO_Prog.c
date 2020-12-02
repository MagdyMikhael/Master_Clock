/*
 * GPIO_Prog.c
 *
 *  Created on: Nov 20, 2018
 *      Author: eng-magdy
 */

/*============================================================*/
/*==========               includes                 ==========*/
/*============================================================*/
#include <MCAL/GPIO/GPIO_CFG.h>


/*============================================================*/
/*==========             Functions Bodies           ==========*/
/*============================================================*/
void GPIO_WritePinDir(uint8 PIN_NUM,uint8 Val){
    //calculate pin port and its offset
    uint8 Pin_Location=PIN_NUM/8;
    uint8 Pin_Index=PIN_NUM%8;

    GPIO_Base base=GPIO_A;
    switch(Pin_Location){
        case 0: base = GPIO_A;
        break;
        case 1: base = GPIO_B;
        break;
        case 2: base = GPIO_C;
        break;
        case 3: base = GPIO_D;
        break;
        case 4: base = GPIO_E;
        break;
        case 5: base = GPIO_F;
        break;
        default:
            break;

    }

    //Enable GPIO PORT
    SET_BIT(SYSCTL_RCGCGPIO,(1UL<<Pin_Location));

    //Enable Digital
    SET_BIT(base+GPIO_DEN_R,(1UL<<Pin_Index));

    //Diable alternative Function
    CLR_BIT(base+GPIO_AFSEL_R,(1UL<<Pin_Index));

    //Enable encrypted pins
    WRITE_REG(base+GPIO_LOCK_R,GPIO_LOCK_KEY);
    WRITE_REG(base+GPIO_CR_R,CR_VALUE);

    //Enable pull up resistor if configered input
    if(Val==STD_LOW){
        SET_BIT(base+GPIO_PUR_R,(1UL<<Pin_Index));
    }

    //define direction of Pin
    if(Val){
        SET_BIT(base+GPIO_DIR_R,(1<<Pin_Index));
    }else{
        CLR_BIT(base+GPIO_DIR_R,(1<<Pin_Index));
    }

}


void GPIO_WritePinVal(uint8 PIN_NUM,uint8 Val){
    //calculate pin port and its offset
    uint8 Pin_Location=PIN_NUM/8;
    uint8 Pin_Index=(1<<(PIN_NUM%8));
    GPIO_Base base=GPIO_A;
    switch(Pin_Location){
        case 0: base = GPIO_A;
        break;
        case 1: base = GPIO_B;
        break;
        case 2: base = GPIO_C;
        break;
        case 3: base = GPIO_D;
        break;
        case 4: base = GPIO_E;
        break;
        case 5: base = GPIO_F;
        break;
        default:
            break;

    }


    //write pin value
    if(Val){
        SET_BIT(base+GPIO_DATA_R,Pin_Index);
    }else{
        CLR_BIT(base+GPIO_DATA_R,Pin_Index);
    }

}


uint8 GPIO_ReadPinVal(uint8 PIN_NUM){
    //calculate pin port and its offset
    uint8 Pin_Location=PIN_NUM/8;
    uint8 Pin_Index=PIN_NUM%8;

    GPIO_Base base=GPIO_A;
    switch(Pin_Location){
        case 0: base = GPIO_A;
        break;
        case 1: base = GPIO_B;
        break;
        case 2: base = GPIO_C;
        break;
        case 3: base = GPIO_D;
        break;
        case 4: base = GPIO_E;
        break;
        case 5: base = GPIO_F;
        break;
        default:
            break;

    }

    //get pin value
    return GET_BIT(base+GPIO_DATA_R,Pin_Index);

}


void GPIO_TogglePinVal(uint8 PIN_NUM){
    //calculate pin port and its offset
    uint8 Pin_Location=PIN_NUM/8;
    uint8 Pin_Index=1<<(PIN_NUM%8);

    GPIO_Base base=GPIO_A;
    switch(Pin_Location){
        case 0: base = GPIO_A;
        break;
        case 1: base = GPIO_B;
        break;
        case 2: base = GPIO_C;
        break;
        case 3: base = GPIO_D;
        break;
        case 4: base = GPIO_E;
        break;
        case 5: base = GPIO_F;
        break;
        default:
            break;

    }

    //get pin value
    if(GET_BIT(base+GPIO_DATA_R,Pin_Index)==1){
        CLR_BIT(base+GPIO_DATA_R,Pin_Index);
    }else{
        SET_BIT(base+GPIO_DATA_R,Pin_Index);
    }
    //TOGGLE_BIT(base+GPIO_DATA_R,Pin_Index);
}
