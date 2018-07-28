#ifndef SSO_POWER_MODE_FSM_H_
#define SSO_POWER_MODE_FSM_H_

#include "fsm.h"
#include "sso_power_mode_types.h"

#define SSO_PM_FSM_DEF(cb) \
FSM_STATE_DEF(cb, SSO_PM_IDLE_STID, \
     FSM_TRANSITION_DEF(cb, SSO_PM_INT_12VDC_REQ_MID,  SSO_PM_IDLE_STID,  SSO_PM_Subscribe_12VDC_Handle) \
     FSM_TRANSITION_DEF(cb, SSO_PM_INT_12VDC_REL_MID,  SSO_PM_IDLE_STID,  SSO_PM_Unsubscribe_12VDC_Handle) \
     FSM_TRANSITION_DEF(cb, SSO_PM_INT_12VDC_INIT_MID, SSO_PM_12VDC_STID, SSO_PM_Init_12VDC_Source) \
     FSM_TRANSITION_DEF(cb, SSO_PM_INT_120AC_REQ_MID,  SSO_PM_IDLE_STID,  SSO_PM_Subscribe_120AC_Handle) \
     FSM_TRANSITION_DEF(cb, SSO_PM_INT_120AC_REL_MID,  SSO_PM_IDLE_STID,  SSO_PM_Unsubscribe__120AC_Handle) \
     FSM_TRANSITION_DEF(cb, SSO_PM_INT_SHUTDOWN_MID,   SSO_PM_SHUT_STID,  SSO_PM_Shut_All) \
     ) \
FSM_STATE_DEF(cb, SSO_PM_12VDC_ON_STID, \
     FSM_TRANSITION_DEF(cb, SSO_PM_INT_12VDC_REQ_MID,  SSO_PM_12VDC_STID,  SSO_PM_Subscribe_12VDC_Handle) \
     FSM_TRANSITION_DEF(cb, SSO_PM_INT_12VDC_REL_MID,  SSO_PM_12VDC_STID,  SSO_PM_Unsubscribe_12VDC_Handle) \
     FSM_TRANSITION_DEF(cb, SSO_PM_INT_120AC_INIT_MID, SSO_PM_120DC_STID,  SSO_PM_Init_120AC_Source) \
     FSM_TRANSITION_DEF(cb, SSO_PM_INT_120AC_REQ_MID,  SSO_PM_12VDC_STID,  SSO_PM_Subscribe_120AC_Handle) \
     FSM_TRANSITION_DEF(cb, SSO_PM_INT_120AC_REL_MID,  SSO_PM_12VDC_STID,  SSO_PM_Unsubscribe__120AC_Handle) \
     FSM_TRANSITION_DEF(cb, SSO_PM_INT_12VDC_SHUT_MID, SSO_PM_IDLE_STID,   SSO_PM_Shut_12VDC_Source) \
     ) \
FSM_STATE_DEF(cb, SSO_PM_120AC_ON_STID, \
     FSM_TRANSITION_DEF(cb, SSO_PM_INT_12VDC_REQ_MID,  SSO_PM_120AC_STID,  SSO_PM_Subscribe_12VDC_Handle) \
     FSM_TRANSITION_DEF(cb, SSO_PM_INT_12VDC_REL_MID,  SSO_PM_120AC_STID,  SSO_PM_Unsubscribe_12VDC_Handle) \
     FSM_TRANSITION_DEF(cb, SSO_PM_INT_120AC_REQ_MID,  SSO_PM_120AC_STID,  SSO_PM_Subscribe_120AC_Handle) \
     FSM_TRANSITION_DEF(cb, SSO_PM_INT_120AC_REL_MID,  SSO_PM_120AC_STID,  SSO_PM_Unsubscribe__120AC_Handle) \
     FSM_TRANSITION_DEF(cb, SSO_PM_INT_120AC_SHUT_MID, SSO_PM_IDLE_STID,   SSO_PM_Shut_120AC_Source) \
     ) \
FSM_STATE_DEF(cb, SSO_PM_SHUT_STID, \
     FSM_TRANSITION_DEF(cb, SSO_PM_INT_SHUTDOWN_MID, SSO_PM_SHUT_STID, SSO_PM_Do_Nothing) \
     ) \

#define SSO_PM_Do_Nothing (NULL)

#define CQueue_Params(IPC_TID)
#include "cqueue.h"
#undef CQueue_Params 

typedef CQueue_IPC_TID_T SSO_PM_Handle_T;

typedef union SSO_PM_FSM
{
    union SSO_PM_FSM_Class _private * _private vtbl;
    struct
    {
        union FSM FSM;
        SSO_PM_Source_T _private active[SSO_PM_MAX_SOURCE];
        SSO_PM_Handle_T _private * _private source; 
        size_t _private n_sources;
    };
    struct Object Object;
};

typedef union SSO_PM_FSM_Class
{
    struct Class Class;
    union FSM_Class FSM;
}SSO_PM_FSM_Class_T;

extern SSO_PM_FSM_Class_T _private SSO_PM_FSM_Class;

void Populate_SSO_PM_FSM(union SSO_PM_FSM * const fsm);

#endif /*SSO_POWER_MODE_FSM_H_*/