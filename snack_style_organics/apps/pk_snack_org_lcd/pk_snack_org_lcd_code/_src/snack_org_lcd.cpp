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

/*=====================================================================================*
 * Project Includes
 *=====================================================================================*/
#include "snack_org_lcd.h"
#include "arduino_fwk_lcd.h"
#include "arduino_fwk_clk.h"
#include "temp_monitor.h"
#include "daylight_monitor.h"
/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/
#include <stdint.h>
#include <string.h>
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
const uint8_t LCD_0_Fmt[] PROGMEM = "Temp: __.__    ";
const uint8_t  LCD_1_Fmt[] PROGMEM ="Time: 00:00-Day";
static uint8_t LCD_Data[16];

static bool Daylight = false;
static uint16_t Temperature = 0;
static uint8_t LCD_Time[] = {0,0};

static Arduino_LCD_T LCD_Print =
{
   0x00, 0x00, LCD_Data, 0x00
};
const uint8_t LCD_TIME_PTR = 6;
const uint8_t LCD_TEMP_PTR = 6;
const uint8_t LCD_DAY_PTR = 12;
/*=====================================================================================* 
 * Exported Object Definitions
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Prototypes
 *=====================================================================================*/
static void Format_Time(void);
static void Format_Temp(void);
static void Format_Day(void);
/*=====================================================================================* 
 * Local Inline-Function Like Macros
 *=====================================================================================*/
/*=====================================================================================* 
 * Local Function Definitions
 *=====================================================================================*/
void Format_Time(void)
{
   uint32_t time = LCD_Time[1]*10 + LCD_Time[0];
   uint32_t new_time = arduino::Get_Clk();
   if(time != new_time)
   {
      LCD_Time[1] = (new_time/60);
      LCD_Time[0] = new_time%60;

      for(uint8_t i = 0; i < sizeof(LCD_Data); ++i)
      {
         LCD_Data[i] = pgm_read_byte(LCD_1_Fmt + i);
      }
   }

}

void Format_Temp(void)
{
   uint16_t temp = temp_mon::Get_Temperature();

   if(temp != Temperature)
   {
      Temperature = temp;

      for(uint8_t i = 0; i < sizeof(LCD_Data); ++i)
      {
         LCD_Data[i] = pgm_read_byte(LCD_1_Fmt + i);
      }
      uint8_t ptr = LCD_TEMP_PTR;
      LCD_Data[ptr] = temp/1000;
      ptr++;
      LCD_Data[ptr] = temp/100;
      ptr+=2;
      LCD_Data[ptr] = temp/10;

      LCD_Print.line = 0;
      LCD_Print.ptr = 0;
      LCD_Print.lenght = 11U;

      arduino::Set_LCD(LCD_Print);
   }
}
void Format_Day(void)
{
   bool day = day_mon::Get_Daylight_Presence();

   if(day != Daylight)
   {
      Daylight = day;

      for(uint8_t i = 0; i < sizeof(LCD_Data); ++i)
      {
         LCD_Data[i] = pgm_read_byte(LCD_1_Fmt + i);
      }

      uint8_t ptr = LCD_TIME_PTR;
      LCD_Data[ptr] = day/1000;
      ptr++;
      LCD_Data[ptr] = day/100;
      ptr+=2;
      LCD_Data[ptr] = day/10;

      LCD_Print.line = 0;
      LCD_Print.ptr = 0;
      LCD_Print.lenght = 11U;

      arduino::Set_LCD(LCD_Print);
   }
}
/*=====================================================================================* 
 * Exported Function Definitions
 *=====================================================================================*/
void snack_lcd::Init(void)
{
   memset(LCD_Data, 0x00, sizeof(LCD_Data));
   arduino::Init_LCD();
}

void snack_lcd::Main(void)
{
   Format_Time();
   Format_Temp();
   Format_Day();
}

void snack_lcd::Shut(void)
{
   arduino::Stop_LCD();
}
/*=====================================================================================* 
 * snack_power_mode.cpp
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/

