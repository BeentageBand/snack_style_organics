/*=====================================================================================*/
/**
 * api_uset.h
 * author : puch
 * date : Oct 22 2015
 *
 * description : Any comments
 *
 */
/*=====================================================================================*/
#ifndef HAMATORA_SCHED_DEF_H_
#define HAMATORA_SCHED_DEF_H_
/*=====================================================================================*
 * Project Includes
 *=====================================================================================*/
#include "axial_fan_ctl.h"
#include "daylight_monitor.h"
#include "hamatora_sched_types.h"
#include "heater_ctl.h"
#include "pid_ctl.h"
#include "snacky_dehyd_ctl.h"
#include "snack_org_lcd.h"
#include "snack_power_mode.h"
#include "temp_monitor.h"
/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported X-Macros
 *=====================================================================================*/
#define HAMA_SCHED_APPS_TABLE \
               /* App id,                Init app,          Run app,            Stop app */\
   HAMA_SCHED_APP(HAMA_DBG_TRACE_ID,     dbg::Init,         0,                  dbg::Shut           ) \
   HAMA_SCHED_APP(SNACK_ORG_CTL_ID,      snack_dehyd::Init, snack_dehyd::Main,  snack_dehyd::Shut   ) \
   HAMA_SCHED_APP(SNACK_ORG_LCD_ID,      snack_lcd::Init,   snack_lcd::Main,    snack_lcd::Shut     ) \
   HAMA_SCHED_APP(SNACK_PMODE_ID,        pmode::Init,       pmode::Main,        pmode::Shut         ) \
   HAMA_SCHED_APP(HAMA_SCHED_ID,         0,                 0,                  hama::Shut          ) \
   HAMA_SCHED_APP(DAYLIGHT_MONITOR_ID,   day_mon::Init,     day_mon::Main,      day_mon::Shut       ) \
   HAMA_SCHED_APP(TEMP_MONITOR_ID,       temp_mon::Init,    temp_mon::Main,     temp_mon::Shut      ) \
   HAMA_SCHED_APP(HEATER_CTL_ID,         heater::Init,      0,                  heater::Shut        ) \
   HAMA_SCHED_APP(AXIAL_FAN_CTL_ID,      fan::Init,         0,                  fan::Shut           ) \
   HAMA_SCHED_APP(PID_CTL_ID,            pid::Init,         pid::Main,          0                   ) \
   /*
   */

/*=====================================================================================* 
 * Exported Define Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Type Declarations
 *=====================================================================================*/

/*=====================================================================================* 
 * api_uset.h
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/

#endif /*HAMATORA_SCHED_DEF_H_*/
