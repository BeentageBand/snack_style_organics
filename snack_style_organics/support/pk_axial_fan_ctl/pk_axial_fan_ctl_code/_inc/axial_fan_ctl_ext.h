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
#ifndef AXIAL_FAN_CTL_EXT_H_
#define AXIAL_FAN_CTL_EXT_H_
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
namespace fan{
/*=====================================================================================* 
 * Exported Type Declarations
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Object Declarations
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Function Prototypes
 *=====================================================================================*/
extern void Init_Driver(void);
extern void Run_Driver(const uint8_t driver_out);
extern void Stop_Driver(void);
/*=====================================================================================* 
 * Exported Function Like Macros
 *=====================================================================================*/
} /*namespace fan*/
/*=====================================================================================* 
 * api_ext.h
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
#endif /*AXIAL_FAN_CTL_EXT_H_*/
