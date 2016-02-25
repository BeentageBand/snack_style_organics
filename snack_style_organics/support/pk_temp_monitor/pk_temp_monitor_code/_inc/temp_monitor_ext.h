/*=====================================================================================*/
/**
 * api_ext.h
 * author : puch
 * date : Oct 22 2015
 *
 * description : Any comments
 *
 */
/*=====================================================================================*/
#ifndef TEMP_MONITOR_EXT_H_
#define TEMP_MONITOR_EXT_H_
/*=====================================================================================*
 * Project Includes
 *=====================================================================================*/

/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/
#include <stdint.h>
/*=====================================================================================* 
 * Exported Define Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Type Declarations
 *=====================================================================================*/
namespace temp_mon{
/*=====================================================================================* 
 * Exported Object Declarations
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Function Prototypes
 *=====================================================================================*/
extern void Driver_Init(void);
extern uint16_t Get_Input(void);
extern void Driver_Stop(void);
/*=====================================================================================* 
 * Exported Function Like Macros
 *=====================================================================================*/
} /*namespace temp_mon*/
/*=====================================================================================* 
 * api_ext.h
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
#endif /*TEMP_MONITOR_H_*/
