/*=====================================================================================*/
/**
 * arduino_fwk_uart.h
 * author : puch
 * date : Oct 22 2015
 *
 * description : Any comments
 *
 */
/*=====================================================================================*/
#ifndef ARDUINO_FWK_UART_H_
#define ARDUINO_FWK_UART_H_
/*=====================================================================================*
 * Project Includes
 *=====================================================================================*/
#include "arduino_fwk_types.h"
/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/
#include <stdint.h>
/*=====================================================================================* 
 * Exported X-Macros
 *=====================================================================================*/

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
extern void Init_UART(Arduino_UART_T const & uart);
extern void Put_UART(  const ARDUINO_UART_CHANNEL_T uart, const uint8_t c);
extern void Print_UART(const ARDUINO_UART_CHANNEL_T uart, const char * printed);
extern void Print_UART_P(const ARDUINO_UART_CHANNEL_T uart, const Pgm_Char_T const_c);
extern void Print_UART_P(const ARDUINO_UART_CHANNEL_T uart, const char * const_c);
extern void Print_UART(const ARDUINO_UART_CHANNEL_T uart, int i);
extern void Print_UART(const ARDUINO_UART_CHANNEL_T uart, long l);
extern uint8_t Get_UART(const ARDUINO_UART_CHANNEL_T uart);
extern uint16_t Get_Available_UART( const ARDUINO_UART_CHANNEL_T uart);
extern void Flush_UART(const ARDUINO_UART_CHANNEL_T uart);
extern void Stop_UART( const ARDUINO_UART_CHANNEL_T uart);
/*=====================================================================================* 
 * Exported Function Like Macros
 *=====================================================================================*/
}/*namespace arduino*/
/*=====================================================================================* 
 * arduino_fwk_uart.h
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
#endif /*ARDUINO_FWK_UART_H_*/
