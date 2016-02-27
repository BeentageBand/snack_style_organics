/*=====================================================================================*/
/**
 * api_uset.h
 * author : puch
 * date : Oct 22 2015
 *
 * description : Any comments
 *
 */
/*=====================================================================================*/
#ifndef ARDUINO_FWK_USET_H_
#define ARDUINO_FWK_USET_H_
/*=====================================================================================*
 * Project Includes
 *=====================================================================================*/

/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported X-Macros
 *=====================================================================================*/
//PWM X
#define ARDUINO_PWM_CHANNELS_TABLE \
   ARDUINO_PWM_CHANNEL_INDEX(ARDUINO_PWM_CHANNEL_0) \
   ARDUINO_PWM_CHANNEL_INDEX(ARDUINO_PWM_CHANNEL_1) \
   ARDUINO_PWM_CHANNEL_INDEX(ARDUINO_PWM_CHANNEL_2) \

//ADC X
#define ARDUINO_ADC_CHANNELS_TABLE \
   ARDUINO_ADC_CHANNEL_INDEX(ARDUINO_ADC_CHANNEL_0) \
   ARDUINO_ADC_CHANNEL_INDEX(ARDUINO_ADC_CHANNEL_1) \
   ARDUINO_ADC_CHANNEL_INDEX(ARDUINO_ADC_CHANNEL_2) \
//ISR X
#define ARDUINO_ISR_THREADS_TABLE \
   ARDUINO_ISR_THREAD_INDEX(ARDUINO_ISR_THREAD_0) \
   ARDUINO_ISR_THREAD_INDEX(ARDUINO_ISR_THREAD_1) \
   ARDUINO_ISR_THREAD_INDEX(ARDUINO_ISR_THREAD_2) \

//UART
#define ARDUINO_UART_CHANNELS_TABLE \
   ARDUINO_UART_CHANNEL_INDEX(ARDUINO_UART_CHANNEL_0) \

#define ARDUINO_UART_BAUDRATE ((uint32_t) 19200UL)

//DIO
#define ARDUINO_DIO_CHANNELS_TABLE \
   ARDUINO_DIO_CHANNEL_INDEX(ARDUINO_DIO_CHANNEL_0) \
   ARDUINO_DIO_CHANNEL_INDEX(ARDUINO_DIO_CHANNEL_1) \
/*=====================================================================================* 
 * Exported Define Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Type Declarations
 *=====================================================================================*/

/*=====================================================================================* 
 * api_uset.h
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/

#endif /*ARDUINO_FWK_USET_H_*/
