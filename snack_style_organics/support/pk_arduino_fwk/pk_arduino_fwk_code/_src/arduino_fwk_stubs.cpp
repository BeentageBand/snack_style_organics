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
#include "hama_dbg_trace.h"
/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/
#include <iostream>
#include <ctime>
#include <unistd.h>
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
typedef struct
{
   pthread_t thread;
   pthread_attr_t attr;
   Arduino_ISR_T isr;
   uint32_t tout;
}ISR_Stub_T;
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

#undef ARDUINO_ISR_THREAD_INDEX
#define ARDUINO_ISR_THREAD_INDEX(ch) {0,0,0,0},
ISR_Stub_T Isr_Threads[] =
{
      ARDUINO_ISR_THREADS_TABLE
};
/*=====================================================================================* 
 * Exported Object Definitions
 *=====================================================================================*/
#undef ARDUINO_DIO_CHANNEL_INDEX
#define ARDUINO_DIO_CHANNEL_INDEX(ch) 0,
static uint8_t Dio_Channel_States[] =
{
   ARDUINO_DIO_CHANNELS_TABLE
};
/*=====================================================================================* 
 * Local Function Prototypes
 *=====================================================================================*/
static void * Thread_Stub(void * args);
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
   TR_INFO(__FUNCTION__);
}
void arduino::Init(void)
{
   TR_INFO(__FUNCTION__);
}
void arduino::Main(void)
{
   TR_INFO(__FUNCTION__);
}

//CLK
void arduino::Init_Clk(void)
{
   TR_INFO(__FUNCTION__);
}
uint32_t arduino::Get_Clk(void)
{
   uint32_t cl = static_cast<uint32_t>( clock() )* 10;
   TR_INFO_1(" get - clock = %d", cl);
   return cl;
}


void arduino::Sleep(const uint32_t ms){usleep(ms*1000);}
void arduino::Usleep(const uint32_t us){usleep(us);}

void arduino::Init_Tone(const ARDUINO_DIO_CHANNEL_T pin)
{
   std::cout << __FUNCTION__ << ":" << pin << std::endl;
}
void arduino::Set_Tone(const ARDUINO_DIO_CHANNEL_T pin, uint16_t freq)
{
   std::cout << __FUNCTION__ << ":" << freq << std::endl;
}
void arduino::Stop_Tone(const ARDUINO_DIO_CHANNEL_T pin){TR_INFO(__FUNCTION__);}

//ADC Stubs
void arduino::Init_ADC(const ARDUINO_ADC_CHANNEL_T channel){TR_INFO(__FUNCTION__);}
uint16_t arduino::Get_ADC(const ARDUINO_ADC_CHANNEL_T channel){TR_INFO(__FUNCTION__);return 0;}
void arduino::Stop_ADC(const ARDUINO_ADC_CHANNEL_T channel){TR_INFO(__FUNCTION__);}

//DIO Stubs

void arduino::Init_DIO(const ARDUINO_DIO_CHANNEL_T pin, uint8_t mode)
{
   TR_INFO_3("%s pin %d mode %d",__FUNCTION__,pin, mode);
}
void arduino::Set_DIO(const ARDUINO_DIO_CHANNEL_T pin,const uint8_t value)
{
   TR_INFO_3("%s pin %d state %x",__FUNCTION__,pin, value);
   Dio_Channel_States[pin] = value;
}
uint8_t arduino::Get_DIO(const ARDUINO_DIO_CHANNEL_T pin)
{
   TR_INFO_3("%s pin %d state %x",__FUNCTION__,pin, Dio_Channel_States[pin]);
   return Dio_Channel_States[pin];
}
void arduino::Shut_DIO(const ARDUINO_DIO_CHANNEL_T pin){TR_INFO_2("%s pin %d",__FUNCTION__, pin);}

//ISR Stubs
void arduino::Init_ISR(const ARDUINO_ISR_THREAD_T channel)
{
   TR_INFO_2("%s thread %d", __FUNCTION__, channel);
   pthread_attr_init(&Isr_Threads[channel].attr);
}
void arduino::Set_ISR(const ARDUINO_ISR_THREAD_T channel, Arduino_ISR_T isr, const uint32_t timer)
{
   TR_INFO_2("%s thread %d", __FUNCTION__, channel);
   Isr_Threads[channel].isr = isr;
   Isr_Threads[channel].tout = timer;
}
void arduino::Run_ISR(const ARDUINO_ISR_THREAD_T channel)
{
   TR_INFO_2("%s thread %d", __FUNCTION__, channel);
   pthread_create(&Isr_Threads[channel].thread, &Isr_Threads[channel].attr, Thread_Stub,
         &Isr_Threads[channel]);
}
void arduino::Stop_ISR(const ARDUINO_ISR_THREAD_T channel)
{
   TR_INFO_2("%s thread %d", __FUNCTION__, channel);
   pthread_join(Isr_Threads[channel].thread,0);
}

void * Thread_Stub(void * args)
{
   ISR_Stub_T stub_arg = *(ISR_Stub_T*)args;
   TR_INFO(__FUNCTION__);
   clock_t cl  = clock();
   while(true)
   {
      if((clock() - cl) > stub_arg.tout )
      {
         cl  = clock();
         stub_arg.isr();
      }
   }
   return 0;
}

//LCD
void arduino::Init_LCD(void){TR_INFO(__FUNCTION__);}
void arduino::Set_LCD(Arduino_LCD_T const & lcd){TR_INFO(__FUNCTION__);}
void arduino::Print_LCD(Arduino_LCD_T const  & lcd, const char * data_print){TR_INFO(__FUNCTION__);}
void arduino::Stop_LCD(void){TR_INFO(__FUNCTION__);}

//PWM Stubs
void arduino::Init_PWM(const ARDUINO_PWM_CHANNEL_T channel){TR_INFO(__FUNCTION__);}
void arduino::Set_PWM(const ARDUINO_PWM_CHANNEL_T channel, const uint8_t output){TR_INFO(__FUNCTION__);}
void arduino::Stop_PWM(const ARDUINO_PWM_CHANNEL_T channel){TR_INFO(__FUNCTION__);}

void arduino::Init_SD(void){TR_INFO(__FUNCTION__);}
bool arduino::Open_File(const char * file_name, uint8_t perms){TR_INFO(__FUNCTION__);return true;}
void arduino::Close_File(void){TR_INFO(__FUNCTION__);}
void arduino::Write_SD(const char c){TR_INFO(__FUNCTION__);}
void arduino::Print_Str_SD(const char * str){TR_INFO(__FUNCTION__);}
void arduino::Print_Int_SD(const int d){TR_INFO(__FUNCTION__);}
void arduino::Shut_SD(void){TR_INFO(__FUNCTION__);}

//UART
void arduino::Init_UART(Arduino_UART_T const & uart){TR_INFO(__FUNCTION__);}
void arduino::Put_UART(               const ARDUINO_UART_CHANNEL_T uart, const uint8_t c){TR_INFO(__FUNCTION__);}
void arduino::Print_UART(             const ARDUINO_UART_CHANNEL_T uart, const char * printed){TR_INFO(__FUNCTION__);}
void arduino::Print_UART_P(             const ARDUINO_UART_CHANNEL_T uart, const Pgm_Char_T  PROGMEM const_c){TR_INFO(__FUNCTION__);}
void arduino::Print_UART_P(             const ARDUINO_UART_CHANNEL_T uart, const Pgm_Char_T * PROGMEM printed){TR_INFO(__FUNCTION__);}
void arduino::Print_UART(             const ARDUINO_UART_CHANNEL_T uart, const int d){TR_INFO(__FUNCTION__);}
void arduino::Print_UART(             const ARDUINO_UART_CHANNEL_T uart, const long l){TR_INFO(__FUNCTION__);}
uint8_t arduino::Get_UART(            const ARDUINO_UART_CHANNEL_T uart){TR_INFO(__FUNCTION__);return 0;}
uint16_t arduino::Get_Available_UART( const ARDUINO_UART_CHANNEL_T uart){TR_INFO(__FUNCTION__);return 0;}
void arduino::Flush_UART(             const ARDUINO_UART_CHANNEL_T uart){TR_INFO(__FUNCTION__);}
void arduino::Stop_UART(              const ARDUINO_UART_CHANNEL_T uart){TR_INFO(__FUNCTION__);}

/*=====================================================================================* 
 * arduino_fwk_stubs.cpp
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/

