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
#define COBJECT_IMPLEMENTATION
#define Dbg_FID SSO_PM_FID, 1
/*=====================================================================================*
 * Project Includes
 *=====================================================================================*/
#ifdef SSO_ENABLE
#include "pwm.h"
#endif /*SSO_ENABLE*/
#include "dbg_log.h"
#include "ipc.h"
#include "sso_power_mode_wn.h"
#include "sso_power_mode_fsm.h"
#include "sso_power_mode_process.h"
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
static union SSO_PM_Worker SSO_PM_Worker = {{NULL}};
static union Mail SSO_PM_Mail_Buff[64] = {{NULL}};
static SSO_PM_Handle_Req_T SSO_PM_Handle_Req_Buff[SSO_PM_POWER_REQUEST_BUFF_SZ];
static union SSO_PM_FSM SSO_PM_FSM = {NULL};
/*=====================================================================================* 
 * Exported Object Definitions
 *=====================================================================================*/
SSO_PM_Worker_Class_T SSO_PM_Worker_Class = 
{{
    {sso_pm_worker_delete, NULL},
}};

IPC_MID_T SSO_PM_Subscription_Mailist [] = 
{
   SSO_PM_SUBSCRIPTION_MAILIST(SSO_PM_PROCESS_POPULATE_SUBSCRIPTION)
};

/*=====================================================================================* 
 * Local Inline-Function Like Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Definitions
 *=====================================================================================*/
void sso_pm_worker_delete(struct Object * const obj)
{
    _delete(&SSO_PM_FSM);
}

void sso_pm_worker_on_mail(union Worker * const worker, union Mail * const mail)
{
    SSO_PM_Processed_MID_T * const process = SSO_PM_Dispatcher.vtbl->find(&SSO_PM_Dispatcher, mail->mid);
    if(process != SSO_PM_Dispatcher.CHash_Set_Pair_IPC_MID_SSO_PM_Process.vtbl->end(&SSO_PM_Dispatcher))
    {
        process->obj(&SSO_PM_Worker, mail);
        SSO_PM_FSM.State_Machine.vtbl->dispatch(&SSO_PM_FSM.State_Machine, mail);
    }
}

#undef PMODE_SOURCE
#define PMODE_SOURCE(src, osc) \
   src##_init();

void sso_pm_worker_on_start(union Worker * const worker)
{
    IPC_Subscribe_Mailist(SSO_PM_Subscription_Mailist, Num_Elems(SSO_PM_Subscription_Mailist));
    Dbg_Info("%s: start SSO PM FSM", __func__);
    SSO_PM_FSM.State_Machine.vtbl->dispatch(&SSO_PM_FSM.State_Machine, NULL);
}

void sso_pm_worker_on_loop(union Worker * const worker)
{

}

void sso_pm_worker_on_stop(union Worker * const worker)
{
   IPC_Unsubscribe_Mailist(SSO_PM_Subscription_Mailist, Num_Elems(SSO_PM_Subscription_Mailist));
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

        Object_Init(&SSO_PM_Worker.Object,
            &SSO_PM_Worker_Class.Class,
         sizeof(SSO_PM_Worker_Class.Worker));
        SSO_PM_Worker.vtbl = &SSO_PM_Worker_Class;

        SSO_PM_Worker_Class.Worker.on_mail = sso_pm_worker_on_mail;
        SSO_PM_Worker_Class.Worker.on_start = sso_pm_worker_on_start;
        SSO_PM_Worker_Class.Worker.on_loop = sso_pm_worker_on_loop;
        SSO_PM_Worker_Class.Worker.on_stop = sso_pm_worker_on_stop;
        Populate_CQueue_SSO_PM_Handle_Req(&SSO_PM_Handle_Req_Queue,
                                    SSO_PM_Handle_Req_Buff, 
                                    Num_Elems(SSO_PM_Handle_Req_Buff));
        Populate_SSO_PM_FSM(&SSO_PM_FSM);
    }
    memcpy(this, &SSO_PM_Worker, sizeof(SSO_PM_Worker));
}

/*=====================================================================================* 
 * snack_power_mode.c
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
