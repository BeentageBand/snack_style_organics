/*=====================================================================================*/
/**
 * snack_power_mode.cpp
 * author : puch
 * date : Oct 22 2015
 *
 * description : Any comments
 *
 */
/*=====================================================================================*/
#define OBJECT_IMPLEMENTATION SSO_LCD_WN
/*=====================================================================================*
 * Project Includes
 *=====================================================================================*/
#include "snack_org_lcd.h"
#include "../../../../support/atmel_asf/pk_arduino_fwk_code/_inc/arduino_fwk_lcd.h"
#include "../../../../support/atmel_asf/pk_arduino_fwk_code/_inc/arduino_fwk_clk.h"
#include "../../../../support/temp_sensor/pk_temp_monitor_user/temp_monitor.h"
#include "../../../../support/heater_resistor_ctl/pk_daylight_monitor/pk_daylight_monitor_user/daylight_monitor.h"
#include "hama_dbg_trace.h"
/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/
#include "arduino_fwk_uset.h"
/*=====================================================================================* 
 * Local X-Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Define Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Type Definitions
 *=====================================================================================*/
CLASS_DEF(SSO_LCD_WN)

/*=====================================================================================* 
 * Local Object Definitions
 *=====================================================================================*/
const char LCD_0_Fmt[] PROGMEM = "Temp: __.__ Day";
const char LCD_1_Fmt[] PROGMEM = "Time: 00:00 00%";
static char LCD_Data[ARDUINO_LCD_MAX_COLS+1];

static bool Daylight = false;
static uint16_t Temperature = 0;
static uint8_t LCD_Time[] = {0,0};

const uint8_t LCD_TIME_PTR = 6;
const uint8_t LCD_TEMP_PTR = 6;
const uint8_t LCD_DAY_PTR = 12;
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
void SSO_LCD_WN_Format_Time(void)
{
   uint32_t time = LCD_Time[1]*10 + LCD_Time[0];
   uint32_t new_time = arduino::Get_Clk();
   if(time != new_time)
   {
      LCD_Time[1] = (new_time/60);
      LCD_Time[0] = new_time%60;

      memcpy_P(LCD_Data, LCD_1_Fmt, sizeof(LCD_Data));
      LCD_Data[ARDUINO_LCD_MAX_COLS] = 0;
   }
   Arduino_LCD_T lcd =
   {
      1, 0,
   };
   TR_Info("Display : %s, %s", __func__, LCD_Data);
   //arduino::Print_LCD(lcd, LCD_Data);
}

void SSO_LCD_WN_Format_Temp(void)
{
   uint16_t temp = temp_mon::Get_Temperature();

   if(temp != Temperature)
   {
      Temperature = temp;

      memcpy_P(LCD_Data, LCD_0_Fmt, sizeof(LCD_Data));
      LCD_Data[ARDUINO_LCD_MAX_COLS] = 0;
      uint8_t ptr = LCD_TEMP_PTR;
      LCD_Data[ptr] = temp/1000;
      ptr++;
      LCD_Data[ptr] = temp/100;
      ptr+=2;
      LCD_Data[ptr] = temp/10;

      Arduino_LCD_T lcd =
      {
         0,
         0,
      };
      TR_INFO_2("Display : %s, %s", __FUNCTION__, LCD_Data);
      arduino::Print_LCD(lcd, LCD_Data);
   }
}
void SSO_LCD_WN_Format_Day(void)
{
   bool day = day_mon::Get_Daylight_Presence();

   if(day != Daylight)
   {
      Daylight = day;

      memcpy_P(LCD_Data, LCD_1_Fmt, sizeof(LCD_Data));
      LCD_Data[ARDUINO_LCD_MAX_COLS] = 0;

      uint8_t ptr = LCD_TIME_PTR;
      LCD_Data[ptr] = day/1000;
      ptr++;
      LCD_Data[ptr] = day/100;
      ptr+=2;
      LCD_Data[ptr] = day/10;

      Arduino_LCD_T lcd =
      {
         1,
         0,
      };
      TR_INFO_2("Display : %s, %s", __FUNCTION__, LCD_Data);
      arduino::Print_LCD(lcd, LCD_Data);
   }
}
/*=====================================================================================* 
 * Exported Function Definitions
 *=====================================================================================*/
void SSO_LCD_WN_on_start(union Worker_Node * const super)
{
	SSO_LCD_WN * const this = _dynamic_cast(SSO_LCD_WN, super);
   memset(LCD_Data, 0x00, sizeof(LCD_Data));
   //arduino::Init_LCD();

	for(Node * it = SSO_LCD_WN_SNodes; it != SSO_LCD_WN_SNodes+1; ++it)
	{
		super.vtbl->subscribe(super, it);
	}

	Isnt_Nullptr(this,);

	this->vtbl->Worker_Node_on_start(&this->Worker_Node);
   TR_Info("%s ",__func__);
}

void SSO_LCD_WN_on_message(union Worker_Node * const super, union Mail * const mail)
{
	this->vtbl->Worker_Node_on_message(&this->Worker_Node);
}

void SSO_LCD_WN_on_periodic(union SSO_LCD_WN * const super)
{
	this->vtbl->Worker_Node_on_periodic(&this->Worker_Node);
   SSO_LCD_WN_Format_Time();
   SSO_LCD_WN_Format_Temp();
   SSO_LCD_WN_Format_Day();
}

void SSO_LCD_WN_on_stop(union Worker_Node * const super)
{
	this->vtbl->Worker_Node_on_stop(&this->Worker_Node);

	for(Node * it = SSO_LCD_WN_SNodes; it != SSO_LCD_WN_SNodes+1; ++it)
	{
		super.vtbl->unsubscribe(super, it);
	}


   //arduino::Stop_LCD();
}
/*=====================================================================================* 
 * snack_power_mode.cpp
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/

