#define COBJECT_IMPLEMENTATION
#include "ipc.h"
#include "sso_dehydrator_cbk.h"
#include "sso_dehydrator_fsm.h"
#include "sso_dehydrator_uset.h"

#define SSO_DEHYD_PID_TOUT (1000U)

static bool SSO_Dehyd_Ready_Guard(union State_Machine * const st_m, union St_Machine_State * const st);
static bool SSO_Dehyd_Dark_Stby_Guard(union State_Machine * const st_m, union St_Machine_State * const st);
static bool SSO_Dehyd_Sunlight_Stby_Guard(union State_Machine * const st_m, union St_Machine_State * const st);
static bool SSO_Dehyd_Dark_Start_Guard(union State_Machine * const st_m, union St_Machine_State * const st);
static bool SSO_Dehyd_Sunlight_Start_Guard(union State_Machine * const st_m, union St_Machine_State * const st);
static bool SSO_Dehyd_Dark2Sunlight_Op_Guard(union State_Machine * const st_m, union St_Machine_State * const st);
static bool SSO_Dehyd_Sunlight2Dark_Op_Guard(union State_Machine * const st_m, union St_Machine_State * const st);
static bool SSO_Dehyd_Sunlight_Start_Guard(union State_Machine * const st_m, union St_Machine_State * const st);
static bool SSO_Dehyd_Feedback_Guard(union State_Machine * const st_m, union St_Machine_State * const st);
static bool SSO_Dehyd_Stop_Guard(union State_Machine * const st_m, union St_Machine_State * const st);

static void SSO_Dehyd_Gets_Ready(union State_Machine * const st_m);
static void SSO_Dehyd_Dark_Start_Ctl(union State_Machine * const st_m);
static void SSO_Dehyd_Sunlight_Start_Ctl(union State_Machine * const st_m);
static void SSO_Dehyd_Switch_Op(union State_Machine * const st_m);
static void SSO_Dehyd_Feedback_Ctl(union State_Machine * const st_m);
static void SSO_Dehyd_Stop_Ctl(union State_Machine * const st_m);

static void sso_dehyd_fsm_delete(struct Object * const obj);

static union SSO_Dehyd_FSM SSO_Dehyd_FSM = {NULL};
static union SSO_Dehyd_Cbk SSO_Dehyd_Cbk = {NULL};
static union St_Machine_State SSO_Dehyd_FSM_States[SSO_DEHYD_MAX_STID] = {{0}};

union SSO_Dehyd_FSM_Class SSO_Dehyd_FSM_Class =
{{//FSM
        {{//State_Machine
                {sso_dehyd_fsm_delete, NULL},
                NULL,
                NULL,
                NULL
        }}

}};

FSM_Declare_Chart(SSO_DEHYD_FSM_DEF, SSO_Dehyd_St_Chart)

bool SSO_Dehyd_Ready_Guard(union State_Machine * const st_m, union St_Machine_State * const st)
{
    union SSO_Dehyd_FSM * const fsm = _cast(SSO_Dehyd_FSM, st_m);
    Isnt_Nullptr(fsm, false);
    bool is_ready = (fsm->temp_reading) && (fsm->sunlight_reading);

    return is_ready;
}

bool SSO_Dehyd_Dark_Stby_Guard(union State_Machine * const st_m, union St_Machine_State * const st)
{
    union SSO_Dehyd_FSM * const fsm = _cast(SSO_Dehyd_FSM, st_m);
    Isnt_Nullptr(fsm, false);

    return SSO_Dehyd_Cbk.vtbl->is_driver_ready(&SSO_Dehyd_Cbk, SSO_DEHYD_DRIVER_FAN) && 
    SSO_Dehyd_Cbk.vtbl->is_driver_ready(&SSO_Dehyd_Cbk, SSO_DEHYD_DRIVER_ELECTRIC_HEATER);
}
bool SSO_Dehyd_Sunlight_Stby_Guard(union State_Machine * const st_m, union St_Machine_State * const st)
{
    union SSO_Dehyd_FSM * const fsm = _cast(SSO_Dehyd_FSM, st_m);
    Isnt_Nullptr(fsm, false);

    return SSO_Dehyd_Cbk.vtbl->is_driver_ready(&SSO_Dehyd_Cbk, SSO_DEHYD_DRIVER_FAN) && 
    SSO_Dehyd_Cbk.vtbl->is_driver_ready(&SSO_Dehyd_Cbk, SSO_DEHYD_DRIVER_GATE);
}
bool SSO_Dehyd_Dark_Start_Guard(union State_Machine * const st_m, union St_Machine_State * const st)
{
    union SSO_Dehyd_FSM * const fsm = _cast(SSO_Dehyd_FSM, st_m);
    Isnt_Nullptr(fsm, false);
    return fsm->countdown;
}
bool SSO_Dehyd_Sunlight_Start_Guard(union State_Machine * const st_m, union St_Machine_State * const st)
{
    union SSO_Dehyd_FSM * const fsm = _cast(SSO_Dehyd_FSM, st_m);
    Isnt_Nullptr(fsm, false);
    return fsm->countdown;
}
bool SSO_Dehyd_Dark2Sunlight_Op_Guard(union State_Machine * const st_m, union St_Machine_State * const st)
{
    union SSO_Dehyd_FSM * const fsm = _cast(SSO_Dehyd_FSM, st_m);
    Isnt_Nullptr(fsm, false);
    int32_t sunlight_limit = SSO_DEHYDRATOR_MIN_SUNLIGHT - SSO_DEHYDRATOR_HYSTHERESIS; 
    return SSO_Dehyd_Sunlight_Start_Guard(st_m, st) && fsm->sunlight_reading > sunlight_limit;
}
bool SSO_Dehyd_Sunlight2Dark_Op_Guard(union State_Machine * const st_m, union St_Machine_State * const st)
{
    union SSO_Dehyd_FSM * const fsm = _cast(SSO_Dehyd_FSM, st_m);
    Isnt_Nullptr(fsm, false);
    int32_t sunlight_limit = SSO_DEHYDRATOR_MIN_SUNLIGHT + SSO_DEHYDRATOR_HYSTHERESIS; 

    return SSO_Dehyd_Dark_Start_Guard(st_m, st) && fsm->sunlight_reading < sunlight_limit;
}

bool SSO_Dehyd_Feedback_Guard(union State_Machine * const st_m, union St_Machine_State * const st)
{
    //TODO : feedback guard
    return true;
}

bool SSO_Dehyd_Stop_Guard(union State_Machine * const st_m, union St_Machine_State * const st)
{
    union SSO_Dehyd_FSM * const fsm = _cast(SSO_Dehyd_FSM, st_m);
    Isnt_Nullptr(fsm, false);
    return true;
}

void SSO_Dehyd_Gets_Ready(union State_Machine * const st_m)
{
    union SSO_Dehyd_FSM * const fsm = _cast(SSO_Dehyd_FSM, st_m);
    Isnt_Nullptr(fsm, );
    IPC_MID_T mid = (SSO_DEHYDRATOR_MIN_SUNLIGHT > fsm->sunlight_reading)? 
        SSO_DEHYD_INT_DARK_MODE_OP_MID : SSO_DEHYD_INT_SUNLIGHT_MODE_OP_MID;
    IPC_Send_Self(mid, NULL, 0);
}

void SSO_Dehyd_Dark_Start_Ctl(union State_Machine * const st_m)
{
    union SSO_Dehyd_FSM * const fsm = _cast(SSO_Dehyd_FSM, st_m);
    Isnt_Nullptr(fsm, );
    union PID_Ctl * pid = fsm->cooler_ctl;
    if (!pid->driver)
    {
        pid->vtbl->start(pid, SSO_Dehyd_Cbk.vtbl->get_driver(&SSO_Dehyd_Cbk, SSO_DEHYD_DRIVER_FAN));
    }

    pid = fsm->heater_ctl;

    if (!pid->driver)
    {
        pid->vtbl->start(pid, SSO_Dehyd_Cbk.vtbl->get_driver(&SSO_Dehyd_Cbk, SSO_DEHYD_DRIVER_ELECTRIC_HEATER));
    }

    if(fsm->heater_ctl->driver || fsm->cooler_ctl->driver)
    {
        union Timer * pid_timer = fsm->pid_timer;
        pid_timer->vtbl->set_time(pid_timer, SSO_DEHYD_PID_TOUT, true);
        pid_timer->vtbl->start(pid_timer);
    }

    if(0 == fsm->countdown)
    {
        IPC_Send_Self(SSO_DEHYD_INT_STOP_OP_MID, NULL, 0);
    }
}

void SSO_Dehyd_Sunlight_Start_Ctl(union State_Machine * const st_m)
{
    union SSO_Dehyd_FSM * const fsm = _cast(SSO_Dehyd_FSM, st_m);
    Isnt_Nullptr(fsm, );

    union PID_Ctl * pid = fsm->cooler_ctl;
    if (!pid->driver)
    {
        pid->vtbl->start(pid, SSO_Dehyd_Cbk.vtbl->get_driver(&SSO_Dehyd_Cbk, SSO_DEHYD_DRIVER_FAN));
    }

    pid = fsm->heater_ctl;
    if (!pid->driver)
    {
        pid->vtbl->start(pid, SSO_Dehyd_Cbk.vtbl->get_driver(&SSO_Dehyd_Cbk, SSO_DEHYD_DRIVER_GATE));
    }

    if(fsm->heater_ctl->driver || fsm->cooler_ctl->driver)
    {
        union Timer * pid_timer = fsm->pid_timer;
        pid_timer->vtbl->set_time(pid_timer, SSO_DEHYD_PID_TOUT, true);
        pid_timer->vtbl->start(pid_timer);
    }

    if(0 == fsm->countdown)
    {
        IPC_Send_Self(SSO_DEHYD_INT_STOP_OP_MID, NULL, 0);
    }
}

void SSO_Dehyd_Switch_Op(union State_Machine * const st_m)
{
    switch(st_m->current_st)
    {
        case SSO_DEHYD_DARK_OP_STID:
            SSO_Dehyd_Stop_Ctl(st_m);
            SSO_Dehyd_Sunlight_Start_Ctl(st_m);
            break;
        case SSO_DEHYD_SUNLIGHT_OP_STID:
            SSO_Dehyd_Stop_Ctl(st_m);
            SSO_Dehyd_Dark_Start_Ctl(st_m);
            break;
        default: break;
    }
}

void SSO_Dehyd_Feedback_Ctl(union State_Machine * const st_m)
{
    //TODO : feedback
    
}

void SSO_Dehyd_Stop_Ctl(union State_Machine * const st_m)
{
    union SSO_Dehyd_FSM * const fsm = _cast(SSO_Dehyd_FSM, st_m);
    Isnt_Nullptr(fsm, );

    union PID_Ctl * pid = fsm->cooler_ctl;
    if (pid->driver)
    {
        pid->vtbl->stop(pid);
    }

    pid = fsm->heater_ctl;
    if (pid->driver)
    {
        pid->vtbl->stop(pid);
    }

    union Timer * const pid_timer = fsm->pid_timer;
    pid_timer->vtbl->stop(pid_timer);
}

void sso_dehyd_fsm_delete(struct Object * const obj)
{}

void Populate_SSO_Dehyd_FSM(union SSO_Dehyd_FSM * const this,
 union PID_Ctl * const cooler_ctl,
 union PID_Ctl * const heater_ctl)
{
    if(NULL == SSO_Dehyd_FSM.vtbl)
    {
        Populate_FSM(&SSO_Dehyd_FSM.FSM,
        SSO_Dehyd_St_Chart,
        Num_Elems(SSO_Dehyd_St_Chart),
        SSO_Dehyd_FSM_States,
        Num_Elems(SSO_Dehyd_FSM_States));
        Object_Init(&SSO_Dehyd_FSM.Object,
        &SSO_Dehyd_FSM_Class.Class,
        sizeof(SSO_Dehyd_FSM_Class.FSM));

        SSO_Dehyd_FSM.vtbl = &SSO_Dehyd_FSM_Class;
    }
    _clone(this, SSO_Dehyd_FSM);
}
