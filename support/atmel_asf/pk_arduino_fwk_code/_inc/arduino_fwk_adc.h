/*=====================================================================================*/
/**
 * arduino_fwk_adc.h
 * author : puch
 * date : Oct 22 2015
 *
 * description : Any comments
 *
 */
/*=====================================================================================*/
#ifndef ARDUINO_FWK_ADC_H_
#define ARDUINO_FWK_ADC_H_
/*=====================================================================================*
 * Project Includes
 *=====================================================================================*/
#include <stdint.h>

#include "../../../avr_framework/pk_arduino_fwk_user/arduino_fwk_types.h"
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
extern void Init_ADC(const ARDUINO_ADC_CHANNEL_T channel);
extern uint16_t Get_ADC(const ARDUINO_ADC_CHANNEL_T channel);
extern void Stop_ADC(const ARDUINO_ADC_CHANNEL_T channel);
/*=====================================================================================* 
 * Exported Function Like Macros
 *=====================================================================================*/
}
/*=====================================================================================* 
 * arduino_fwk_adc.h
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
#endif /*ARDUINO_FWK_ADC_H_*/