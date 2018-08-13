/*=====================================================================================*/
/**
 * sso_dehyd_worker.c
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
#define COBJECT_IMPLEMENTATION
#define Dbg_FID SSO_DEHYD_WORKER_TID, 0
#include "dbg_log.h"
#include "ipc.h"
#include "sso_dehydrator_worker.h"
#include "sso_dehydrator_fsm.h"

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
static void sso_dehyd_worker_delete(struct Object * const obj);
static void sso_dehyd_worker_on_start(union Worker * const worker);
static void sso_dehyd_worker_on_loop(union Worker * const worker);
static void sso_dehyd_worker_on_stop(union Worker * const worker);
static void sso_dehyd_worker_on_mail(union Worker * const worker, union Mail * const mail);

/*=====================================================================================* 
 * Local Object Definitions
 *=====================================================================================*/
static union SSO_Dehyd_Worker = {NULL};
static union Mail SSO_Dehyd_Mailbox_Buff[64] = {{0}};
static union PID_Ctl SSO_Dehyd_Cooler = {NULL};
static union PID_Ctl SSO_Dehyd_Heater = {NULL};
static union SSO_Dehyd_FSM SSO_Dehyd_FSM = {NULL};

/*=====================================================================================* 
 * Exported Object Definitions
 *=====================================================================================*/
union SSO_Dehyd_Worker_Class SSO_Dehyd_Worker_Class =
{
   {{sso_dehyd_worker_delete, &Worker_Class}},
   sso_dehyd_worker_on_mail,
   sso_dehyd_worker_on_start,
   sso_dehyd_worker_on_loop,
   sso_dehyd_worker_on_stop
};

/*=====================================================================================* 
 * Local Inline-Function Like Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Definitions
 *=====================================================================================*/
void sso_dehyd_worker_delete(struct Object * const obj)
{
    _delete(&SSO_Dehyd_Cooler);
    _delete(&SSO_Dehyd_Heater);
    _delete(&SSO_Dehyd_FSM);
}

void sso_dehyd_worker_on_start(union Worker * const super)
{
   union SSO_Dehyd_Worker * const this = _cast(SSO_Dehyd_Worker, super);
   Isnt_Nullptr(this, );
   if(IPC_Subscribe_Mailist(SSO_Dehyd_Mailist, Num_Elems(SSO_Dehyd_Mailist)))
   {
         this->st_m->vtbl->dispatch(this->st_m, NULL);
   }
}

void sso_dehyd_worker_on_loop(union Worker * const super)
{
}

void sso_dehyd_worker_on_stop(union Worker * const this)
{
   if(IPC_Unsubscribe_Mailist(SSO_Dehyd_Mailist, Num_Elems(SSO_Dehyd_Mailist)))
   {

   }
}

void sso_dehyd_worker_on_mail(union Worker * const super, union Mail * const mail)
{
   union SSO_Dehyd_Worker * const this = _cast(SSO_Dehyd_Worker, super);
   Isnt_Nullptr(this, );

   /** handle events **/
   SSO_Dehyd_IPC_MID_Process_T * process = SSO_Dehyd_Dispatcher.vtbl->find(&SSO_Dehyd_Dispatcher, mail->mid);
   if(process != SSO_Dehyd_Dispatcher.CHash_Set_Pair_IPC_MID_SSO_Dehyd_Process.vtbl->end(&SSO_Dehyd_Dispatcher))
   {
      process->obj(this, mail);
   }

   this->st_m->vtbl->dispatch(this->st_m, mail);
}

/*=====================================================================================* 
 * Exported Function Definitions
 *=====================================================================================*/
void Populate_SSO_Dehyd_Worker(union SSO_Dehyd_Worker * const this)
{
   if(NULL == SSO_Dehyd_Worker.vtbl)
   {
      Populate_Worker(&SSO_Dehyd_Worker.Worker, 
         SSO_DEHYD_WORKER_TID,
         SSO_Dehyd_Mailbox_Buff, 
         Num_Elems(SSO_Dehyd_Mailbox_Buff));
      Object_Init(&SSO_Dehyd_Ctl_Worker.Object,
         &SSO_Dehyd_Ctl_Worker_Class.Class,
         sizeof(SSO_Dehyd_Worker_Class.Thread));
      SSO_Dehyd_Worker.vtbl = &SSO_Dehyd_Worker_Class;

      Populate_PID_Ctl(&SSO_Dehyd_Cooler);
      Populate_PID_Ctl(&SSO_Dehyd_Heater);
      Populate_SSO_Dehyd_FSM(&SSO_Dehyd_FSM);

      SSO_Dehyd_Worker.st_m = &SSO_Dehyd_FSM.State_Machine;
      SSO_Dehyd_FSM.cooler_ctl = &SSO_Dehyd_Cooler;
      SSO_Dehyd_FSM.heater_ctl = &SSO_Dehyd_Heater;
   }
   _clone(this, SSO_Dehyd_Worker);
}
/*=====================================================================================* 
 * sso_dehyd_worker.c
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/


