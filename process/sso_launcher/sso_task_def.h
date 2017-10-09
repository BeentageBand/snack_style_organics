/*=====================================================================================*/
/**
 * snack_style_organics_task_def.h
 * author : puch
 * date : Oct 22 2015
 *
 * description : Any comments
 *
 */
/*=====================================================================================*/
#ifndef SNACK_STYLE_ORGANICS_TASK_DEF_H_
#define SNACK_STYLE_ORGANICS_TASK_DEF_H_
/*=====================================================================================*
 * Project Includes
 *=====================================================================================*/
#include "../../../support/avr_framework/pk_arduino_fwk_user/arduino_fwk.h"
#include "../../../support/axial_fan_ctl/pk_axial_fan_ctl_user/axial_fan_ctl.h"
#include "../../../support/heater_resistor_ctl/pk_daylight_monitor/pk_daylight_monitor_user/daylight_monitor.h"
#include "../../../support/heater_resistor_ctl/pk_heater_ctl_user/heater_ctl.h"
#include "../../../support/pid_controller/pk_pid_ctl_user/pid_ctl.h"
#include "../../../support/temp_sensor/pk_temp_monitor_user/temp_monitor.h"
#include "hamatora_sched_types.h"
#include "snacky_dehyd_ctl.h"
#include "snack_org_lcd.h"
#include "snack_power_mode.h"
/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported X-Macros
 *=====================================================================================*/
#define SSO_TASKS_TABLE(SSO_TASK) \
         /* Task name,              Task Id */\
   SSO_TASK(Arduino_WN,             ARDUINO_ID,            ""  ) \
   SSO_TASK(Test_WN,                TEST_ID,               ""  ) \
   SSO_TASK(SSO_Ctl_WN,             SNACK_ORG_CTL_ID,      ""  ) \
   SSO_TASK(SSO_LCD_WN,             SNACK_ORG_LCD_ID,      ""  ) \
   SSO_TASK(Heater_Ctl_WN,          HEATER_CTL_ID,         ""  ) \
   SSO_TASK(Fan_Ctl_WN,             AXIAL_FAN_CTL_ID,      ""  ) \
   SSO_TASK(PID_Ctl_WN,             PID_CTL_ID,            ""  ) \
   SSO_TASK(Hama_Dbg_Trace_WN,      HAMA_DBG_TRACE_ID,     ""  ) \
   SSO_TASK(SSO_Power_Mode_WN,      SNACK_PMODE_ID,        ""  ) \
   SSO_TASK(Daylight_Monitor_WN,    DAYLIGHT_MONITOR_ID,   ""  ) \
   SSO_TASK(Temperature_Monitor_WN, TEMP_MONITOR_ID,       ""  ) \
   /*
   */

/*=====================================================================================* 
 * Exported Define Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Type Declarations
 *=====================================================================================*/

/*=====================================================================================* 
 * snack_style_organics_task_def.h
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/

#endif /*SNACK_STYLE_ORGANICS_TASK_DEF_H_*/
