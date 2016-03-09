/*=====================================================================================*/
/**
 * arduino_fwk_stubs.cpp
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
#include "arduino_fwk.h"
#include "arduino_fwk_adc.h"
#include "arduino_fwk_clk.h"
#include "arduino_fwk_dio.h"
#include "arduino_fwk_iic.h"
#include "arduino_fwk_isr.h"
#include "arduino_fwk_lcd.h"
#include "arduino_fwk_pwm.h"
#include "arduino_fwk_sd.h"
#include "arduino_fwk_spi.h"
#include "arduino_fwk_uart.h"
/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/

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
//Framework
void arduino::Shut(void){}
void arduino::Init(void){}

//CLK
void arduino::Init_Clk(void){}
uint32_t arduino::Get_Clk(void){return 0;}
void arduino::Init_Tone(const ARDUINO_DIO_CHANNEL_T pin){}
void arduino::Set_Tone(const ARDUINO_DIO_CHANNEL_T pin, uint16_t freq){}
void arduino::Stop_Tone(const ARDUINO_DIO_CHANNEL_T pin){}

//ADC Stubs
void arduino::Init_ADC(const ARDUINO_ADC_CHANNEL_T channel){}
uint16_t arduino::Get_ADC(const ARDUINO_ADC_CHANNEL_T channel){return 0;}
void arduino::Stop_ADC(const ARDUINO_ADC_CHANNEL_T channel){}

//DIO Stubs
void arduino::Init_DIO(const ARDUINO_DIO_CHANNEL_T pin, uint8_t mode){}
void arduino::Set_DIO(const ARDUINO_DIO_CHANNEL_T pin,const uint8_t value){}
uint8_t arduino::Get_DIO(const ARDUINO_DIO_CHANNEL_T pin){ return 0;}
void arduino::Shut_DIO(const ARDUINO_DIO_CHANNEL_T pin){}

//ISR Stubs
void arduino::Init_ISR(const ARDUINO_ISR_THREAD_T channel){}
void arduino::Set_ISR(const ARDUINO_ISR_THREAD_T channel, Arduino_ISR_T isr, const uint32_t timer){ isr();}
void arduino::Run_ISR(const ARDUINO_ISR_THREAD_T channel){}
void arduino::Stop_ISR(const ARDUINO_ISR_THREAD_T channel){}

//LCD
void arduino::Init_LCD(void){}
void arduino::Set_LCD(Arduino_LCD_T const & lcd){}
void arduino::Print_LCD(Arduino_LCD_T & lcd, uint8_t * data_print, size_t lenght){}
void arduino::Stop_LCD(void){}

//PWM Stubs
void arduino::Init_PWM(const ARDUINO_PWM_CHANNEL_T channel){}
void arduino::Set_PWM(const ARDUINO_PWM_CHANNEL_T channel, const uint8_t output){}
void arduino::Stop_PWM(const ARDUINO_PWM_CHANNEL_T channel){}

void arduino::Init_SD(void){}
bool arduino::Open_File(const char * file_name, uint8_t perms){return true;}
void arduino::Close_File(void){}
void arduino::Write_SD(const char c){}
void arduino::Print_Str_SD(const char * str){}
void arduino::Print_Int_SD(const int d){}
void arduino::Shut_SD(void){}

//UART
void arduino::Init_UART(Arduino_UART_T const & uart){}
void arduino::Put_UART(Arduino_UART_T const & uart, const uint8_t c){}
uint8_t arduino::Get_UART(Arduino_UART_T const & uart){return 0;}
uint16_t arduino::Get_Available_UART(Arduino_UART_T const & uart){return 0;}
void arduino::Flush_UART(Arduino_UART_T const & uart){}
void arduino::Stop_UART(Arduino_UART_T const & uart){}

/*=====================================================================================* 
 * arduino_fwk_stubs.cpp
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
