/*=====================================================================================*/
/**
 * snack_power_mode.cpp
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
#include "arduino_fwk_clk.h"
#include "arduino_fwk_dio.h"
#include "arduino_fwk_isr.h"
#include "snack_style_gpio.h"
#include "snack_power_mode_ext.h"
#include "snack_power_mode_types.h"
/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/

/*=====================================================================================* 
 * Local X-Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Define Macros
 *=====================================================================================*/
#define PMODE_SOURCE_AC_60HZ (16) //120 HZ nyquist
#define PMODE_SOURCE_NEG_1KHZ (2) //2kHz  nyquist
#define PMODE_TICK_PERIOD_US    (500) // Tick 5 us
#define PMODE_SOURCE_AC_60HZ_THREAD (ARDUINO_ISR_THREAD_0)
#define PMODE_SOURCE_NEG_1kHZ_THREAD (ARDUINO_ISR_THREAD_1)

#define OUTPUT_LINE (1)
/*=====================================================================================* 
 * Local Type Definitions
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Object Definitions
 *=====================================================================================*/
static bool AC_Source_Is_Running = false;
static bool AC_Source_Signal_H_State = false;
static bool AC_Source_Signal_L_State = false;

static bool NEG_Source_Is_Running = false;
static bool NEG_Source_Signal = false;
/*=====================================================================================* 
 * Exported Object Definitions
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Prototypes
 *=====================================================================================*/
#undef PMODE_SOURCE
#define PMODE_SOURCE(src, osc) \
   static void src##_start(void); \
   static void src##_stop(void);
POWER_MODE_SOURCES_TB

static void PMode_AC_Run(void);
static void PMode_NEG_5V_Run(void);

/*=====================================================================================* 
 * Local Inline-Function Like Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Definitions
 *=====================================================================================*/
// Source defs
void PMODE_SOURCE_AC_start(void)
{
   AC_Source_Is_Running =true;

   AC_Source_Signal_H_State = true;
   AC_Source_Signal_L_State = false;
}

void PMODE_SOURCE_AC_stop(void)
{
   AC_Source_Is_Running = false;

   AC_Source_Signal_H_State = false;
   AC_Source_Signal_L_State = false;
   arduino::Set_DIO(SNACK_GPIO_AC_H_120HZ, AC_Source_Signal_H_State);
   arduino::Set_DIO(SNACK_GPIO_AC_L_120HZ, AC_Source_Signal_L_State);

}
void PMODE_SOURCE_NEG_DC_start(void)
{
   NEG_Source_Is_Running = true;
}

void PMODE_SOURCE_NEG_DC_stop(void)
{
   NEG_Source_Is_Running = false;
}

void PMode_AC_Run(void)
{
      AC_Source_Signal_H_State = AC_Source_Signal_H_State ^ AC_Source_Is_Running;
      AC_Source_Signal_L_State = AC_Source_Signal_L_State ^ AC_Source_Is_Running;
      arduino::Set_DIO(SNACK_GPIO_AC_H_120HZ, AC_Source_Signal_H_State);
      arduino::Set_DIO(SNACK_GPIO_AC_L_120HZ, AC_Source_Signal_L_State);
}

void PMode_NEG_5V_Run(void)
{
      NEG_Source_Signal = NEG_Source_Signal ^ NEG_Source_Signal;
      arduino::Set_DIO(SNACK_GPIO_NEG_5V_1KHZ, NEG_Source_Signal);
}
/*=====================================================================================* 
 * Exported Function Definitions
 *=====================================================================================*/
void pmode::PMODE_SOURCE_AC_init(void)
{
   arduino::Init_ISR(PMODE_SOURCE_AC_60HZ_THREAD);
   arduino::Init_DIO(SNACK_GPIO_AC_H_120HZ, OUTPUT_LINE);
   arduino::Init_DIO(SNACK_GPIO_AC_L_120HZ, OUTPUT_LINE);
   arduino::Set_ISR(PMODE_SOURCE_AC_60HZ_THREAD, PMode_AC_Run, PMODE_SOURCE_AC_60HZ);
}

void pmode::PMODE_SOURCE_NEG_DC_init(void)
{
   arduino::Init_DIO(SNACK_GPIO_NEG_5V_1KHZ, OUTPUT_LINE);
   arduino::Set_ISR(PMODE_SOURCE_NEG_1kHZ_THREAD, PMode_NEG_5V_Run, PMODE_SOURCE_NEG_1KHZ);
}

void pmode::Enter_PMODE_AC_OFF(void)
{}

void pmode::Enter_PMODE_ALL_OFF_STATE(void)
{
   PMODE_SOURCE_NEG_DC_stop();
   arduino::Stop_ISR(PMODE_SOURCE_AC_60HZ_THREAD);
}

void pmode::Enter_PMODE_ALL_ON(void)
{
   PMODE_SOURCE_AC_start();
}

void pmode::Exit_PMODE_AC_OFF(void)
{}

void pmode::Exit_PMODE_ALL_OFF_STATE(void)
{
   PMODE_SOURCE_NEG_DC_start();
   arduino::Run_ISR(PMODE_SOURCE_AC_60HZ_THREAD);
}


void pmode::Exit_PMODE_ALL_ON(void)
{
   PMODE_SOURCE_AC_stop();
}
/*=====================================================================================* 
 * snack_power_mode.cpp
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
