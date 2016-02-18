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
#include "temp_monitor.h"
#include "daylight_monitor.h"
#include "data_logger.h"
#include "heater_ctl.h"
#include "hamatora_sched_types.h"
#include "snack_org_lcd.h"
#include "snacky_dehyd_ctl.h"
/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported X-Macros
 *=====================================================================================*/
#define HAMA_SCHED_APPS_TABLE \
               /* App id,                Init app,          Run app,            Stop app */\
   HAMA_SCHED_APP(SNACK_ORG_CTL_ID,      snack_dehyd::Init, snack_dehyd::Main,  snack_dehyd::Shut   ) \
   HAMA_SCHED_APP(DATA_LOGGER_ID,        logger::Init,      logger::Main,       logger::Shut        ) \
   HAMA_SCHED_APP(SNACK_ORG_LCD_ID,      snack_lcd::Init,   snack_lcd::Main,    snack_lcd::Shut     ) \
   HAMA_SCHED_APP(DAYLIGHT_MONITOR_ID,   day_mon::Init,     NULL,               day_mon::Shut       ) \
   HAMA_SCHED_APP(TEMP_MONITOR_ID,       temp_mon::Init,    NULL,               temp_mon::Shut      ) \
   HAMA_SCHED_APP(HEATER_CTL_ID,         heater::Init,      NULL,               heater::Shut        ) \
   HAMA_SCHED_APP(AXIAL_FAN_CTL_ID,      fan::Init,         NULL,               fan::Shut           ) \
   HAMA_SCHED_APP(HAMA_SCHED_ID,         NULL,              NULL,               hama::Shut          ) \
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
