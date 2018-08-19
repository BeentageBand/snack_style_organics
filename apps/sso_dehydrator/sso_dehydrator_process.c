#define COBJECT_IMPLEMENTATION
#include "ipc.h"
#include "sso_dehydrator_process.h"
#include "sso_dehydrator_fsm.h"

#define SSO_DEHYD_POPULATE_DISPATCHER(mid, func) {mid, func},
#define SSO_DEHYD_POPULATE_SUBSCRIPTION(mid, func) mid,

static void sso_dehyd_sunlight_monitor_update(union SSO_Dehyd_Worker * const dehyd, union Mail * const mail);
static void sso_dehyd_temperature_monitor_update(union SSO_Dehyd_Worker * const dehyd, union Mail * const mail);
static void sso_dehyd_pid_timeout(union SSO_Dehyd_Worker * const dehyd, union Mail * const mail);
static void sso_dehyd_release(union SSO_Dehyd_Worker * const dehyd, union Mail * const mail);

SSO_Dehyd_Dispatcher_T SSO_Dehyd_Dispatcher[] =
{
    SSO_DEHYD_PROCESS_MAILIST(SSO_DEHYD_POPULATE_DISPATCHER)
};

IPC_MID_T SSO_Dehyd_Mailist[] =
{
    SSO_DEHYD_SUBSCRIPTION_MAILIST(SSO_DEHYD_POPULATE_SUBSCRIPTION)
};

void sso_dehyd_sunlight_monitor_update(union SSO_Dehyd_Worker * const dehyd, union Mail * const mail)
{
    union SSO_Dehyd_FSM * const fsm = _cast(SSO_Dehyd_FSM, dehyd->st_m);
    int32_t sunlight_reading = *(int32_t *)mail->payload;
    if(fsm->sunlight_reading != sunlight_reading)
    {
        fsm->sunlight_reading = *(int32_t *)mail->payload;
        IPC_Send_Self(SSO_DEHYD_INT_SUNLIGHT_UPDATE_MID, mail->payload, mail->pay_size);
    }
}

void sso_dehyd_temperature_monitor_update(union SSO_Dehyd_Worker * const dehyd, union Mail * const mail)
{
    union SSO_Dehyd_FSM * const fsm = _cast(SSO_Dehyd_FSM, dehyd->st_m);
    Isnt_Nullptr(fsm, );
    int32_t temp_reading = *(int32_t *)mail->payload;
    if(fsm->temp_reading != temp_reading)
    {
        fsm->temp_reading = *(int32_t *)mail->payload;
        IPC_Send_Self(SSO_DEHYD_INT_TEMP_UPDATE_MID, mail->payload, mail->pay_size);
    }
}

void sso_dehyd_pid_timeout(union SSO_Dehyd_Worker * const dehyd, union Mail * const mail)
{
    union SSO_Dehyd_FSM * const fsm = _cast(SSO_Dehyd_FSM, dehyd->st_m);
    Isnt_Nullptr(fsm, );

    if(fsm->heater_ctl->driver)
        fsm->heater_ctl->vtbl->loop(fsm->heater_ctl, fsm->temp_reading);

    if(fsm->cooler_ctl->driver)
        fsm->cooler_ctl->vtbl->loop(fsm->cooler_ctl, fsm->temp_reading);
}

void sso_dehyd_release(union SSO_Dehyd_Worker * const dehyd, union Mail * const mail)
{

}