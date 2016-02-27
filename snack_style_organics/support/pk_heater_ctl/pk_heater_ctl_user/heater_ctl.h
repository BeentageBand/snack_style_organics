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
#ifndef  HEATER_CTL_H
#define HEATER_CTL_H
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
namespace heater{
/*=====================================================================================* 
 * Exported Object Declarations
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Function Prototypes
 *=====================================================================================*/
extern void Init(void);
extern void Set_Output(const uint8_t out);
extern uint8_t Get_Output(void);
extern void Shut(void);
/*=====================================================================================* 
 * Exported Function Like Macros
 *=====================================================================================*/
}/*heater*/
/*=====================================================================================* 
 * arduino_fwk.h
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
#endif /*HEATER_CTL_H*/

