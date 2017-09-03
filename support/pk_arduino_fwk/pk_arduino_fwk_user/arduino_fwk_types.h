/*=====================================================================================*/
/**
 * arduino_fwk_types.h
 * author : puch
 * date : Oct 22 2015
 *
 * description : Any comments
 *
 */
/*=====================================================================================*/
#ifndef ARDUINO_FWK_TYPES_H_
#define ARDUINO_FWK_TYPES_H_
/*=====================================================================================*
 * Project Includes
 *=====================================================================================*/
#include "arduino_fwk_uset.h"
#include "std_def.h"
/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Define Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Type Declarations
 *=====================================================================================*/
//PWM types
#undef ARDUINO_PWM_CHANNEL_INDEX
#define ARDUINO_PWM_CHANNEL_INDEX(ch) ch,

typedef enum{
ARDUINO_PWM_CHANNELS_TABLE
ARDUINO_PWM_MAX_CHANNELS
}ARDUINO_PWM_CHANNEL_T;

//ADC types
#undef ARDUINO_ADC_CHANNEL_INDEX
#define ARDUINO_ADC_CHANNEL_INDEX(ch) ch,

typedef enum{
ARDUINO_ADC_CHANNELS_TABLE
ARDUINO_ADC_MAX_CHANNELS
}ARDUINO_ADC_CHANNEL_T;


//ISR types
#undef ARDUINO_ISR_THREAD_INDEX
#define ARDUINO_ISR_THREAD_INDEX(thread) thread,
typedef enum{
ARDUINO_ISR_THREADS_TABLE
ARDUINO_ISR_MAX_THREADS
}ARDUINO_ISR_THREAD_T;

typedef void (*Arduino_ISR_T) (void);

//LCD types
typedef struct
{
   uint8_t         line;
   uint8_t         ptr;
}Arduino_LCD_T;

//UART types
#undef ARDUINO_UART_CHANNEL_INDEX
#define ARDUINO_UART_CHANNEL_INDEX(ch) ch,

typedef enum{
ARDUINO_UART_CHANNELS_TABLE
ARDUINO_UART_MAX_CHANNELS
}ARDUINO_UART_CHANNEL_T;

typedef struct
{
   ARDUINO_UART_CHANNEL_T  channel;
   uint16_t baud;
}Arduino_UART_T;

#undef ARDUINO_DIO_CHANNEL_INDEX
#define ARDUINO_DIO_CHANNEL_INDEX(ch) ch,
typedef enum
{
   ARDUINO_DIO_CHANNELS_TABLE
   ARDUINO_DIO_MAX_CHANNELS
}ARDUINO_DIO_CHANNEL_T;


typedef char Pgm_Char_T; //for const strings
/*=====================================================================================* 
 * arduino_fwk_types.h
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
#endif /*ARDUINO_FWK_TYPES_H_*/
