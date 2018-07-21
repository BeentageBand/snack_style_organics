/*=====================================================================================*/
/**
 * snack_power_mode_wn.c
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
#include "snack_power_mode_wn.h"
#include "pwm.h"
#include "snack_power_mode_ext.h"
/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/

/*=====================================================================================* 
 * Local X-Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Define Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Type Definitions
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Prototypes
 *=====================================================================================*/
static void sso_pm_worker_delete(struct Object * const obj);
static void sso_pm_worker_on_mail(union Worker * const worker, union Mail * const mail);
static void sso_pm_worker_on_start(union Worker * const worker);
static void sso_pm_worker_on_loop(union Worker * const worker);
static void sso_pm_worker_on_stop(union Worker * const worker);

/*=====================================================================================* 
 * Local Object Definitions
 *=====================================================================================*/
#undef PMODE_STATE
#define PMODE_STATE(st) \
const Change_Of_State_T st##_State PROGMEM = \
{\
   pmode::Enter_##st, \
   pmode::Exit_##st   \
};\

POWER_MODE_STATES_TB

#undef PMODE_STATE
#define PMODE_STATE(st) \
&st##_State,\

const Change_Of_State_T * const PMode_SM[] PROGMEM =
{
   POWER_MODE_STATES_TB
};

static PMode_State_T Current_State = 0;
static PMode_State_T New_State = 0;
static union SSO_PM_Worker SSO_PM_Worker = {{NULL}};
static union Mail SSO_PM_Mail_Buff[64] = {{NULL}};
/*=====================================================================================* 
 * Exported Object Definitions
 *=====================================================================================*/
SSO_PM_Worker_Class_T SSO_PM_Worker_Class = 
{{
    {sso_pm_worker_delete, NULL},
}};
/*=====================================================================================* 
 * Local Inline-Function Like Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Definitions
 *=====================================================================================*/
void sso_pm_worker_delete(struct Object * const obj)
{
}

void sso_pm_worker_on_mail(union Worker * const worker, union Mail * const mail)
{


}

#undef PMODE_SOURCE
#define PMODE_SOURCE(src, osc) \
   src##_init();
void sso_pm_worker_on_start(union Worker * const worker)
{
   POWER_MODE_SOURCES_TB
}

void sso_pm_worker_on_loop(union Worker * const worker)
{
}

void sso_pm_worker_on_stop(union Worker * const worker)
{
   pmode::Set_State(PMODE_ALL_OFF_STATE);
}
/*=====================================================================================* 
 * Exported Function Definitions
 *=====================================================================================*/
void Populate_SSO_PM_Worker(union SSO_PM_Worker * const this)
{
    if(NULL == SSO_PM_Worker.vtbl)
    {
        Populate_Worker(&SSO_PM_Worker.Worker,
                        SSO_PM_WORKER_TID, 
                        SSO_PM_Mail_Buff,
                        Num_Elems(SSO_PM_Mail_Buff));

        Object_Init(&this.Object,
            &SSO_PM_Worker_Class.Class,
			sizeof(this), sizeof(SSO_PM_Worker_Class.Worker));
        SSO_PM_Worker.vtbl = &SSO_PM_Worker_Class;

        SSO_PM_Worker_Class.on_mail = sso_pm_worker_on_mail;
        SSO_PM_Worker_Class.on_start = sso_pm_worker_on_start;
        SSO_PM_Worker_Class.on_loop = sso_pm_worker_on_loop;
        SSO_PM_Worker_Class.on_stop = sso_pm_worker_on_stop;
    }
    memcpy(this, &SSO_PM_Worker, sizeof(SSO_PM_Worker));
}

/*=====================================================================================* 
 * snack_power_mode.c
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
