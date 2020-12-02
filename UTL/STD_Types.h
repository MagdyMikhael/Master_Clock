#ifndef STD_Types_H
#define STD_Types_H

/********************************************************************************
***** Includes                  										     																*****
********************************************************************************/
#include <UTL/Platform_Types.h>
#include "stdint.h"

/********************************************************************************
***** Typedefs                    										   																	 *****
********************************************************************************/
typedef uint8 Std_ReturnType;
	
/********************************************************************************
***** Structure for the version of the module							    							 *****
*****This is requested by calling <Module name>_GetVersionInfo()****
********************************************************************************/
typedef struct{
	uint16 vendorID;
	uint16 moduleID;
	uint8 sw_major_version;
	uint8 sw_minor_version;
	uint8 sw_patch_version;
}Std_VersionInfoType;


#define STD_HIGH                              0x01U       /*Standard HIGH */
#define STD_LOW                               0x00U       /*Standard LOW  */

#define STD_ACTIVE                            0x01U       /*Logical state active */
#define STD_IDLE                              0x00U       /*Logical state idle   */

#define STD_ON                                0x01U       /*Standard ON   */
#define STD_OFF                               0x00U       /*Standard OFF  */

#define E_OK                                  ((Std_ReturnType)0x01U)    /*Function Return OK     */
#define E_NOT_OK                              ((Std_ReturnType)0x00U)    /*Function Return NOT OK */




#endif //STD_Types_H
