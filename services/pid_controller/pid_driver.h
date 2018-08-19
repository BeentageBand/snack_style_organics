#ifndef PID_DRIVER_H_
#define PID_DRIVER_H_

#include "pid_ctl_types.h"
#include "cobject.h"

typedef union PID_Driver
{
    struct PID_Driver_Class _private * _private vtbl;
    struct
    {
        struct Object
        struct PID_Laws laws;
        PID_Driver_Cbk_T cbk;
    };
}PID_Driver_T;

typedef struct PID_Driver_Class
{
    struct Class Class;
    void (*_private write_u)(union PID_Driver * const, PID_Fix32_T const);
    void (*_private tune)(union PID_Driver * const, PID_Fix32_T const,
                PID_Fix32_T const, PID_Fix32_T const);
}PID_Driver_Class_T:

extern struct PID_Driver_Class _private PID_Driver_Class;

extern void Populate_PID_Driver(union PID_Driver * const drv, PID_Driver_Cbk_T cbk);
#endif /*PID_DRIVER_H_*/