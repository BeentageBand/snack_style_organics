/*=====================================================================================*/
/**
 * arduino_fwk_clk.cpp
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
#include "arduino_fwk_clk.h"
/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/
#include "Arduino.h"
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
void arduino::Init_Clk(void)
{
   init();
}

uint32_t arduino::Get_Clk( void)
{
   return millis();
}

void arduino::Init_Tone(const ARDUINO_DIO_CHANNEL_T pin)
{
   pinMode(pin, OUTPUT);
}

void arduino::Set_Tone(const ARDUINO_DIO_CHANNEL_T pin, uint16_t freq)
{
   tone(pin,freq);
}

void arduino::Stop_Tone(const ARDUINO_DIO_CHANNEL_T pin)
{
   noTone(pin);
}
/*=====================================================================================* 
 * arduino_fwk_clk.cpp
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
