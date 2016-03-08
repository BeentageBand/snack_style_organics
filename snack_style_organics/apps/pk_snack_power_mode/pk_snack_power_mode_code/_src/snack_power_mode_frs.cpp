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
   static void src##_start(const uint8_t osc_val); \
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
void PMODE_SOURCE_AC_start(const uint8_t osc_val)
{
   AC_Source_Signal_H_State = false;
   AC_Source_Signal_L_State = false;
   arduino::Run_ISR(ARDUINO_ISR_THREAD_2);
}

void PMODE_SOURCE_AC_stop(void)
{
   AC_Source_Signal_H_State = false;
   AC_Source_Signal_L_State = false;
   arduino::Stop_ISR(ARDUINO_ISR_THREAD_2);
}
void PMODE_SOURCE_NEG_DC_start(const uint8_t osc_val)
{
}

void PMODE_SOURCE_NEG_DC_stop(void)
{

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
   arduino::Set_ISR(ARDUINO_ISR_THREAD_2, PMode_AC_Run,PMODE_SOURCE_AC_60HZ);
}

void pmode::PMODE_SOURCE_NEG_DC_init(void)
{

}

void pmode::Enter_PMODE_AC_OFF(void)
{
   PMODE_SOURCE_NEG_DC_start(0);
}

void pmode::Enter_PMODE_ALL_OFF_STATE(void)
{
   PMODE_SOURCE_NEG_DC_stop();
}

void pmode::Enter_PMODE_ALL_ON(void)
{
   PMODE_SOURCE_AC_start(0);
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
