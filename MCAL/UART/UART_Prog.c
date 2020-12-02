/*
 * UART_Prog.c
 *
 *  Created on: Nov 1, 2020
 *      Author: Eng-Magdy Moheb
 */


/*============================================================*/
/*==========               includes                 ==========*/
/*============================================================*/
#include <MCAL/UART/UART_CFG.h>

/*============================================================*/
/*==========              ProtoTypes                ==========*/
/*============================================================*/
void UART0_ISR(void);
void UART1_ISR(void);
void UART2_ISR(void);
void UART3_ISR(void);
void UART4_ISR(void);
void UART5_ISR(void);
void UART6_ISR(void);
void UART7_ISR(void);
/*============================================================*/
/*==========              GlobalVars                ==========*/
/*============================================================*/
const static uint8 Uart_IRQ_list[8]={UART0_IRQn,
                                     UART1_IRQn,
                                     UART2_IRQn,
                                     UART3_IRQn,
                                     UART4_IRQn,
                                     UART5_IRQn,
                                     UART6_IRQn,
                                     UART7_IRQn
};


UART_STRUCT UART[8]={{Uart0,PORTA,PIN0,PIN1,Uart_PCM0,Uart_PCM1},
                     {99,99,99,99,99,99},
                     {Uart2,PORTD,PIN6,PIN7,Uart_PCM6,Uart_PCM7},
                     {Uart3,PORTC,PIN6,PIN7,Uart_PCM6,Uart_PCM7},
                     {Uart4,PORTC,PIN4,PIN5,Uart_PCM4,Uart_PCM5},
                     {Uart5,PORTE,PIN4,PIN5,Uart_PCM4,Uart_PCM5},
                     {Uart6,PORTD,PIN4,PIN5,Uart_PCM4,Uart_PCM5},
                     {Uart7,PORTE,PIN0,PIN1,Uart_PCM0,Uart_PCM1}};


volatile uint32 ReceiveComplete0 =0;
volatile uint32 i0=0;
volatile uint32 ReceiveComplete1 =0;
volatile uint32 i1=0;
volatile uint32 ReceiveComplete2 =0;
volatile uint32 i2=0;
volatile uint32 ReceiveComplete3 =0;
volatile uint32 i3=0;
volatile uint32 ReceiveComplete4 =0;
volatile uint32 i4=0;
volatile uint32 ReceiveComplete5 =0;
volatile uint32 i5=0;
volatile uint32 ReceiveComplete6 =0;
volatile uint32 i6=0;
volatile uint32 ReceiveComplete7 =0;
volatile uint32 i7=0;

char Uart0_Receive[Uart0_Buffer_Length];
char Uart1_Receive[Uart1_Buffer_Length];
char Uart2_Receive[Uart2_Buffer_Length];
char Uart3_Receive[Uart3_Buffer_Length];
char Uart4_Receive[Uart4_Buffer_Length];
char Uart5_Receive[Uart5_Buffer_Length];
char Uart6_Receive[Uart6_Buffer_Length];
char Uart7_Receive[Uart7_Buffer_Length];


uint8 data=0;
char arrBack[500];
/*============================================================*/
/*==========            Static Functions            ==========*/
/*============================================================*/


/*============================================================*/
/*==========             Functions Bodies           ==========*/
/*============================================================*/

void UART_Init(UART_S CFG_S){

    //Calculate Baud rate
    float BRDI_float=UARTSysClk/(ClkDiv * (CFG_S.baudRate));
    uint16 BAUD_RATE=(uint16)BRDI_float;
    BRDI_float = BRDI_float - (long)BRDI_float;
    uint8 FRACTION_PART=(uint8)(BRDI_float * 64 + 0.5);

    // provide clock to UART
    SET_BIT(SYSCTL_RCGCUART,(1UL<<UART[CFG_S.U_NUM].UART_NUM));



    //enable clock to PORT
    SET_BIT(SYSCTL_RCGCGPIO,(1UL<<UART[CFG_S.U_NUM].PORT_NUM));

    GPIO_Base base=GPIO_A;
    switch(UART[CFG_S.U_NUM].PORT_NUM){
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

    //Enable encrypted pins
    WRITE_REG(base+GPIO_LOCK_R,GPIO_LOCK_KEY);
    WRITE_REG(base+GPIO_CR_R,CR_VALUE);

    //USE ALTERNATIVE FUNCTIONS
    SET_BIT(base+GPIO_AFSEL_R,(1UL<<UART[CFG_S.U_NUM].URx));
    SET_BIT(base+GPIO_AFSEL_R,(1UL<<UART[CFG_S.U_NUM].UTx));


    //ENABLE DIGITAL
    SET_BIT(base+GPIO_DEN_R,(1UL<<UART[CFG_S.U_NUM].URx));
    SET_BIT(base+GPIO_DEN_R,(1UL<<UART[CFG_S.U_NUM].UTx));

    //USE PINS AS UART
    SET_BIT(base+GPIO_PCTL_R,(1UL<<UART[CFG_S.U_NUM].PCLR_Rx));
    SET_BIT(base+GPIO_PCTL_R,(1UL<<UART[CFG_S.U_NUM].PCLR_Tx));


    //Enable interrupt Function
    NVIC_EnableIRQ(Uart_IRQ_list[UART[CFG_S.U_NUM].UART_NUM]);

    //disable UART
    CLR_BIT(CFG_S.base+UART_CTL_R,(1UL<<UARTEN));

    //Set intger baud rate
    WRITE_REG(CFG_S.base+UART_IBRD_R,BAUD_RATE);

    //Set fraction part of baud rate
    WRITE_REG(CFG_S.base+UART_FBRD_R,FRACTION_PART);

    //8-bit, no parity, 1-stop bit, no FIFO
    WRITE_REG(CFG_S.base+UART_LCRH_R,(CFG_S.Bit_Num <<WLEN_SHIFT));
    //SET_BIT(CFG_S.base+UART_LCRH_R,(1UL<<FEN));

    //use system clock
    WRITE_REG(CFG_S.base+UART_CC_R,SYS_CLOCK);

#ifdef Debug
    SET_BIT(CFG_S.base+UART_CTL_R,L);
#endif

    //enable UART, TXE, RXE

    SET_THREE_BITS(CFG_S.base+UART_CTL_R,UARTEN,TXE,RXE);

    //SET_BIT(CFG_S.base+UART_CTL_R,TXE);
    //SET_BIT(CFG_S.base+UART_CTL_R,RXE);
    //SET_BIT(CFG_S.base+UART_CTL_R,UARTEN);

    //ENABLE INTERRUPT
    SET_BIT(CFG_S.base+UART_IM_R,(1UL<<RXIM));



}


void UART_Transmit(uint32 base,uint8 DATA){
    //wait until Tx buffer not full before giving it another byte
    while(GET_BIT(base+UART_FR_R,TXFF)!=FALSE);

    //transmit data
    WRITE_REG(base,DATA);

}


uint8 UART_Recieve(uint8 U_NUM){


    switch(U_NUM){
        case 0:
                  //while(Get_Bit(UART0_FR_R,RXFE)!=0);                               //wait until the buffer is not empty
                  data = Uart0_Receive[0];                                               //read the received data

          break;
        case 1:
                  //while(Get_Bit(UART1_FR_R,RXFE)!=0);
                  data = Uart1_Receive[1];
          break;
        case 2:
                  //while(Get_Bit(UART2_FR_R,RXFE)!=0);
                  data = Uart2_Receive[0];
          break;
        case 3:
                  //while(Get_Bit(UART3_FR_R,RXFE)!=0);
                  data = Uart3_Receive[0];
          break;
        case 4:
                  //while(Get_Bit(UART4_FR_R,RXFE)!=0);
                  data = Uart4_Receive[0];
          break;
        case 5:
                  //while(Get_Bit(UART5_FR_R,RXFE)!=0);
                  data = Uart5_Receive[0];
          break;
        case 6:
                  //while(Get_Bit(UART6_FR_R,RXFE)!=0);
                  data = Uart6_Receive[0];
          break;
        case 7:
                  //while(Get_Bit(UART7_FR_R,RXFE)!=0);
                  data = Uart7_Receive[0];
          break;
        default:
          break;

    }
    return data;
}


void UART_Write_String(Uart_Base base,char * string){
    while(*string != '\0')
      {
        UART_Transmit(base,* string );
        string++;
    }
    UART_Transmit(base, '\0' );
}


char * UART_Read_String(uint8 U_NUM ){

    switch(U_NUM){
      case 0:strcpy(arrBack,Uart0_Receive);
      break;
      case 1:strcpy(arrBack,Uart1_Receive);
      break;
      case 2:strcpy(arrBack,Uart2_Receive);
      break;
      case 3:strcpy(arrBack,Uart3_Receive);
      break;
      case 4:strcpy(arrBack,Uart4_Receive);
      break;
      case 5:strcpy(arrBack,Uart5_Receive);

      break;

      case 6:strcpy(arrBack,Uart6_Receive);
      break;
      case 7:strcpy(arrBack,Uart7_Receive);
      break;
      default:
        break;

      }
    return arrBack;
}





void UART0_ISR(void){
    Uart0_Receive[i0]=READ_REG(Uart0_base+UART_DR_R);

    if((Uart0_Receive[i0]=='\0')){
            ReceiveComplete0 =1;
            i0=0;

        }
    i0++;
    if(ReceiveComplete0==1){
        CLR_BIT(Uart0_base+UART_ICR_R,RXIC);
        i0=0;
        ReceiveComplete0=0;
    }
}


void UART1_ISR(void){
    Uart1_Receive[i1]=READ_REG(Uart1_base+UART_DR_R);

    if((Uart1_Receive[i1]=='\0')){
            ReceiveComplete1 =1;
            i1=0;

        }
    i1++;
    if(ReceiveComplete1==1){
        CLR_BIT(Uart1_base+UART_ICR_R,RXIC);
        i1=0;
    }
}


void UART2_ISR(void){
    Uart2_Receive[i2]=READ_REG(Uart2_base+UART_DR_R);

    if((Uart2_Receive[i2]=='\0')){
        ReceiveComplete2 =1;
        i2=0;

    }

    i2++;
    if(ReceiveComplete2==1){
        CLR_BIT(Uart2_base+UART_ICR_R,RXIC);
        i2=0;
        ReceiveComplete2=0;
    }
}


void UART3_ISR(void){
    Uart3_Receive[i3]=READ_REG(Uart3_base+UART_DR_R);

    if((Uart3_Receive[i3]=='\0')){
        ReceiveComplete3 =1;
        i3=0;}
    i3++;
    if(ReceiveComplete3==1){
        CLR_BIT(Uart3_base+UART_ICR_R,RXIC);
        i3=0;
        ReceiveComplete3=0;
    }
}


void UART4_ISR(void){
    Uart4_Receive[i4]=READ_REG(Uart4_base+UART_DR_R);

    if((Uart4_Receive[i4]=='\0')){
        ReceiveComplete4 =1;
        i4=0;}
    i4++;
    if(ReceiveComplete4==1){
        CLR_BIT(Uart4_base+UART_ICR_R,RXIC);
        i4=0;
        ReceiveComplete4=0;
    }
}


void UART5_ISR(void){

    Uart5_Receive[i5]=READ_REG(Uart5_base+UART_DR_R);

    if((Uart5_Receive[i5]=='\0')){
       ReceiveComplete5 =1;
       i5=0;}
    i5++;
   if(ReceiveComplete5==1){
       CLR_BIT(Uart5_base+UART_ICR_R,RXIC);
       ReceiveComplete5=0;
       i5=0;
   }


}


void UART6_ISR(void){
    Uart6_Receive[i6]=READ_REG(Uart6_base+UART_DR_R);

    if((Uart6_Receive[i6]=='\0')){
        ReceiveComplete6 =1;
        i6=0;}
    i6++;
    if(ReceiveComplete6==1){
        CLR_BIT(Uart6_base+UART_ICR_R,RXIC);
        i6=0;
        ReceiveComplete6=0;
    }
}


void UART7_ISR(void){
    Uart7_Receive[i7]=READ_REG(Uart7_base+UART_DR_R);

    if((Uart7_Receive[i7]=='\0')){
        ReceiveComplete7 =1;
        i7=0;}
    i7++;
    if(ReceiveComplete7==1){
        CLR_BIT(Uart7_base+UART_ICR_R,RXIC);
        i7=0;
        ReceiveComplete7=0;
    }
}

