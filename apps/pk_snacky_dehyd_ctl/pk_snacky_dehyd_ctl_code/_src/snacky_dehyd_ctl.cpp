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
#include "snack_power_mode.h"
#include "snacky_dehyd_ctl.h"

#include "../../../../include/pid_ctl_set.h"
#include "../../../../support/atmel_asf/pk_arduino_fwk_code/_inc/arduino_fwk_clk.h"
#include "../../../../support/chimney_ctl/pk_chimney_ctl_user/chimney_ctl.h"
#include "../../../../support/heater_resistor_ctl/pk_daylight_monitor/pk_daylight_monitor_user/daylight_monitor.h"
#include "../../../../support/pid_controller/pk_pid_ctl_user/pid_ctl.h"
#include "../../../../support/temp_sensor/pk_temp_monitor_user/temp_monitor.h"
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
#define SNACK_DEHYD_CTL_MIN_TEMP (110000)
#define SNACK_DEHYD_CTL_MAX_TEMP (118000)
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
void snack_dehyd::Init(void)
{
   TR_INFO("snack_dehyd::Init");
   pid::Set_Point(PID_CTL_CHANNEL_FAN_DOOR, SNACK_DEHYD_CTL_MAX_TEMP);
   pid::Set_Point(PID_CTL_CHANNEL_HEATER, SNACK_DEHYD_CTL_MIN_TEMP);
   pmode::Set_State(PMODE_ALL_ON);
}

void snack_dehyd::Main(void)
{
   if(SNACK_DEHYD_CTL_MIN_TEMP < temp_mon::Get_Temperature())
   {
      pid::Run(PID_CTL_CHANNEL_HEATER);
      chim::Set_State(CHIMNEY_CLOSED);

      pid::Stop(PID_CTL_CHANNEL_FAN_DOOR);
   }
   else if(SNACK_DEHYD_CTL_MAX_TEMP < temp_mon::Get_Temperature())
   {
      pid::Run(PID_CTL_CHANNEL_FAN_DOOR);
      chim::Set_State(CHIMNEY_OPEN);
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
   pmode::Set_State(PMODE_AC_OFF);
   pid::Stop(PID_CTL_CHANNEL_FAN_DOOR);
   pid::Stop(PID_CTL_CHANNEL_HEATER);
}
/*=====================================================================================* 
 * snack_power_mode.cpp
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/



