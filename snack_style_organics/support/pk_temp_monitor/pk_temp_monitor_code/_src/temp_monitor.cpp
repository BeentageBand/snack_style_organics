/*=====================================================================================*/
/**
 * arduino_fwk.cpp
 * author : puch
 * date : Oct 22 2015
 *
 * description : Any comments
 *
 */
/*=====================================================================================*/

/*=====================================================================================*
 * Project Includes
 *=====================================================================================*/
#include "arduino_fwk_adc.h"
#include "temp_monitor.h"
#include "temp_monitor_set.h"
/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/

/*=====================================================================================* 
 * Local X-Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Define Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Type Definitions
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Object Definitions
 *=====================================================================================*/
const ARDUINO_ADC_CHANNEL_T TEMP_MON_ADC_CHANNEL = ARDUINO_ADC_CHANNEL_1;
/*=====================================================================================* 
 * Exported Object Definitions
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Prototypes
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Inline-Function Like Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Definitions
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Function Definitions
 *=====================================================================================*/
void temp_mon::Init(void)
{
   arduino::Init_ADC( TEMP_MON_ADC_CHANNEL );
}

uint16_t temp_mon::Get_Temperature(void)
{
   return (TEMPERATURE_CONVERSION_COEFF*arduino::Get_ADC( TEMP_MON_ADC_CHANNEL ) );
}

void temp_mon::Shut(void)
{
   arduino::Stop_ADC( TEMP_MON_ADC_CHANNEL );
}
/*=====================================================================================* 
 * arduino_fwk.cpp
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/


