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
#include "daylight_monitor.h"
#include "daylight_monitor_ext.h"
#include "daylight_monitor_set.h"
/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/
#include <stdint.h>
/*=====================================================================================* 
 * Local X-Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Define Macros
 *=====================================================================================*/
//#ifdef  ( DAYLIGHT_MON_DAYLIGHT_READING < DAYLIGHT_MON_HYSTHERESIS )
//#error  "DAYLIGHT_MON_DAYLIGHT_READING >= DAYLIGHT_MON_HYSTHERESIS"
//#endif
/*=====================================================================================* 
 * Local Type Definitions
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Object Definitions
 *=====================================================================================*/
const uint16_t  Light_Sensitivity_No_Day = DAYLIGHT_MON_DAYLIGHT_READING + DAYLIGHT_MON_HYSTHERESIS;
const uint16_t  Light_Sensitivity_Day =  DAYLIGHT_MON_DAYLIGHT_READING - DAYLIGHT_MON_HYSTHERESIS;
const ARDUINO_ADC_CHANNEL_T DAY_MON_ADC_CHANNEL = ARDUINO_ADC_CHANNEL_0;
static bool Is_Day_Present = false;
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
void day_mon::Init(void)
{
   arduino::Init_ADC(DAY_MON_ADC_CHANNEL);
}

bool day_mon::Get_Daylight_Presence(void)
{
   if(Is_Day_Present)
   {
      Is_Day_Present = Light_Sensitivity_Day > arduino::Get_ADC(DAY_MON_ADC_CHANNEL);
   }
   else
   {
      Is_Day_Present = Light_Sensitivity_No_Day < arduino::Get_ADC(DAY_MON_ADC_CHANNEL);
   }
   return (Is_Day_Present);
}

void day_mon::Shut(void)
{
   arduino::Stop_ADC(DAY_MON_ADC_CHANNEL);
}
/*=====================================================================================* 
 * arduino_fwk.cpp
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/


