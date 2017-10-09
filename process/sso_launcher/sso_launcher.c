/*
 * snack_style_organics_launcher.cpp
 *
 * Created: 07/01/2016 12:51:27 a.m.
 * Author : ASUS
 */ 

/*================================================================================================*
 * Project Includes
 *================================================================================================*/
#include "sso_app_task_def.h"
#include "application.h"
#include "sso_lcd.h"
#include "sso_dehyd_ctl.h"
#include "sso_monitor.h"
/*================================================================================================*
 * Standard Includes
 *================================================================================================*/

/*================================================================================================*
 * Local Prototypes
 *================================================================================================*/
static union Task * SSO_App_Task_Def(uint8_t const tid);
/*================================================================================================*
 * Local Object Definitions
 *================================================================================================*/

/*================================================================================================*
 * Local Main Definition
 *================================================================================================*/
union Task * SSO_App_Task_Def(uint8_t const tid)
{
   union Task * task = NULL;
   switch(tid)
   {
      SSO_APP_TASK_DEF(SSO_APP_TASK_SWITCH)
      default: break;
   }
   return task;
}

/*================================================================================================*
 * Local Main Definition
 *================================================================================================*/

int main(void)
{
   union Application sso_application = Application(0);
   sso_application->vtbl->append_table(&sso_application, SSO_App_Task_Def);

   sso_application->vtbl->startup(&sso_application);
   int rc = sso_application->vtbl->run(&sso_application, 10000);
   if(0 == rc)
   {
      _delete(&sso_application);
   }
   return rc;
}
