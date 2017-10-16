/*=====================================================================================*/
/**
 * sso_dehyd_ctl_wrkr.cpp
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
#include "snacky_dehyd_ctl.h"

#include "pid_ctl_set.h"
#include "clk.h"
#include "chimney_ctl.h"
#include "daylight_monitor.h"
#include "pid_ctl.h"
#include "temp_monitor.h"
#include "dbg_log.h"

#define OBJECT_IMPLEMENTATION
#include "sso_dehyd_ctl_wrkr.h"
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
 * Local Function Prototypes
 *=====================================================================================*/
static void sso_dehyd_ctl_init(void);
static void sso_dehyd_ctl_wrkr_delete(struct Object * const obj);
static void sso_dehyd_ctl_wrkr_on_start(union Dispatcher * const this);
static void sso_dehyd_ctl_wrkr_on_loop(union Dispatcher * const this);
static void sso_dehyd_ctl_wrkr_on_stop(union Dispatcher * const this);
static void sso_dehyd_ctl_wrkr_on_mail(union Dispatcher * const this, union Mail * const mail);

/*=====================================================================================* 
 * Local Object Definitions
 *=====================================================================================*/
static union Dispatcher SSO_Dehyd_Ctl_Wrkr = {NULL};

static union PID_Ctl Fan_Door_Ctl;
static union PID_Ctl Heater_Ctl;
static union SSO_Power_Mode PM;
static union Chimney Chimney_Ctl;
/*=====================================================================================* 
 * Exported Object Definitions
 *=====================================================================================*/
union Dispatcher_Class SSO_Dehyd_Ctl_Wrkr_Class =
{
   {{&Dispatcher_Class, sso_dehyd_ctl_wrkr_delete}},
   sso_dehyd_ctl_wrkr_on_start,
   sso_dehyd_ctl_wrkr_on_loop,
   sso_dehyd_ctl_wrkr_on_stop,
   sso_dehyd_ctl_wrkr_on_mail
};

/*=====================================================================================* 
 * Local Inline-Function Like Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Definitions
 *=====================================================================================*/
void sso_dehyd_ctl_init(void)
{
   Populate_PID_Ctl(&Fan_Door_Ctl, PID_CTL_CHANNEL_FAN_DOOR, temp_sensor_cbk);
   Populate_PID_Ctl(&Heater_Ctl, PID_CTL_CHANNEL_HEATER, temp_sensor_cbk);
   Populate_Chimney(&Chimney_Ctl);
   Populate_SSO_Power_Mode_Proxy(&PM);
}
void sso_dehyd_ctl_wrkr_delete(struct Object * const obj)
{
   _delete(&Fan_Door_Ctl);
   _delete(&Heater_Ctl);
}

void sso_dehyd_ctl_wrkr_on_start(union Dispatcher * const this)
{
   TR_INFO("%s",__func__);
   Fan_Door_Ctl.vtbl->set_point(&Fan_Door_Ctl, SNACK_DEHYD_CTL_MAX_TEMP);
   Heater_Ctl.vtbl->set_point(&Heater_Ctl, SNACK_DEHYD_CTL_MIN_TEMP);
   PM.vtbl->power_req(&PM, Power_Mode_ON);
}

void sso_dehyd_ctl_wrkr_on_loop(union Dispatcher * const this)
{
   if(SNACK_DEHYD_CTL_MIN_TEMP < temp_mon::Get_Temperature())
   {
      Fan_Door_Ctl.vtbl->stop(&Fan_Door_Ctl);
      Heater_Ctl.vtbl->run(&Heater_Ctl);
      Chimney_Ctl.vtbl->set_state(CHIMNEY_CLOSED);
   }
   else if(SNACK_DEHYD_CTL_MAX_TEMP < temp_mon::Get_Temperature())
   {
      Fan_Door_Ctl.vtbl->run(&Fan_Door_Ctl);
      Heater_Ctl.vtbl->stop(&Heater_Ctl);
      Chimney_Ctl.vtbl->set_state(CHIMNEY_CLOSED);
   }
   else
   {
      Fan_Door_Ctl.vtbl->run(&Fan_Door_Ctl);
      Heater_Ctl.vtbl->run(&Heater_Ctl);
   }
}

void sso_dehyd_ctl_wrkr_on_stop(union Dispatcher * const this)
{
   PM.vtbl->power_rel(&PM, Power_Mode_ON);
   Fan_Door_Ctl.vtbl->stop(&Fan_Door_Ctl);
   Heater_Ctl.vtbl->stop(&Heater_Ctl);
}

void sso_dehyd_ctl_wrkr_on_mail(union Dispatcher * const this, union Mail * const mail)
{
   /** handle events **/
   _using(Dispatcher, &SSO_Dehyd_Ctl, on_mail, mail);
}

/*=====================================================================================* 
 * Exported Function Definitions
 *=====================================================================================*/
void Alloc_SSO_Dehyd_Ctl_Wrkr(union Dispatcher ** const this)
{
   if(NULL == SSO_Dehyd_Ctl_Wrkr.vtbl)
   {
      sso_dehyd_ctl_wrkr_init();
      Populate_Dispatcher(&SSO_Dehyd_Ctl_Wrkr.Dispatcher, SSO_DEHYD_CTL_TID, 64);
      Object_Update_Info(&SSO_Dehyd_Ctl_Wrkr.Object, &SSO_Dehyd_Ctl_Wrkr_Class.Class,
         sizeof(SSO_Dehyd_Ctl_Wrkr_Class));
   }
   *this = &SSO_Dehyd_Ctl_Wrkr;
}
/*=====================================================================================* 
 * sso_dehyd_ctl_wrkr.cpp
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/


