/*=====================================================================================*/
/**
 * arduino_fwk_uart.cpp
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
#include "arduino_fwk_uart.h"
#include "arduino_fwk_uset.h"
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
static HardwareSerial* UART_Channels_To_Ports[] =
{
      &Serial,
};
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
void arduino::Init_UART(Arduino_UART_T const & uart)
{
   if(uart.channel < ARDUINO_UART_MAX_CHANNELS)
   {
      UART_Channels_To_Ports[uart.channel]->begin(uart.baud);
   }
}
void arduino::Put_UART(const ARDUINO_UART_CHANNEL_T uart, const uint8_t c)
{
   if(uart < ARDUINO_UART_MAX_CHANNELS)
   {
      UART_Channels_To_Ports[uart]->write(c);
   }
}

void arduino::Print_UART(const ARDUINO_UART_CHANNEL_T uart, const char * printed)
{
   if(uart < ARDUINO_UART_MAX_CHANNELS)
   {
      UART_Channels_To_Ports[uart]->write(printed);
   }
}

void arduino::Print_UART_P(const ARDUINO_UART_CHANNEL_T uart, const Pgm_Char_T const_c)
{
   if(uart < ARDUINO_UART_MAX_CHANNELS)
   {
      const char c = pgm_read_byte(const_c);
      UART_Channels_To_Ports[uart]->write(c);
   }
}

void arduino::Print_UART_P(const ARDUINO_UART_CHANNEL_T uart, const char * const_c)
{
   if(uart < ARDUINO_UART_MAX_CHANNELS)
   {
      for(uint8_t i = 0 ; '\0' != pgm_read_byte(const_c + i); ++i)
      {
         UART_Channels_To_Ports[uart]->write(pgm_read_byte(const_c + i));
      }
   }
}

void arduino::Print_UART(const ARDUINO_UART_CHANNEL_T uart, int d)
{
   if(uart < ARDUINO_UART_MAX_CHANNELS)
   {
      UART_Channels_To_Ports[uart]->print(d, DEC);
   }
}

void arduino::Print_UART(const ARDUINO_UART_CHANNEL_T uart, long l)
{
   if(uart < ARDUINO_UART_MAX_CHANNELS)
   {
      UART_Channels_To_Ports[uart]->print(l, DEC);
   }
}
uint8_t arduino::Get_UART(const ARDUINO_UART_CHANNEL_T uart)
{
   uint8_t read = 0xFFU;

   if(uart < ARDUINO_UART_MAX_CHANNELS &&
     (UART_Channels_To_Ports[uart]->available() > 0))
   {
      read = UART_Channels_To_Ports[uart]->read();
   }
   return read;
}
uint16_t arduino::Get_Available_UART(const ARDUINO_UART_CHANNEL_T uart)
{
   uint16_t available = 0;

   if(uart < ARDUINO_UART_MAX_CHANNELS)
   {
      available = UART_Channels_To_Ports[uart]->available();
   }
   return available;
}
void arduino::Flush_UART(const ARDUINO_UART_CHANNEL_T uart)
{
   if(uart < ARDUINO_UART_MAX_CHANNELS)
   {
      UART_Channels_To_Ports[uart]->flush();
   }
}

void arduino::Stop_UART(const ARDUINO_UART_CHANNEL_T uart)
{
   if(uart < ARDUINO_UART_MAX_CHANNELS)
   {
      UART_Channels_To_Ports[uart]->end();
   }
}
/*=====================================================================================* 
 * arduino_fwk_uart.cpp
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
