#define COBJECT_IMPLEMENTATION
#include "pid_ctl.h"
#include "sso_dehydrator_cbk.h"

static void sso_dehyd_cbk_delete(struct Object * const obj);
static union PID_Driver * sso_dehyd_cbk_get_driver(union SSO_Dehyd_Cbk * const this, PID_Channel_T const channel);
static bool sso_dehyd_cbk_is_ready(union SSO_Dehyd_Cbk * const this, PID_Channel_T const channel);

union SSO_Dehyd_Cbk SSO_Dehyd_Cbk = {NULL};
struct SSO_Dehyd_Cbk_Class SSO_Dehyd_Cbk_Class =
{
    {sso_dehyd_cbk_delete, NULL},
    sso_dehyd_cbk_get_driver,
    sso_dehyd_cbk_is_ready
};

static union PID_Driver PID_Driver[SSO_DEHYD_DRIVER_MAX] = {0};
static PID_Driver_Cbk_T PID_Driver_Cbk[SSO_DEHYD_DRIVER_MAX] = {0};

void sso_dehyd_cbk_delete(struct Object * const obj)
{
    uint8_t i;
    for(i = 0; i < SSO_DEHYD_DRIVER_MAX; ++i)
    {
        _delete(PID_Driver + i);
    }
}

union PID_Driver * sso_dehyd_cbk_get_driver(union SSO_Dehyd_Cbk * const this, PID_Channel_T const channel)
{
    if (channel >= SSO_DEHYD_DRIVER_MAX) return false;
    return PID_Driver + channel;
}

bool sso_dehyd_cbk_is_ready(union SSO_Dehyd_Cbk * const this, PID_Channel_T const channel)
{
    if (channel >= SSO_DEHYD_DRIVER_MAX) return false;
    return PID_Driver[channel].vtbl;
}

void Populate_SSO_Dehyd_Cbk(union SSO_Dehyd_Cbk * const this)
{
    if(NULL == SSO_Dehyd_Cbk.vtbl)
    {
        SSO_Dehyd_Cbk.vtbl = &SSO_Dehyd_Cbk_Class;
        uint8_t i;
        for(i = 0; i < SSO_DEHYD_DRIVER_MAX; ++i)
        {
            Populate_PID_Driver(PID_Driver + i, PID_Driver_Cbk + i);
        }
    }
    _clone(this, SSO_Dehyd_Cbk);
}