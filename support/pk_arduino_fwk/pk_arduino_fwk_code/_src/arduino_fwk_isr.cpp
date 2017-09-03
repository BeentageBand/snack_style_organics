/*=====================================================================================*/
/**
 * arduino_fwk_isr.cpp
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
#include "arduino_fwk_isr.h"
/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/
#include "Arduino.h"
/*=====================================================================================* 
 * Local X-Macros
 *=====================================================================================*/
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
/*=====================================================================================* 
 * Local Define Macros
 *=====================================================================================*/
#define ARDUINO_ISR_PERIOD ((float)0.0005)
/*=====================================================================================* 
 * Local Type Definitions
 *=====================================================================================*/
typedef struct
{
   Arduino_ISR_T isr;
   uint16_t      count;
   uint32_t      msecs;
   bool          overflowing;
}ISR_Handler_T;

/*=====================================================================================* 
 * Local Object Definitions
 *=====================================================================================*/
static volatile ISR_Handler_T ISR_Handler[ARDUINO_ISR_MAX_THREADS] = {0};
static uint8_t  Timer_Counter = 0;
/*=====================================================================================* 
 * Exported Object Definitions
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Prototypes
 *=====================================================================================*/
static void On_Overflow(volatile ISR_Handler_T & isr);
/*=====================================================================================* 
 * Local Inline-Function Like Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Definitions
 *=====================================================================================*/
ISR(TIMER2_OVF_vect)
{
   TCNT2 = Timer_Counter;

   for(uint8_t i = 0; i < ARDUINO_ISR_MAX_THREADS; ++i)
   {
      if(0 != ISR_Handler[i].isr)
      {
         On_Overflow( ISR_Handler[i] );
      }
   }
}

void On_Overflow(volatile ISR_Handler_T & isr)
{
   ++isr.count;

   if (isr.count >=isr.msecs && !isr.overflowing) {
      isr.overflowing = 1;
      isr.count = isr.count - isr.msecs; // subtract ms to catch missed overflows
               // set to 0 if you don't want this.
      isr.isr();
      isr.overflowing = 0;
   }
}
/*=====================================================================================* 
 * Exported Function Definitions
 *=====================================================================================*/
void arduino::Init_ISR(const ARDUINO_ISR_THREAD_T thread)
{
   if(thread < ARDUINO_ISR_MAX_THREADS)
   {
      float prescaler = 0.0;

      TIMSK2 &= ~(1<<TOIE2);
      TCCR2A &= ~((1<<WGM21) | (1<<WGM20));
      TCCR2B &= ~(1<<WGM22);
      ASSR &= ~(1<<AS2);
      TIMSK2 &= ~(1<<OCIE2A);

      if ((F_CPU >= 1000000UL) && (F_CPU <= 16000000UL)) {  // prescaler set to 64
         TCCR2B |= (1<<CS22);
         TCCR2B &= ~((1<<CS21) | (1<<CS20));
         prescaler = 64.0;
      } else if (F_CPU < 1000000UL) {  // prescaler set to 8
         TCCR2B |= (1<<CS21);
         TCCR2B &= ~((1<<CS22) | (1<<CS20));
         prescaler = 8.0;
      } else { // F_CPU > 16Mhz, prescaler set to 128
         TCCR2B |= ((1<<CS22) | (1<<CS20));
         TCCR2B &= ~(1<<CS21);
         prescaler = 128.0;
      }

      Timer_Counter = 256 - (int)((float)F_CPU * ARDUINO_ISR_PERIOD / prescaler);
   }
}
void arduino::Set_ISR(const ARDUINO_ISR_THREAD_T thread, Arduino_ISR_T isr, const uint32_t timer)
{
   if(thread < ARDUINO_ISR_MAX_THREADS)
   {

      if (timer == 0)
      {
         ISR_Handler[thread].msecs = 1;
      }
      else
      {
         ISR_Handler[thread].msecs = timer;
      }

      ISR_Handler[thread].isr = isr;
   }
}
void arduino::Run_ISR(const ARDUINO_ISR_THREAD_T thread)
{
   if(thread < ARDUINO_ISR_MAX_THREADS)
   {
      ISR_Handler[thread].count = 0;
      ISR_Handler[thread].overflowing = 0;
      TCNT2 = Timer_Counter;
      TIMSK2 |= (1<<TOIE2);
   }
}
void arduino::Stop_ISR(const ARDUINO_ISR_THREAD_T channel)
{
   TIMSK2 &= ~(1<<TOIE2);
}
/*=====================================================================================* 
 * arduino_fwk_isr.cpp
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
