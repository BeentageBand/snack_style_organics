#define COBJECT_IMPLEMENTATION
#include "pid_ctl.h"
#include "sso_dehydrator_cbk.h"

static void sso_dehyd_cbk_delete(struct Object * const obj);
static union PID_Driver * sso_dehyd_cbk_get_driver(union SSO_Dehyd_Cbk * const this);
static struct PID_Laws sso_dehyd_cbk_get_laws(union SSO_Dehyd_Cbk * const this);

union SSO_Dehyd_Cbk SSO_Dehyd_Cbk = {NULL};
struct SSO_Dehyd_Cbk_Class SSO_Dehyd_Cbk_Class =
{
    {sso_dehyd_cbk_delete, NULL},
    sso_dehyd_cbk_get_driver,
    sso_dehyd_cbk_get_laws
};

void sso_dehyd_cbk_delete(struct Object * const obj)
{}

union PID_Driver * sso_dehyd_cbk_get_driver(union SSO_Dehyd_Cbk * const this)
{
    return NULL;
}

struct PID_Laws sso_dehyd_cbk_get_laws(union SSO_Dehyd_Cbk * const this)
{}

void Populate_SSO_Dehyd_Cbk(union SSO_Dehyd_Cbk * const this)
{
    if(NULL == SSO_Dehyd_Cbk.vtbl)
    {
        SSO_Dehyd_Cbk.vtbl = &SSO_Dehyd_Cbk_Class;
    }
    _clone(this, SSO_Dehyd_Cbk);
}