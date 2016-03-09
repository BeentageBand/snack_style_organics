/*=====================================================================================*/
/**
 * arduino_fwk_ext.h
 * author : puch
 * date : Oct 22 2015
 *
 * description : Any comments
 *
 */
/*=====================================================================================*/
#ifndef DAYLIGHT_MONITOR_EXT_H_
#define DAYLIGHT_MONITOR_EXT_H_
/*=====================================================================================*
 * Project Includes
 *=====================================================================================*/
#include "std_def.h"
/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Define Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Type Declarations
 *=====================================================================================*/
namespace day_mon{
/*=====================================================================================* 
 * Exported Object Declarations
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Function Prototypes
 *=====================================================================================*/
extern void Driver_Init(void);
extern uint16_t Get_Light_Sensitivity(void);
extern void Driver_Stop(void);
/*=====================================================================================* 
 * Exported Function Like Macros
 *=====================================================================================*/
}
/*=====================================================================================* 
 * arduino_fwk_ext.h
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
#endif /*DAYLIGHT_MONITOR_EXT_H_*/

