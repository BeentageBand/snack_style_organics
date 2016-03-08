/*=====================================================================================*/
/**
 * snack_style_gpio.h
 * author : puch
 * date : Oct 22 2015
 *
 * description : Any comments
 *
 */
/*=====================================================================================*/
#ifndef SNACK_STYLE_GPIO_H_
#define SNACK_STYLE_GPIO_H_
/*=====================================================================================*
 * Project Includes
 *=====================================================================================*/

/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported X-Macros
 *=====================================================================================*/
//DIO

#define SNACK_GPIO_UART_RXD          (ARDUINO_DIO_CHANNEL_0)
#define SNACK_GPIO_UART_TXD          (ARDUINO_DIO_CHANNEL_1)
#define SNACK_GPIO_NEG_5V_1KHZ       (ARDUINO_DIO_CHANNEL_2)
#define SNACK_GPIO_AC_H_120HZ        (ARDUINO_DIO_CHANNEL_3)
#define SNACK_GPIO_AC_L_120HZ        (ARDUINO_DIO_CHANNEL_4)
#define SNACK_GPIO_FAN_PWM           (ARDUINO_DIO_CHANNEL_5)
#define SNACK_GPIO_RES_PWM           (ARDUINO_DIO_CHANNEL_6)
#define SNACK_GPIO_DC_MOTOR_H        (ARDUINO_DIO_CHANNEL_7)
#define SNACK_GPIO_DC_MOTOR_L        (ARDUINO_DIO_CHANNEL_8)
#define SNACK_GPIO_LCD_EN            (ARDUINO_DIO_CHANNEL_9)
#define SNACK_GPIO_LCD_D4            (ARDUINO_DIO_CHANNEL_10)
#define SNACK_GPIO_LCD_D5            (ARDUINO_DIO_CHANNEL_11)
#define SNACK_GPIO_LCD_D6            (ARDUINO_DIO_CHANNEL_12)
#define SNACK_GPIO_LCD_D7            (ARDUINO_DIO_CHANNEL_13)
#define SNACK_GPIO_ADC_TEMP_AVG      (ARDUINO_DIO_CHANNEL_14)
#define SNACK_GPIO_ADC_LIGHT_AVG     (ARDUINO_DIO_CHANNEL_15)
#define SNACK_GPIO_ADC_FAN_OUT       (ARDUINO_DIO_CHANNEL_16)
#define SNACK_GPIO_ADC_RES_OUT       (ARDUINO_DIO_CHANNEL_17)
#define SNACK_GPIO_ADC_BATT          (ARDUINO_DIO_CHANNEL_18)
#define SNACK_GPIO_ADC_TEMP_OUTDOORS (ARDUINO_DIO_CHANNEL_19)

/*=====================================================================================* 
 * Exported Define Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Type Declarations
 *=====================================================================================*/

/*=====================================================================================* 
 * snack_style_gpio.h
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/

#endif /*snack_style_gpio*/
