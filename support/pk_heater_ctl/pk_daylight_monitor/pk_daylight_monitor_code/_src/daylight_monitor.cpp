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

#include "../../../../include/daylight_monitor_set.h"
#include "../../../../include/snack_style_gpio.h"
#include "daylight_monitor_ext.h"
/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/

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
static bool Is_Day_Present = false;

static uint16_t Light_Channel_Readings[DAYLIGHT_MON_AVG_SIZE] = {0};
/*=====================================================================================* 
 * Exported Object Definitions
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Prototypes
 *=====================================================================================*/
static uint16_t Get_Average(void);
/*=====================================================================================* 
 * Local Inline-Function Like Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Definitions
 *=====================================================================================*/
uint16_t Get_Average(void)
{
   uint16_t avg = 0;
   for(uint8_t i = 0; i < DAYLIGHT_MON_AVG_SIZE; ++i)
   {
      avg += Light_Channel_Readings[i];
   }
   return (avg/DAYLIGHT_MON_AVG_SIZE);
}
/*=====================================================================================* 
 * Exported Function Definitions
 *=====================================================================================*/
void day_mon::Init(void)
{
   arduino::Init_ADC(SNACK_GPIO_ADC_LIGHT_AVG);
}

bool day_mon::Get_Daylight_Presence(void)
{
   if(Is_Day_Present)
   {
      Is_Day_Present = Light_Sensitivity_Day > day_mon::Get_Daylight_Percentage();
   }
   else
   {
      Is_Day_Present = Light_Sensitivity_No_Day < day_mon::Get_Daylight_Percentage();
   }
   return (Is_Day_Present);
}

uint16_t day_mon::Get_Daylight_Percentage(void)
{
	return Get_Average();
}

void day_mon::Main(void)
{
	uint16_t light = DAYLIGHT_CONVERSION_COEFF*arduino::Get_ADC( SNACK_GPIO_ADC_LIGHT_AVG );
	memcpy( Light_Channel_Readings, &Light_Channel_Readings[1], sizeof(Light_Channel_Readings) );
	Light_Channel_Readings[DAYLIGHT_MON_AVG_SIZE-1] = light;
}

void day_mon::Shut(void)
{
   arduino::Stop_ADC(SNACK_GPIO_ADC_LIGHT_AVG);
}
/*=====================================================================================* 
 * arduino_fwk.cpp
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/


