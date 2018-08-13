#define COBJECT_IMPLEMENTATION
#include "sso_dehydrator_fsm.h"

static bool SSO_Dehyd_Ready_Guard(union State_Machine * const stm, union St_Machine_State * const st);
static bool SSO_Dehyd_Dark_Stby_Guard(union State_Machine * const stm, union St_Machine_State * const st);
static bool SSO_Dehyd_Sunlight_Stby_Guard(union State_Machine * const stm, union St_Machine_State * const st);
static bool SSO_Dehyd_Dark_Start_Guard(union State_Machine * const stm, union St_Machine_State * const st);
static bool SSO_Dehyd_Sunlight_Start_Guard(union State_Machine * const stm, union St_Machine_State * const st);
static bool SSO_Dehyd_Dark2Sunlight_Op_Guard(union State_Machine * const stm, union St_Machine_State * const st);
static bool SSO_Dehyd_Sunlight2Dark_Op_Guard(union State_Machine * const stm, union St_Machine_State * const st);
static bool SSO_Dehyd_Sunlight_Start_Guard(union State_Machine * const stm, union St_Machine_State * const st);
static bool SSO_Dehyd_Stop_Guard(union State_Machine * const stm, union St_Machine_State * const st);

static void SSO_Dehyd_Gets_Ready(union State_Machine * const stm);
static void SSO_Dehyd_Dark_Start_Ctl(union State_Machine * const stm);
static void SSO_Dehyd_Sunlight_Start_Ctl(union State_Machine * const stm);
static void SSO_Dehyd_Switch_Op(union State_Machine * const stm);
static void SSO_Dehyd_Stop_Ctl(union State_Machine * const stm);

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
    return SSO_Dehyd_Sunlight_Start_Guard(st_m, st) fsm->sunlight_reading > sunlight_limit;
}
bool SSO_Dehyd_Sunlight2Dark_Op_Guard(union State_Machine * const st_m, union St_Machine_State * const st)
{
    union SSO_Dehyd_FSM * const fsm = _cast(SSO_Dehyd_FSM, st_m);
    Isnt_Nullptr(fsm, false);
    int32_t sunlight_limit = SSO_DEHYDRATOR_MIN_SUNLIGHT + SSO_DEHYDRATOR_HYSTHERESIS; 

    return SSO_Dehyd_Dark_Start_Guard(st_m, st) && fsm->sunlight_reading < sunlight_limit;
}

bool SSO_Dehyd_Stop_Guard(union State_Machine * const stm, union St_Machine_State * const st)
{
    union SSO_Dehyd_FSM * const fsm = _cast(SSO_Dehyd_FSM, st_m);
    Isnt_Nullptr(fsm, false);
    return true;
}

void SSO_Dehyd_Gets_Ready(union State_Machine * const stm)
{
    union SSO_Dehyd_FSM * const fsm = _cast(SSO_Dehyd_FSM, st_m);
    Isnt_Nullptr(fsm, false);
    IPC_MID_T mid = (SSO_DEHYDRATOR_MIN_SUNLIGHT > fsm->sunlight_reading)? 
        SSO_DEHYD_INT_DARK_MODE_OP_MID : SSO_DEHYD_INT_SUNLIGHT_MODE_OP_MID;
    IPC_Send_Self(mid, NULL, 0);
}

void SSO_Dehyd_Dark_Start_Ctl(union State_Machine * const st_m)
{
    union SSO_Dehyd_FSM * const fsm = _cast(SSO_Dehyd_FSM, st_m);
    Isnt_Nullptr(fsm, false);
    union PID_Ctl * pid = fsm->cooler_ctl;
    if (!pid->is_running)
    {
        pid->vtbl->start(pid, SSO_Dehyd_Cbk.vtbl->get_driver(&SSO_Dehyd_Cbk, SSO_DEHYD_DRIVER_FAN));
    }

    pid = fsm->heater_ctl;

    if (!pid->is_running)
    {
        pid->vtbl->start(pid, SSO_Dehyd_Cbk.vtbl->get_driver(&SSO_Dehyd_Cbk, SSO_DEHYD_DRIVER_ELECTRIC_HEATER));
    }

    if(fsm->heater_ctl->is_running || fsm->cooler_ctl->is_running)
    {
        union Timer * pid_timer = fsm->pid_timer;
        pid_timer->vtbl->start(pid_timer, SSO_DEHYD_PID_TOUT);
    }

    if(0 == fsm->countdown)
    {
        IPC_Send_Self(SSO_DEHYD_INT_STOP_OP_MID, NULL, 0);
    }
}

void SSO_Dehyd_Sunlight_Start_Ctl(union State_Machine * const stm)
{
    union SSO_Dehyd_FSM * const fsm = _cast(SSO_Dehyd_FSM, st_m);
    Isnt_Nullptr(fsm, false);

    union PID_Ctl * pid = fsm->cooler_ctl;
    if (!pid->is_running)
    {
        pid->vtbl->start(pid, SSO_Dehyd_Cbk.vtbl->get_driver(&SSO_Dehyd_Cbk, SSO_DEHYD_DRIVER_FAN));
    }

    pid = fsm->heater_ctl;
    if (!pid->is_running)
    {
        pid->vtbl->start(pid, SSO_Dehyd_Cbk.vtbl->get_driver(&SSO_Dehyd_Cbk, SSO_DEHYD_DRIVER_GATE));
    }

    if(fsm->heater_ctl->is_running || fsm->cooler_ctl->is_running)
    {
        union Timer * pid_timer = fsm->pid_timer;
        pid_timer->vtbl->start(pid_timer, SSO_DEHYD_PID_TOUT);
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

void SSO_Dehyd_Stop_Ctl(union State_Machine * const stm)
{
    union SSO_Dehyd_FSM * const fsm = _cast(SSO_Dehyd_FSM, st_m);
    Isnt_Nullptr(fsm, false);

    union PID_Ctl * pid = fsm->cooler_ctl;
    if (pid->is_running)
    {
        pid->vtbl->stop(pid);
    }

    pid = fsm->heater_ctl;
    if (pid->is_running)
    {
        pid->vtbl->stop(pid);
    }

    union Timer * const pid_timer = fsm->pid_timer;
    pid_timer->vtbl->stop(pid_timer);
}