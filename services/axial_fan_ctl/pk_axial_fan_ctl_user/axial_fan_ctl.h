/*=====================================================================================*/
/**
 * arduino_fwk.h
 * author : puch
 * date : Oct 22 2015
 *
 * description : Any comments
 *
 */
/*=====================================================================================*/
#ifndef AXIAL_FAN_CTL_H
#define AXIAL_FAN_CTL_H
/*=====================================================================================*
 * Project Includes
 *=====================================================================================*/

/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/
#include <stdint.h>
/*=====================================================================================* 
 * Exported X-Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Define Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Type Declarations
 *=====================================================================================*/
namespace fan{
/*=====================================================================================* 
 * Exported Object Declarations
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Function Prototypes
 *=====================================================================================*/
extern void Init(void);
extern void Set_Output(const uint8_t out);
extern uint16_t Get_Output(void);
extern void Shut(void);
/*=====================================================================================* 
 * Exported Function Like Macros
 *=====================================================================================*/
   
} /*namespace fan*/
/*=====================================================================================* 
 * arduino_fwk.h
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
#endif /*AXIAL_FAN_CTL_H*/
