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
#include <iostream>
#include <ctime>
/*=====================================================================================* 
 * Local X-Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Define Macros
 *=====================================================================================*/
#undef ARDUINO_ADC_CHANNEL_INDEX
#undef ARDUINO_DIO_CHANNEL_INDEX
#undef ARDUINO_UART_CHANNEL_INDEX
#undef ARDUINO_PWM_CHANNEL_INDEX
#undef ARDUINO_ISR_THREAD_INDEX

#define ARDUINO_ADC_CHANNEL_INDEX(ch)  ARDUINO_CHANNEL_INDEX(ch)
#define ARDUINO_DIO_CHANNEL_INDEX(ch)  ARDUINO_CHANNEL_INDEX(ch)
#define ARDUINO_UART_CHANNEL_INDEX(ch) ARDUINO_CHANNEL_INDEX(ch)
#define ARDUINO_PWM_CHANNEL_INDEX(ch)  ARDUINO_CHANNEL_INDEX(ch)
#define ARDUINO_ISR_THREAD_INDEX(ch)   ARDUINO_CHANNEL_INDEX(ch)
#define ARDUINO_DIO_CHANNEL_INDEX(ch)  ARDUINO_CHANNEL_INDEX(ch)
#define ARDUINO_UART_CHANNEL_INDEX(ch) ARDUINO_CHANNEL_INDEX(ch)
#define ARDUINO_PWM_CHANNEL_INDEX(ch)  ARDUINO_CHANNEL_INDEX(ch)

#undef ARDUINO_CHANNEL_INDEX
#define ARDUINO_CHANNEL_INDEX(ch) #ch,
/*=====================================================================================* 
 * Local Type Definitions
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Object Definitions
 *=====================================================================================*/

const char * Arduino_ADC_Channel_Names[] =
{
      ARDUINO_ADC_CHANNELS_TABLE
};
const char * Arduino_DIO_Channel_Names[] =
{
      ARDUINO_DIO_CHANNELS_TABLE
};

const char * Arduino_UART_Channel_Names[] =
{
      ARDUINO_UART_CHANNELS_TABLE
};

const char * Arduino_PWM_Channel_Names[] =
{
      ARDUINO_PWM_CHANNELS_TABLE
};

const char* Arduino_ISR_Threads_Names[] =
{
      ARDUINO_ISR_THREADS_TABLE
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
//Framework
void arduino::Shut(void)
{
	std::cout << __FUNCTION__ << std::endl;
}
void arduino::Init(void)
{
   std::cout << __FUNCTION__ << std::endl;
}

//CLK
void arduino::Init_Clk(void)
{
	std::cout << __FUNCTION__ << std::endl;
}
uint32_t arduino::Get_Clk(void)
{
   uint32_t cl = static_cast<uint32_t>( clock() )* 10;
   return cl;
}

void arduino::Init_Tone(const ARDUINO_DIO_CHANNEL_T pin)
{
   std::cout << __FUNCTION__ << ":" << pin << std::endl;
}
void arduino::Set_Tone(const ARDUINO_DIO_CHANNEL_T pin, uint16_t freq)
{
   std::cout << __FUNCTION__ << ":" << freq << std::endl;
}
void arduino::Stop_Tone(const ARDUINO_DIO_CHANNEL_T pin){std::cout << __FUNCTION__ << std::endl;}

//ADC Stubs
void arduino::Init_ADC(const ARDUINO_ADC_CHANNEL_T channel){std::cout << __FUNCTION__ << std::endl;}
uint16_t arduino::Get_ADC(const ARDUINO_ADC_CHANNEL_T channel){std::cout << __FUNCTION__ << std::endl;return 0;}
void arduino::Stop_ADC(const ARDUINO_ADC_CHANNEL_T channel){std::cout << __FUNCTION__ << std::endl;}

//DIO Stubs
void arduino::Init_DIO(const ARDUINO_DIO_CHANNEL_T pin, uint8_t mode){std::cout << __FUNCTION__ << std::endl;}
void arduino::Set_DIO(const ARDUINO_DIO_CHANNEL_T pin,const uint8_t value){std::cout << __FUNCTION__ << std::endl;}
uint8_t arduino::Get_DIO(const ARDUINO_DIO_CHANNEL_T pin){std::cout << __FUNCTION__ << std::endl; return 0;}
void arduino::Shut_DIO(const ARDUINO_DIO_CHANNEL_T pin){std::cout << __FUNCTION__ << std::endl;}

//ISR Stubs
void arduino::Init_ISR(const ARDUINO_ISR_THREAD_T channel){}
void arduino::Set_ISR(const ARDUINO_ISR_THREAD_T channel, Arduino_ISR_T isr, const uint32_t timer){std::cout << __FUNCTION__ << std::endl; isr();}
void arduino::Run_ISR(const ARDUINO_ISR_THREAD_T channel){std::cout << __FUNCTION__ << std::endl;}
void arduino::Stop_ISR(const ARDUINO_ISR_THREAD_T channel){std::cout << __FUNCTION__ << std::endl;}

//LCD
void arduino::Init_LCD(void){std::cout << __FUNCTION__ << std::endl;}
void arduino::Set_LCD(Arduino_LCD_T const & lcd){std::cout << __FUNCTION__ << std::endl;}
void arduino::Print_LCD(Arduino_LCD_T & lcd, uint8_t * data_print, size_t lenght){std::cout << __FUNCTION__ << std::endl;}
void arduino::Stop_LCD(void){std::cout << __FUNCTION__ << std::endl;}

//PWM Stubs
void arduino::Init_PWM(const ARDUINO_PWM_CHANNEL_T channel){std::cout << __FUNCTION__ << std::endl;}
void arduino::Set_PWM(const ARDUINO_PWM_CHANNEL_T channel, const uint8_t output){std::cout << __FUNCTION__ << std::endl;}
void arduino::Stop_PWM(const ARDUINO_PWM_CHANNEL_T channel){std::cout << __FUNCTION__ << std::endl;}

void arduino::Init_SD(void){std::cout << __FUNCTION__ << std::endl;}
bool arduino::Open_File(const char * file_name, uint8_t perms){std::cout << __FUNCTION__ << std::endl;return true;}
void arduino::Close_File(void){std::cout << __FUNCTION__ << std::endl;}
void arduino::Write_SD(const char c){std::cout << __FUNCTION__ << std::endl;}
void arduino::Print_Str_SD(const char * str){std::cout << __FUNCTION__ << std::endl;}
void arduino::Print_Int_SD(const int d){std::cout << __FUNCTION__ << std::endl;}
void arduino::Shut_SD(void){std::cout << __FUNCTION__ << std::endl;}

//UART
void arduino::Init_UART(Arduino_UART_T const & uart){std::cout << __FUNCTION__ << std::endl;}
void arduino::Put_UART(Arduino_UART_T const & uart, const uint8_t c){std::cout << __FUNCTION__ << std::endl;}
void arduino::Print_UART(Arduino_UART_T const & uart, const char * printed){std::cout << __FUNCTION__ << std::endl;}
uint8_t arduino::Get_UART(Arduino_UART_T const & uart){std::cout << __FUNCTION__ << std::endl;return 0;}
uint16_t arduino::Get_Available_UART(Arduino_UART_T const & uart){std::cout << __FUNCTION__ << std::endl;return 0;}
void arduino::Flush_UART(Arduino_UART_T const & uart){std::cout << __FUNCTION__ << std::endl;}
void arduino::Stop_UART(Arduino_UART_T const & uart){std::cout << __FUNCTION__ << std::endl;}

/*=====================================================================================* 
 * arduino_fwk_stubs.cpp
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/

