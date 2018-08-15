#ifndef SSO_DEHYD_CTL_DISPATCHER_H_
#define SSO_DEHYD_CTL_DISPATCHER_H_

#include "state_machine.h"
#include "worker.h"

typedef union SSO_Dehyd_Worker
{
    union SSO_Dehyd_Worker_Class _private * _private vtbl;
    struct
    {
        union Worker Worker;
        union State_Machine _private * _private st_m;
    };
    union Thread Thread;
    struct Object Object;
}SSO_Dehyd_Worker_T;

typedef union SSO_Dehyd_Worker_Class
{
    union Worker_Class Worker;
    struct Thread_Class Thread;
    struct Class Class;
}SSO_Dehyd_Worker_Class_T;

extern union SSO_Dehyd_Worker_Class _private SSO_Dehyd_Worker_Class;

extern void Populate_SSO_Dehyd_Worker(union SSO_Dehyd_Worker * const dehyd);

#endif /*SSO_DEHYD_CTL_DISPATCHER_H_*/
