/*
 * snack_style_organics_launcher.cpp
 *
 * Created: 07/01/2016 12:51:27 a.m.
 * Author : ASUS
 */ 
#include "sso_task_def.h"
#include "application.h"
#include "sso_friends.h"
#ifdef ENABLE_SSO
#include "sso_lcd.h"
#include "sso_monitor.h"
#endif

#define SSO_APP_TASK_SWITCH(name, id, desc) \
case id: \
   static union name name = {NULL}; \
   if (NULL == name.vtbl) \
   { \
    Method_Name(Populate, name)(&name, id); \
    worker = &name; \
   } \
   break; \

static union Worker * SSO_App_Factory_Method(IPC_TID_T const tid);

union Worker * SSO_App_Factory_Method(IPC_TID_T const tid)
{
   static union SSO_PM_Worker sso_pm = {NULL};
   static union SSO_Dehyd_Worker sso_dehyd = {NULL};
   union Worker * worker = NULL;
   switch(tid)
   {
      //SSO_APP_TASK_DEF(SSO_APP_TASK_SWITCH)
      case SSO_PM_WORKER_TID:
      if(NULL == sso_pm.vtbl)
        Populate_SSO_PM_Worker(&sso_pm);
      worker = &sso_pm.Worker;
      break;

      case SSO_DEHYD_WORKER_TID:
      if(NULL == sso_dehyd.vtbl)
        Populate_SSO_Dehyd_Worker(&sso_dehyd);
      break;
      default: break;
   }
   return worker;
}

/*================================================================================================*
 * Local Main Definition
 *================================================================================================*/

int main(void)
{
   Snack_Style_Organics_Init();
   union Application sso_application = {NULL};
   Populate_Application(&sso_application, SSO_App_Factory_Method);
   App_Stat_T rc = sso_application.vtbl->startup(&sso_application);
   if(0 == rc)
   {
      _delete(&sso_application);
   }
   return rc;
}