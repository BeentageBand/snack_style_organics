#define COBJECT_IMPLEMENTATION
#include "sso_power_mode_ext.h"
#include "sso_power_mode_fsm.h"
#include "sso_power_mode_process.h"
#include "ipc.h"

#define CQueue_Params SSO_PM_Handle_Req
#include "cqueue.c"
#undef CQueue_Params

static void sso_pm_fsm_delete(struct Object * const obj);
static bool sso_pm_pop_power_request(SSO_PM_Handle_Req_T * const pm_req);
static void sso_pm_init_source(SSO_PM_Source_T const pm_src);
static void sso_pm_shut_source(SSO_PM_Source_T const pm_src);

/* Guards */
static bool SSO_PM_12VDC_Guard(union State_Machine * const fsm, union St_Machine_State * const st);
static bool SSO_PM_120AC_Guard(union State_Machine * const fsm, union St_Machine_State * const st);
static bool SSO_PM_Power_Request_Guard(union State_Machine * const fsm, union St_Machine_State * const st);
static bool SSO_PM_Shut_Guard(union State_Machine * const fsm, union St_Machine_State * const st);
/* Actions */
static void SSO_PM_Subscribe_Handle(union State_Machine * const fsm);
static void SSO_PM_Unsubscribe_Handle(union State_Machine * const fsm);
static void SSO_PM_Init_12VDC_Source(union State_Machine * const fsm);
static void SSO_PM_Shut_12VDC_Source(union State_Machine * const fsm);
static void SSO_PM_Init_120AC_Source(union State_Machine * const fsm);
static void SSO_PM_Shut_120AC_Source(union State_Machine * const fsm);
static void SSO_PM_Shut_All(union State_Machine * const fsm);

static union St_Machine_State SSO_PM_States[SSO_PM_MAX_STID] = {NULL};
static union SSO_PM_FSM SSO_PM_FSM = {NULL};
static SSO_PM_Handle_Req_T SSO_PM_Power_Request_Buff [SSO_PM_POWER_REQUEST_BUFF_SZ] = {0};
union SSO_PM_FSM_Class SSO_PM_FSM_Class = 
{
    {sso_pm_fsm_delete, &FSM_Class}
};
FSM_Declare_Chart(SSO_PM_FSM_DEF, SSO_PM_St_Chart)

void sso_pm_init_source(SSO_PM_Source_T const pm_src)
{
   switch(pm_src)
   {
      case SSO_PM_120AC_SOURCE:
         IPC_Self_Send(SSO_PM_INT_120AC_INIT_MID, NULL, 0);
         break;
      case SSO_PM_12VDC_SOURCE:
         IPC_Self_Send(SSO_PM_INT_12VDC_INIT_MID, NULL, 0);
         break;
      default: break;
   }
}

void sso_pm_shut_source(SSO_PM_Source_T const pm_src)
{
   switch(pm_src)
   {
      case SSO_PM_120AC_SOURCE:
         IPC_Self_Send(SSO_PM_INT_120AC_SHUT_MID, NULL, 0);
         break;
      case SSO_PM_12VDC_SOURCE:
         IPC_Self_Send(SSO_PM_INT_12VDC_SHUT_MID, NULL, 0);
         break;
      default: break;
   }
}

void SSO_PM_Subscribe_Handle(union State_Machine * const fsm)
{
   SSO_PM_Handle_Req_T   pm_req = SSO_PM_Handle_Req_Queue.vtbl->back(&SSO_PM_Handle_Req_Queue);;
   SSO_PM_Handle_Req_Queue.vtbl->pop_back(&SSO_PM_Handle_Req_Queue);
   if(0 == pm_req.handle_id)
   {
      SSO_PM_Source_Cbk[pm_req.source].vtbl->subscribe(&SSO_PM_Source_Cbk);
      pm_req.handle_id = SSO_PM_Source_Cbk[pm_req.source].handles;
   }
   IPC_Send(pm_req.tid,
         SSO_PM_INT_POWER_REQUEST_RES_MID,
         &pm_req,
         sizeof(pm_req));

   sso_pm_init_source(&pm_req);
}

void SSO_PM_Unsubscribe_Handle(union State_Machine * const fsm)
{
   SSO_PM_Handle_Req_T pm_req = SSO_PM_Handle_Req_Queue.vtbl->back(&SSO_PM_Handle_Req_Queue);
   SSO_PM_Handle_Req_Queue.vtbl->pop_back(&SSO_PM_Handle_Req_Queue);
   if(pm_req.handle_id && 
     pm_req.handle_id <= SSO_PM_Source_Cbk[pm_req.source].handles)  
   {
      SSO_PM_Source_Cbk[pm_req.source].vtbl->unsubscribe(&SSO_PM_Source_Cbk);
      pm_req.handle_id = SSO_PM_Source_Cbk[pm_req.source].handles;
   }
   IPC_Send(pm_req.tid,
         SSO_PM_INT_POWER_REQUEST_RES_MID,
         &pm_req,
         sizeof(pm_req));
   sso_pm_shut_source(&pm_req);
}

void SSO_PM_Init_12VDC_Source(union State_Machine * const fsm)
{
   if(SSO_PM_Source_Cbk[SSO_PM_12VDC_SOURCE].handles)
   {
      if(!SSO_PM_Source_Cbk[SSO_PM_12VDC_SOURCE].is_active)
      {
         SSO_PM_Source_Cbk[SSO_PM_12VDC_SOURCE].vtbl->init_source(&SSO_PM_Source_Cbk);
      }
   }
}

void SSO_PM_Init_120AC_Source(union State_Machine * const fsm)
{
   if(0 == SSO_PM_Source_Cbk[SSO_PM_12VDC_SOURCE].handles ||
      !SSO_PM_Source_Cbk[SSO_PM_120AC_SOURCE].is_active)
   {
      SSO_PM_Source_Cbk[SSO_PM_120AC_SOURCE].vtbl->acquire_source(
            SSO_PM_Source_Cbk + SSO_PM_120AC_SOURCE);
   }

   if(SSO_PM_Source_Cbk[SSO_PM_120AC_SOURCE].handles)
   {
      if(!SSO_PM_Source_Cbk[SSO_PM_120AC_SOURCE].is_active)
      {
         SSO_PM_Source_Cbk[SSO_PM_120AC_SOURCE].vtbl->init_source(&SSO_PM_Source_Cbk);
      }
   }
}

void SSO_PM_Shut_12VDC_Source(union State_Machine * const fsm)
{
   SSO_PM_Source_Cbk[SSO_PM_12VDC_SOURCE].vtbl->shut_source(&SSO_PM_Source_Cbk);
}

void SSO_PM_Shut_120AC_Source(union State_Machine * const fsm)
{
   if(0 == SSO_PM_Source_Cbk[SSO_PM_120AC_SOURCE].handles)
   {
      if(SSO_PM_Source_Cbk[SSO_PM_120AC_SOURCE].is_active)
      {
         SSO_PM_Source_Cbk[SSO_PM_120AC_SOURCE].vtbl->shut_source(&SSO_PM_Source_Cbk);
      }
      SSO_PM_Source_Cbk[SSO_PM_120AC_SOURCE].vtbl->release_source(
            SSO_PM_Source_Cbk + SSO_PM_120AC_SOURCE);
   }
}

void SSO_PM_Shut_All(union State_Machine * const fsm)
{
   IPC_Publish(SSO_PM_PBC_FORCE_RELEASE_REQ_MID, NULL, 0);
}

bool SSO_PM_Power_Request_Guard(union State_Machine * const fsm, union St_Machine_State * const state)
{
   SSO_PM_Handle_Req_T pm_req = {0};
   if(SSO_PM_Handle_Req_Queue.vtbl->size(&SSO_PM_Handle_Req_Queue))
   {
      pm_req = SSO_PM_Handle_Req_Queue.vtbl->back(&SSO_PM_Handle_Req_Queue);
   }
   else
   {
      Dbg_Warn("%s: Power Request Queue is empty", __func__);
      SSO_PM_Handle_Req_Queue.vtbl->pop_back(&SSO_PM_Handle_Req_Queue);
      return false;
   }

   if(pm_req.source >= SSO_PM_MAX_SOURCE && 0 == pm_req.handle_id)
   {
      Dbg_Warn("%s:Invalid Power Request handle id=%d; source=%d request=%s",
            __func__,
            pm_req.handle_id,
            pm_req.source,
            (pm_req.req_type)? "ACQUIRE" : "RELEASE");
      IPC_Send(pm_req.tid, 
            SSO_PM_INT_POWER_REQUEST_RES_MID,
            &pm_req,
            sizeof(pm_req));
      SSO_PM_Handle_Req_Queue.vtbl->pop_back(&SSO_PM_Handle_Req_Queue);
      return false;
   }
   return true;
}

bool SSO_PM_12VDC_Guard(union State_Machine * const fsm, union St_Machine_State * const state)
{
   bool do_transition = false;
   switch(state->stid)
   {
      case SSO_PM_IDLE_STID: //shutdown 12vdc
         do_transition = 0 == SSO_PM_Source_Cbk[SSO_PM_12VDC_SOURCE].handles &&
                     SSO_PM_Source_Cbk[SSO_PM_12VDC_SOURCE].is_active;
         break;
      case SSO_PM_12VDC_STID: //init 12vdc
         do_transition = SSO_PM_Source_Cbk[SSO_PM_12VDC_SOURCE].handles &&
                     !SSO_PM_Source_Cbk[SSO_PM_12VDC_SOURCE].is_active;
         break;
      default: break;
   }
   return do_transition;
}
bool SSO_PM_120AC_Guard(union State_Machine * const fsm, union St_Machine_State * const state)
{
   bool do_transition = false;
   switch(state->stid)
   {
      case SSO_PM_12VDC_STID: //shutdown 120ac
         do_transition = 0 == SSO_PM_Source_Cbk[SSO_PM_120AC_SOURCE].handles &&
                     SSO_PM_Source_Cbk[SSO_PM_120AC_SOURCE].is_active;
         break;
      case SSO_PM_120AC_STID: //init 120ac
         do_transition = SSO_PM_Source_Cbk[SSO_PM_120AC_SOURCE].handles &&
                     !SSO_PM_Source_Cbk[SSO_PM_120AC_SOURCE].is_active;
         break;
      default: break;
   }
   return do_transition;
}
bool SSO_PM_SHUT_STID_Guard(union State_Machine * const fsm, union St_Machine_State * const state)
{
   return true;
}

void Populate_SSO_PM_FSM(union SSO_PM_FSM * const this)
{
    if(NULL == SSO_PM_FSM.vtbl)
    {
        Populate_FSM(&SSO_PM_FSM,
                    SSO_PM_St_Chart,
                    Num_Elems(SSO_PM_St_Chart),
                    SSO_PM_States,
                    Num_Elems(SSO_PM_States));
        Object_Init(&SSO_PM_FSM.Object,
                    &SSO_PM_FSM_Class.Class,
                    sizeof(SSO_PM_FSM_Class.FSM));
      TEMPLATE(Populate, CQueue, SSO_PM_Handle_Req)(&SSO_PM_Handle_Req_Queue,
            SSO_PM_Power_Request_Buff,
            Num_Elems(SSO_PM_Power_Request_Buff));
    }
}
