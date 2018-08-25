#ifndef SSO_DEHYDRATOR_FSM_H_
#define SSO_DEHYDRATOR_FSM_H_

#include "fsm.h"
#include "pid_ctl.h"
#include "sso_dehydrator_types.h"
#include "tmr.h"

#define SSO_DEHYD_FSM_DEF(cb) \
FSM_STATE_DEF(cb, SSO_DEHYD_IDLE_STID, \
     FSM_TRANSITION_DEF(cb, SSO_DEHYD_INT_SUNLIGHT_UPDATE_MID, SSO_DEHYD_READY_STID,  SSO_Dehyd_Ready_Guard, SSO_Dehyd_Gets_Ready) \
     FSM_TRANSITION_DEF(cb, SSO_DEHYD_INT_TEMP_UPDATE_MID,     SSO_DEHYD_READY_STID,  SSO_Dehyd_Ready_Guard, SSO_Dehyd_Gets_Ready) \
     FSM_TRANSITION_DEF(cb, SSO_DEHYD_INT_DRIVERS_READY_MID,   SSO_DEHYD_READY_STID,  SSO_Dehyd_Ready_Guard, SSO_Dehyd_Gets_Ready) \
)\
FSM_STATE_DEF(cb, SSO_DEHYD_READY_STID, \
     FSM_TRANSITION_DEF(cb, SSO_DEHYD_INT_DARK_MODE_OP_MID,     SSO_DEHYD_DARK_STBY_STID,      SSO_Dehyd_Dark_Stby_Guard,     SSO_Dehyd_Do_Nothing) \
     FSM_TRANSITION_DEF(cb, SSO_DEHYD_INT_SUNLIGHT_MODE_OP_MID, SSO_DEHYD_SUNLIGHT_STBY_STID,  SSO_Dehyd_Sunlight_Stby_Guard, SSO_Dehyd_Do_Nothing) \
)\
FSM_STATE_DEF(cb, SSO_DEHYD_DARK_STBY_STID, \
     FSM_TRANSITION_DEF(cb, SSO_DEHYD_INT_SUNLIGHT_UPDATE_MID, SSO_DEHYD_DARK_STBY_STID,  SSO_Dehyd_Ready_Guard,      SSO_Dehyd_Gets_Ready) \
     FSM_TRANSITION_DEF(cb, SSO_DEHYD_INT_TEMP_UPDATE_MID,     SSO_DEHYD_DARK_STBY_STID,  SSO_Dehyd_Ready_Guard,      SSO_Dehyd_Gets_Ready) \
     FSM_TRANSITION_DEF(cb, SSO_DEHYD_INT_START_OP_MID,        SSO_DEHYD_DARK_OP_STID,    SSO_Dehyd_Dark_Start_Guard, SSO_Dehyd_Dark_Start_Ctl) \
     FSM_TRANSITION_DEF(cb, SSO_DEHYD_INT_TIMER_UPDATE_MID,    SSO_DEHYD_DARK_OP_STID,    SSO_Dehyd_Dark_Start_Guard, SSO_Dehyd_Dark_Start_Ctl) \
)\
FSM_STATE_DEF(cb, SSO_DEHYD_SUNLIGHT_STBY_STID, \
     FSM_TRANSITION_DEF(cb, SSO_DEHYD_INT_SUNLIGHT_UPDATE_MID, SSO_DEHYD_SUNLIGHT_STBY_STID,  SSO_Dehyd_Ready_Guard,          SSO_Dehyd_Gets_Ready) \
     FSM_TRANSITION_DEF(cb, SSO_DEHYD_INT_TEMP_UPDATE_MID,     SSO_DEHYD_SUNLIGHT_STBY_STID,  SSO_Dehyd_Ready_Guard,          SSO_Dehyd_Gets_Ready) \
     FSM_TRANSITION_DEF(cb, SSO_DEHYD_INT_START_OP_MID,        SSO_DEHYD_SUNLIGHT_OP_STID,    SSO_Dehyd_Sunlight_Start_Guard, SSO_Dehyd_Sunlight_Start_Ctl) \
     FSM_TRANSITION_DEF(cb, SSO_DEHYD_INT_TIMER_UPDATE_MID,    SSO_DEHYD_SUNLIGHT_OP_STID,    SSO_Dehyd_Sunlight_Start_Guard, SSO_Dehyd_Sunlight_Start_Ctl) \
)\
FSM_STATE_DEF(cb, SSO_DEHYD_DARK_OP_STID, \
     FSM_TRANSITION_DEF(cb, SSO_DEHYD_INT_SUNLIGHT_UPDATE_MID, SSO_DEHYD_SUNLIGHT_OP_STID,    SSO_Dehyd_Dark2Sunlight_Op_Guard, SSO_Dehyd_Switch_Op) \
     FSM_TRANSITION_DEF(cb, SSO_DEHYD_INT_TEMP_UPDATE_MID,     SSO_DEHYD_SUNLIGHT_OP_STID,    SSO_Dehyd_Feedback_Guard,         SSO_Dehyd_Feedback_Ctl) \
     FSM_TRANSITION_DEF(cb, SSO_DEHYD_INT_STOP_OP_MID,         SSO_DEHYD_DARK_STBY_STID,     SSO_Dehyd_Stop_Guard,             SSO_Dehyd_Stop_Ctl) \
)\
FSM_STATE_DEF(cb, SSO_DEHYD_SUNLIGHT_OP_STID, \
     FSM_TRANSITION_DEF(cb, SSO_DEHYD_INT_SUNLIGHT_UPDATE_MID, SSO_DEHYD_DARK_OP_STID,        SSO_Dehyd_Sunlight2Dark_Op_Guard, SSO_Dehyd_Switch_Op) \
     FSM_TRANSITION_DEF(cb, SSO_DEHYD_INT_TEMP_UPDATE_MID,     SSO_DEHYD_SUNLIGHT_OP_STID,    SSO_Dehyd_Feedback_Guard,         SSO_Dehyd_Feedback_Ctl) \
     FSM_TRANSITION_DEF(cb, SSO_DEHYD_INT_STOP_OP_MID,         SSO_DEHYD_SUNLIGHT_STBY_STID,  SSO_Dehyd_Stop_Guard,             SSO_Dehyd_Stop_Ctl) \
)\

#define SSO_Dehyd_Do_Nothing NULL

#ifdef __cplusplus
extern "C" {
#endif

typedef union SSO_Dehyd_FSM
{
    union SSO_Dehyd_FSM_Class _private * _private vtbl;
    struct
    {
        union FSM FSM;
        int32_t temp_reading;
        int32_t sunlight_reading;
        uint16_t countdown;
        union PID_Ctl * cooler_ctl;
        union PID_Ctl * heater_ctl;
        union Timer * pid_timer;
    };
    union State_Machine State_Machine;
    struct Object Object;
}SSO_Dehyd_FSM_T;

typedef union SSO_Dehyd_FSM_Class
{
    union FSM_Class FSM;
    struct State_Machine_Class State_Machine;
    struct Class Class;
}SSO_Dehyd_FSM_Class_T;

extern union SSO_Dehyd_FSM_Class _private SSO_Dehyd_FSM_Class;

extern void Populate_SSO_Dehyd_FSM(union SSO_Dehyd_FSM * const fsm,
 union PID_Ctl * const cooler_ctl,
 union PID_Ctl * const heater_ctl);

#ifdef __cplusplus
}
#endif

#endif /*SSO_DEHYDRATOR_FSM_H_*/