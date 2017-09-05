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
#include "../include/snack_style_gpio.h"
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
   ARDUINO_PWM_CHANNEL_INDEX(ARDUINO_PWM_CHANNEL_3) \
   ARDUINO_PWM_CHANNEL_INDEX(ARDUINO_PWM_CHANNEL_4) \
   ARDUINO_PWM_CHANNEL_INDEX(ARDUINO_PWM_CHANNEL_5) \

//ADC X
#define ARDUINO_ADC_CHANNELS_TABLE \
   ARDUINO_ADC_CHANNEL_INDEX(ARDUINO_ADC_CHANNEL_0) \
   ARDUINO_ADC_CHANNEL_INDEX(ARDUINO_ADC_CHANNEL_1) \
   ARDUINO_ADC_CHANNEL_INDEX(ARDUINO_ADC_CHANNEL_2) \
//ISR X
#define ARDUINO_ISR_THREADS_TABLE \
   ARDUINO_ISR_THREAD_INDEX(ARDUINO_ISR_THREAD_0) \
   ARDUINO_ISR_THREAD_INDEX(ARDUINO_ISR_THREAD_1) \

//UART
#define ARDUINO_UART_CHANNELS_TABLE \
   ARDUINO_UART_CHANNEL_INDEX(ARDUINO_UART_CHANNEL_0) \

#define ARDUINO_UART_BAUDRATE ((uint32_t) 19200UL)

//DIO
#define ARDUINO_DIO_CHANNELS_TABLE \
   ARDUINO_DIO_CHANNEL_INDEX(ARDUINO_DIO_CHANNEL_0) \
   ARDUINO_DIO_CHANNEL_INDEX(ARDUINO_DIO_CHANNEL_1) \
   ARDUINO_DIO_CHANNEL_INDEX(ARDUINO_DIO_CHANNEL_2) \
   ARDUINO_DIO_CHANNEL_INDEX(ARDUINO_DIO_CHANNEL_3) \
   ARDUINO_DIO_CHANNEL_INDEX(ARDUINO_DIO_CHANNEL_4) \
   ARDUINO_DIO_CHANNEL_INDEX(ARDUINO_DIO_CHANNEL_5) \
   ARDUINO_DIO_CHANNEL_INDEX(ARDUINO_DIO_CHANNEL_6) \
   ARDUINO_DIO_CHANNEL_INDEX(ARDUINO_DIO_CHANNEL_7) \
   ARDUINO_DIO_CHANNEL_INDEX(ARDUINO_DIO_CHANNEL_8) \
   ARDUINO_DIO_CHANNEL_INDEX(ARDUINO_DIO_CHANNEL_9) \
   ARDUINO_DIO_CHANNEL_INDEX(ARDUINO_DIO_CHANNEL_10) \
   ARDUINO_DIO_CHANNEL_INDEX(ARDUINO_DIO_CHANNEL_11) \
   ARDUINO_DIO_CHANNEL_INDEX(ARDUINO_DIO_CHANNEL_12) \
   ARDUINO_DIO_CHANNEL_INDEX(ARDUINO_DIO_CHANNEL_13) \
   /*ANALOG IO*/ \
   ARDUINO_DIO_CHANNEL_INDEX(ARDUINO_DIO_CHANNEL_14) \
   ARDUINO_DIO_CHANNEL_INDEX(ARDUINO_DIO_CHANNEL_15) \
   ARDUINO_DIO_CHANNEL_INDEX(ARDUINO_DIO_CHANNEL_16) \
   ARDUINO_DIO_CHANNEL_INDEX(ARDUINO_DIO_CHANNEL_17) \
   ARDUINO_DIO_CHANNEL_INDEX(ARDUINO_DIO_CHANNEL_18) \
   ARDUINO_DIO_CHANNEL_INDEX(ARDUINO_DIO_CHANNEL_19) \

//LCD
#define ARDUINO_LCD_RS   SNACK_GPIO_LCD_RS
#define ARDUINO_LCD_EN   SNACK_GPIO_LCD_EN
#define ARDUINO_LCD_D4   SNACK_GPIO_LCD_D4
#define ARDUINO_LCD_D5   SNACK_GPIO_LCD_D5
#define ARDUINO_LCD_D6   SNACK_GPIO_LCD_D6
#define ARDUINO_LCD_D7   SNACK_GPIO_LCD_D7

#define ARDUINO_LCD_MAX_ROWS 2
#define ARDUINO_LCD_MAX_COLS 16


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
