#ifndef Platform_Types_H
#define Platform_Types_H

/********************************************************************************
***** CPU register type width                                               *****
********************************************************************************/
#define CPU_TYPE_8                                  (8u)
#define CPU_TYPE_16                                 (16u)
#define CPU_TYPE_32                                 (32u)

/********************************************************************************
***** Bit order definition                                                  *****
********************************************************************************/
#define MSB_FIRST                                   (0u)     /* Big endian bit ordering      */
#define LSB_FIRST                                   (1u)     /* Little endian bit ordering   */

/********************************************************************************
***** Byte order definition                             					*****
********************************************************************************/
#define HIGH_BYTE_FIRST                             (0u)     /* Big endian byte ordering     */
#define LOW_BYTE_FIRST                              (1u)     /* Little endian byte ordering  */

/********************************************************************************
***** Platform type & endian definitions ,specific for win32/ix86           *****
********************************************************************************/
#define CPU_TYPE 													CPU_TYPE_8

#define CPU_BIT_ORDER												LSB_FIRST
#define CPU_BYTE_ORDER												LOW_BYTE_FIRST

#define FALSE														((uint8)0x00)
#define TRUE 														((uint8)0x01)

/********************************************************************************
***** AUTOSAR integer data types										    *****
********************************************************************************/
typedef signed char                          sint8;
typedef	unsigned char 						 uint8;
typedef	signed short int                     sint16;
typedef unsigned short int					 uint16;
typedef	signed long int                      sint32;
typedef	unsigned long                        uint32;
typedef unsigned long long                   uint64;
typedef float                                float32;
typedef	double								 float64;
typedef uint8 bool;
typedef unsigned long						 uint8_least;
typedef unsigned long                        uint16_least;
typedef unsigned long                        uint32_least;
typedef signed long                          sint8_least;
typedef signed long                          sint16_least;
typedef	signed long                          sint32_least;

typedef unsigned char                        boolean;
	

#endif //Platform_Types_H
