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
#include "daylight_monitor.h"
#include "pid_ctl.h"
#include "pid_ctl_set.h"
#include "snack_power_mode.h"
#include "snacky_dehyd_ctl.h"
#include "temp_monitor.h"
#include "hama_dbg_trace.h"
/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/

/*=====================================================================================* 
 * Local X-Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Define Macros
 *=====================================================================================*/
#define SNACK_DEHYD_CTL_MIN_TEMP (11000)
#define SNACK_DEHYD_CTL_MAX_TEMP (11800)
/*=====================================================================================* 
 * Local Type Definitions
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Object Definitions
 *=====================================================================================*/
const Fix32_T Dehydrator_Set_Point_Temp = 0U;
static uint32_t sample_tout = 0;
/*=====================================================================================* 
 * Exported Object Definitions
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Prototypes
 *=====================================================================================*/
static void Wait_For_Sample(void);
/*=====================================================================================* 
 * Local Inline-Function Like Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Definitions
 *=====================================================================================*/
void Wait_For_Sample(void)
{
   sample_tout = arduino::Get_Clk();
   while(  (arduino::Get_Clk() -  sample_tout) < PID_CTL_TAU_COEFF_MS)
   {
      TR_INFO_2("Wait for sample %d - %d", arduino::Get_Clk(), sample_tout);
   }
}
/*=====================================================================================* 
 * Exported Function Definitions
 *=====================================================================================*/
void snack_dehyd::Init(void)
{
   pid::Set_Point(PID_CTL_CHANNEL_FAN_DOOR, Dehydrator_Set_Point_Temp);
   pid::Set_Point(PID_CTL_CHANNEL_HEATER, Dehydrator_Set_Point_Temp);
}

void snack_dehyd::Main(void)
{
   Wait_For_Sample();
   if(SNACK_DEHYD_CTL_MIN_TEMP < temp_mon::Get_Temperature())
   {
	   pid::Run(PID_CTL_CHANNEL_HEATER);
	   pid::Stop(PID_CTL_CHANNEL_FAN_DOOR);
   }
   else if(SNACK_DEHYD_CTL_MAX_TEMP < temp_mon::Get_Temperature())
   {
	   pid::Run(PID_CTL_CHANNEL_FAN_DOOR);
	   pid::Stop(PID_CTL_CHANNEL_HEATER);
   }
   else
   {
	   pid::Run(PID_CTL_CHANNEL_HEATER);
	   pid::Run(PID_CTL_CHANNEL_FAN_DOOR);
   }
}

void snack_dehyd::Shut(void)
{
   pid::Stop(PID_CTL_CHANNEL_FAN_DOOR);
   pid::Stop(PID_CTL_CHANNEL_HEATER);
}
/*=====================================================================================* 
 * snack_power_mode.cpp
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/



