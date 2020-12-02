/*
 * utilites.h
 *
 * Created: 2/20/2018 10:15:13 PM
 *  Author: magdy
 */ 


#ifndef UTL_UTILITES_H_
#define UTL_UTILITES_H_

#define ASSIGN_BIT(reg,bit_no,value)                        (*(volatile uint32*) (reg))=((~(1<<bit_no))&(*(volatile uint32*) (reg)))|(value<<bit_no)
#define GET_BIT(reg,bits_no)                                ((*(volatile uint32*) (reg)) &(1UL<<bits_no))>>bits_no
#define CLR_BIT(REG,BIT_OFFSET)                             ((*(volatile uint32*) (REG)) &= (~(BIT_OFFSET)))
#define SET_BIT(REG,BIT_OFFSET)                             (*(volatile uint32*) (REG)) |= (BIT_OFFSET)
#define BIT_IS_SET(REG,BIT_OFFSET)                          ((*(volatile uint32*) (REG)) & (BIT_OFFSET))
#define BIT_IS_CLR(REG,BIT_OFFSET)                          (!(BIT_IS_SET((REG),BIT_OFFSET)))
#define SET_TWO_BITS(Reg,bitNum1,bitNum2)                   (*(volatile uint32*) (Reg))=Reg|(1UL<<bitNum1)|(1UL<<bitNum2)
#define SET_THREE_BITS(Reg,bitNum1,bitNum2,bitNum3)         (*(volatile uint32*) (Reg))=Reg|(1UL<<bitNum1)|(1UL<<bitNum2)|(1UL<<bitNum3)
#define SET_FOUR_BITS(Reg,bitNum1,bitNum2,bitNum3,bitNum4)  Reg=Reg|(1UL<<bitNum1)|(1UL<<bitNum2)|(1UL<<bitNum3)|(1UL<<bitNum4)
#define TOGGLE_BIT(reg,bits_no)                             (*(volatile uint32*) (reg))^=(1UL<<bits_no)
#define SET_REG(reg)                                        reg= 0xff
#define CLR_REG(reg)                                        reg = 0x00
#define TOGGLE_REG(reg)                                     reg^=0xff
#define ASSIGN_REG(reg,value)                               reg=value
#define GET_LOW_NIBLE(reg)                                  reg& 0x0f
#define CLR_LOW_NIBLE(reg )                                 reg&= 0xf0
#define SET_LOW_NIBLE(reg )                                 reg|=0x0f
#define TOGGLE_LOW_NIBLE(reg)                               reg^=0x0f
#define ASSIGN_LOW_NIBLE(reg,value)                         reg=(reg&0xf0)|(value&0x0f)
#define GET_HIGH_NIBLE(reg)                                 reg=(reg& 0x0f )>> 4UL
#define CLR_HIGH_NIBLE(reg)                                 reg&=0x0f
#define SET_HIGH_NIBLE(reg)                                 reg|=0xf0
#define TOGGLE_HIGH_NIBLE(reg)                              reg^=0xf0
#define ASSIGN_HIGH_NIBLE(reg,value)                        reg=(reg&0x0f)|(value<<4UL)
#define ADD_BIT_VALUE(bitNum,value)                         (value<<bitNum)
#define ACCESS_REG(REG)                                     (*(volatile uint32*)(REG))
#define READ_REG(REG)                                       (*(volatile uint32*) (REG))
#define WRITE_REG(REG, VAL)                                 ((*(volatile uint32*) (REG)) = VAL)


#define GET_DATA_BIT(Reg,bitNum)                            (Reg&(1<<bitNum))>>bitNum
#define SET_D_BIT(reg,bits_no)                              reg |=(1UL<<bits_no)
#define CLR_D_BIT(reg,bits_no)                              reg &= ~(1UL<<bits_no)
#define CPU_Clk  80000000UL

#define Test_Mode 1
#define Real_Mode 0

#define     BIT0        0
#define     BIT1        1
#define     BIT2        2
#define     BIT3        3
#define     BIT4        4
#define     BIT5        5
#define     BIT6        6
#define     BIT7        7
#define     BIT8        8
#define     BIT9        9
#define     BIT10       10
#define     BIT11       11
#define     BIT12       12
#define     BIT13       13
#define     BIT14       14
#define     BIT15       15
#define     BIT16       16
#define     BIT17       17
#define     BIT18       18
#define     BIT19       19
#define     BIT20       20
#define     BIT21       21
#define     BIT22       22
#define     BIT23       23
#define     BIT24       24
#define     BIT25       25
#define     BIT26       26
#define     BIT27       27
#define     BIT28       28
#define     BIT29       29
#define     BIT30       30
#define     BIT30       30
#define     BIT31       31
#define     BIT32       32


#endif /* UTL_UTILITES_H_ */
