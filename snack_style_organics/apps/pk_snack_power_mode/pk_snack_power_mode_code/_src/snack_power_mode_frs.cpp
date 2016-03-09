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
#include "arduino_fwk_dio.h"
#include "arduino_fwk_isr.h"
#include "arduino_fwk_clk.h"
#include "snack_power_mode_ext.h"
#include "snack_power_mode_types.h"
#include "snack_style_gpio.h"
/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/

/*=====================================================================================* 
 * Local X-Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Define Macros
 *=====================================================================================*/
#define PMODE_SOURCE_AC_60HZ (8)
#define PMODE_SOURCE_AC_60HZ_THREAD (ARDUINO_ISR_THREAD_0)
/*=====================================================================================* 
 * Local Type Definitions
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Object Definitions
 *=====================================================================================*/
static bool AC_Source_Signal_H_State = false;
static bool AC_Source_Signal_L_State = false;

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

/*=====================================================================================* 
 * Local Inline-Function Like Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Definitions
 *=====================================================================================*/
// Source defs
void PMODE_SOURCE_AC_start(void)
{
   AC_Source_Signal_H_State = false;
   AC_Source_Signal_L_State = false;
   arduino::Run_ISR(PMODE_SOURCE_AC_60HZ_THREAD);
}

void PMODE_SOURCE_AC_stop(void)
{
   AC_Source_Signal_H_State = false;
   AC_Source_Signal_L_State = false;
   arduino::Stop_ISR(PMODE_SOURCE_AC_60HZ_THREAD);
}
void PMODE_SOURCE_NEG_DC_start(void)
{
   arduino::Set_Tone(SNACK_GPIO_NEG_5V_1KHZ, 1000);
}

void PMODE_SOURCE_NEG_DC_stop(void)
{
   arduino::Stop_Tone(SNACK_GPIO_NEG_5V_1KHZ);
}
void PMode_AC_Run(void)
{
   AC_Source_Signal_H_State = !AC_Source_Signal_H_State;
   AC_Source_Signal_L_State = !AC_Source_Signal_L_State;
   arduino::Set_DIO(SNACK_GPIO_AC_H_120HZ, AC_Source_Signal_H_State);
   arduino::Set_DIO(SNACK_GPIO_AC_L_120HZ, AC_Source_Signal_L_State);
}
/*=====================================================================================* 
 * Exported Function Definitions
 *=====================================================================================*/
void pmode::PMODE_SOURCE_AC_init(void)
{
   arduino::Set_ISR(PMODE_SOURCE_AC_60HZ_THREAD, PMode_AC_Run,PMODE_SOURCE_AC_60HZ);
}

void pmode::PMODE_SOURCE_NEG_DC_init(void)
{
   arduino::Init_Tone(SNACK_GPIO_NEG_5V_1KHZ);
}

void pmode::Enter_PMODE_AC_OFF(void)
{
   PMODE_SOURCE_NEG_DC_start();

}

void pmode::Enter_PMODE_ALL_OFF_STATE(void)
{
   PMODE_SOURCE_NEG_DC_stop();
}

void pmode::Enter_PMODE_ALL_ON(void)
{
   PMODE_SOURCE_AC_start();
}

void pmode::Exit_PMODE_AC_OFF(void)
{

}

void pmode::Exit_PMODE_ALL_OFF_STATE(void)
{

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
