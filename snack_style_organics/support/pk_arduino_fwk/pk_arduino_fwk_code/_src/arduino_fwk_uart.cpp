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
void arduino::Put_UART(Arduino_UART_T const & uart, const uint8_t c)
{
   if(uart.channel < ARDUINO_UART_MAX_CHANNELS)
   {
      UART_Channels_To_Ports[uart.channel]->write(c);
   }
}
uint8_t arduino::Get_UART(Arduino_UART_T const & uart)
{
   uint8_t read = 0xFFU;

   if(uart.channel < ARDUINO_UART_MAX_CHANNELS &&
     (UART_Channels_To_Ports[uart.channel]->available() > 0))
   {
      read = UART_Channels_To_Ports[uart.channel]->read();
   }
   return read;
}
uint16_t arduino::Get_Available_UART(Arduino_UART_T const & uart)
{
   uint16_t available = 0;

   if(uart.channel < ARDUINO_UART_MAX_CHANNELS)
   {
      available = UART_Channels_To_Ports[uart.channel]->available();
   }
   return available;
}
void arduino::Flush_UART(Arduino_UART_T const & uart)
{
   if(uart.channel < ARDUINO_UART_MAX_CHANNELS)
   {
      UART_Channels_To_Ports[uart.channel]->flush();
   }
}

void arduino::Stop_UART(Arduino_UART_T const & uart)
{
   if(uart.channel < ARDUINO_UART_MAX_CHANNELS)
   {
      UART_Channels_To_Ports[uart.channel]->end();
   }
}
/*=====================================================================================* 
 * arduino_fwk_uart.cpp
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
