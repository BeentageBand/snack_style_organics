/*
 * snack_style_organics_launcher.cpp
 *
 * Created: 07/01/2016 12:51:27 a.m.
 * Author : ASUS
 */ 
#include "sso_app_task_def.h"
#include "snack_org_friends.h"
#include "application.h"
#include "sso_lcd.h"
#include "sso_dehyd_ctl.h"
#include "sso_monitor.h"

#define SSO_APP_TASK_SWITCH(name, id, desc) \
case id: \
   static union name name = {{NULL}}; \
   if (NULL == name.vtbl) \
   { \
    Method_Name(Populate, name)(&name, id); \
    worker = &name; \
   } \
   break; 

static union Worker * SSO_App_Factory_Method(IPC_TID_T const tid);

union Worker * SSO_App_Factory_Method(IPC_TID_T const tid)
{
   union Worker * worker = NULL;
   switch(tid)
   {
      SSO_APP_TASK_DEF(SSO_APP_TASK_SWITCH)
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
   union Application sso_application;
   Populate_Application(&sso_application, SSO_App_Factory_Method);
   rc = sso_application->vtbl->startup(&sso_application);
   if(0 == rc)
   {
      _delete(&sso_application);
   }
   return rc;
}
