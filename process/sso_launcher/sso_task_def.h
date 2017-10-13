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
   SSO_TASK(Arduino_WN,             ARDUINO_TID,            ""  ) \
   SSO_TASK(Test_WN,                TEST_TID,               ""  ) \
   SSO_TASK(SSO_Ctl_WN,             SNACK_ORG_CTL_TID,      ""  ) \
   SSO_TASK(SSO_LCD_WN,             SNACK_ORG_LCD_TID,      ""  ) \
   SSO_TASK(Heater_Ctl_WN,          HEATER_CTL_TID,         ""  ) \
   SSO_TASK(Fan_Ctl_WN,             AXIAL_FAN_CTL_TID,      ""  ) \
   SSO_TASK(PID_Ctl_WN,             PID_CTL_TID,            ""  ) \
   SSO_TASK(Hama_Dbg_Trace_WN,      HAMA_DBG_TRACE_TID,     ""  ) \
   SSO_TASK(SSO_Power_Mode_WN,      SNACK_PMODE_TID,        ""  ) \
   SSO_TASK(Daylight_Monitor_WN,    DAYLIGHT_MONITOR_TID,   ""  ) \
   SSO_TASK(Temperature_Monitor_WN, TEMP_MONITOR_TID,       ""  ) \
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
