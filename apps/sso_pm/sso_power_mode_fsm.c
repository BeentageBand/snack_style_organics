#include "sso_power_mode_fsm.h"

#define CQueue_Params(SSO_PM_Handle_Req)
#include "cqueue.c"
#undef CQueue_Params

static void sso_pm_fsm_delete(struct Object * const obj);
static void SSO_PM_Subscribe_12VDC_Handle(union State_Machine * const fsm);
static void SSO_PM_Unsubscribe_12VDC_Handle(union State_Machine * const fsm);
static void SSO_PM_Init_12VDC_Source(union State_Machine * const fsm);
static void SSO_PM_Subscribe_120AC_Handle(union State_Machine * const fsm);
static void SSO_PM_Unsubscribe__120AC_Handle(union State_Machine * const fsm);
static void SSO_PM_Shut_All(union State_Machine * const fsm);

FSM_Declare_Chart(SSO_PM_FSM, SSO_PM_St_Chart)
static union St_Machine_State SSO_PM_States[SSO_PM_MAX_STID] = {NULL};
static union SSO_PM_FSM SSO_PM_FSM = {NULL};
union SSO_PM_FSM_Class SSO_PM_FSM_Class = 
{
    {sso_pm_fsm_delete, &FSM_Class}
};


void SSO_PM_Subscribe_12VDC_Handle(union State_Machine * const fsm)
{
    union SSO_PM_FSM * const this = _cast(SSO_PM_FSM, fsm);
    Isnt_Nullptr(this,);
    SSO_PM_Handle_T * const source = this->sources[SSO_PM_12VDC_SOURCE];
    if()
    if(SSO_PM_Source_Active)
        IPC_Self_Send(SSO_PM_INT_12VDC_INIT_MID, NULL, 0);
}

void SSO_PM_Unsubscribe_12VDC_Handle(union State_Machine * const fsm)
{
    union SSO_PM_FSM * const this = _cast(SSO_PM_FSM, fsm);
    Isnt_Nullptr(this,);
    SSO_PM_Handle_T * const source = this->sources[SSO_PM_12VDC_SOURCE];
    if (0 == source->size)
    {
        IPC_Self_Send(SSO_PM_INT_12VDC_SHUT_MID, NULL, 0);
    }
}

void SSO_PM_Init_12VDC_Source(union State_Machine * const fsm)
{

}

void SSO_PM_Subscribe_120AC_Handle(union State_Machine * const fsm)
{}

void SSO_PM_Unsubscribe__120AC_Handle(union State_Machine * const fsm)
{}

void SSO_PM_Shut_All(union State_Machine * const fsm)
{}
bool SSO_PM_IDLE_STID_guard(union State_Machine * const, union St_Machine_State * const)
{}
bool SSO_PM_12VDC_ON_STID_guard(union State_Machine * const, union St_Machine_State * const);
{}
bool SSO_PM_120AC_ON_STID_guard(union State_Machine * const, union St_Machine_State * const)
{}
bool SSO_PM_SHUT_STID_guard(union State_Machine * const, union St_Machine_State * const)
{}

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
        SSO_PM_Source_T i;
        for(i = 0; i < SSO_PM_MAX_SOURCE; ++i)
            TEMPLATE(Populate, CQueue, IPC_TID)(SSO_PM_FSM.sources + i,
                    SSO_PM_Source_Buff[i],
                    Num_Elems(SSO_PM_Source_Buff[i]));
    }
}