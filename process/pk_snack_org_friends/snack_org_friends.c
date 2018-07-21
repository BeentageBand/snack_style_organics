/*=====================================================================================*/
/**
 * pid_ctl_frs.cpp
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
#ifdef ENABLE_SSO
#include "arduino_fwk_clk.h"
#include "axial_fan_ctl.h"
#include "heater_ctl.h"
#include "pid_ctl_ext.h"
#include "temp_monitor.h"
#endif
#include "snack_org_friends.h"

void Snack_Style_Organics_Init(void)
{

}

#ifdef ENABLE_SSO
Fix32_T pid::Get_PID_CTL_CHANNEL_FAN_DOOR()
{
   return static_cast<Fix32_T>(PID_CTL_FIX32_PARSE_FACTOR*temp_mon::Get_Temperature() );
}
Fix32_T pid::Get_PID_CTL_CHANNEL_HEATER()
{
   return static_cast<Fix32_T>(PID_CTL_FIX32_PARSE_FACTOR*temp_mon::Get_Temperature() );
}

void pid::Put_PID_CTL_CHANNEL_FAN_DOOR(const Fix32_T uout)
{
   uint8_t fan_out = (uout/PID_CTL_FIX32_PARSE_FACTOR);
   fan::Set_Output(fan_out);
}

void pid::Put_PID_CTL_CHANNEL_HEATER(const Fix32_T uout)
{
   uint8_t pwm_out = (uout/PID_CTL_FIX32_PARSE_FACTOR);
   heater::Set_Output(pwm_out);
}


uint32_t pid::Get_Sample_Time(void)
{
   return arduino::Get_Clk();
}
#endif