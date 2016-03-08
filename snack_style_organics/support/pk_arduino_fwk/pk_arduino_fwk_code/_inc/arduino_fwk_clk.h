/*=====================================================================================*/
/**
 * arduino_fwk_clk.h
 * author : puch
 * date : Oct 22 2015
 *
 * description : Any comments
 *
 */
/*=====================================================================================*/
#ifndef ARDUINO_FWK_CLK_H_
#define ARDUINO_FWK_CLK_H_
/*=====================================================================================*
 * Project Includes
 *=====================================================================================*/
#include "arduino_fwk_types.h"
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
namespace arduino{
/*=====================================================================================* 
 * Exported Object Declarations
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Function Prototypes
 *=====================================================================================*/
extern void Init_Clk(void);
extern uint32_t Get_Clk(void);

extern void Init_Tone(const ARDUINO_DIO_CHANNEL_T pin);
extern void Set_Tone(const ARDUINO_DIO_CHANNEL_T pin, uint16_t freq);
extern void Stop_Tone(const ARDUINO_DIO_CHANNEL_T pin);

/*=====================================================================================* 
 * Exported Function Like Macros
 *=====================================================================================*/
}
/*=====================================================================================* 
 * arduino_fwk_clk.h
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
#endif /*ARDUINO_FWK_CLK_H_*/

