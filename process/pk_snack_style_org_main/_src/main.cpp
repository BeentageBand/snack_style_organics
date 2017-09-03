/*
 * snack_style_organics.cpp
 *
 * Created: 07/01/2016 12:51:27 a.m.
 * Author : ASUS
 */ 

/*================================================================================================*
 * Project Includes
 *================================================================================================*/
#include "arduino_fwk_dio.h"
#include "arduino_fwk_clk.h"
#include "hamatora_sched_def.h"
#include "hamatora_sched.h"
#include "hamatora_sched_ext.h"
#include "hama_dbg_trace.h"
#include "std_def.h"
/*================================================================================================*
 * Standard Includes
 *================================================================================================*/
#include <stdlib.h>

/*================================================================================================*
 * Local Prototypes
 *================================================================================================*/
static void Init_Test(void);
static void Main_Test(void);
/*================================================================================================*
 * Local Object Definitions
 *================================================================================================*/
#undef HAMA_SCHED_APP
#define HAMA_SCHED_APP(app, init, run, stop) \
const Hama_Apps_T App_##app PROGMEM = \
{\
   app, init, run, stop \
};\

HAMA_SCHED_APPS_TABLE

#undef HAMA_SCHED_APP
#define HAMA_SCHED_APP(app, init, run, stop) &App_##app,

const Hama_Apps_T * const Scheduled_Apps[] PROGMEM=
{
   HAMA_SCHED_APPS_TABLE
};

const uint8_t Num_Of_Scheduled_Apps PROGMEM = HAMA_MAX_APPS_ID;

const char Hello_Test[] PROGMEM = "Hello_P \n\r\0";

/*================================================================================================*
 * Local Main Definition
 *================================================================================================*/
void Init_Test(void)
{
   arduino::Init_DIO(ARDUINO_DIO_CHANNEL_13,ARDUINO_DIO_OUTPUT_MODE);
}

void Main_Test(void)
{
   //arduino::Sleep(500);
   //arduino::Set_DIO(ARDUINO_DIO_CHANNEL_13,0);

   //arduino::Sleep(500);
   //arduino::Set_DIO(ARDUINO_DIO_CHANNEL_5,1);

#ifndef HOST
   arduino::Print_UART(dbg::UART_Init.channel, "Hello \n\r");
   arduino::Print_UART_P(dbg::UART_Init.channel, Hello_Test);
#endif
   TR_INFO("Start Snack Style Organics");
}
/*================================================================================================*
 * Local Main Definition
 *================================================================================================*/

int main(void)
{
   arduino::Init();
   dbg::Init();

   hama::Run_All_Apps();
   return 0;
}

