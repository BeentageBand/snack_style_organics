#include "ipc.h"
#include "sso_dehydrator_process.h"

#define SSO_DEHYD_POPULATE_DISPATCHER(mid, func) {mid, func},
#define SSO_DEHYD_POPULATE_SUBSCRIPTION(mid, func) mid,

static void sso_dehyd_sunlight_monitor_update(union SSO_Dehyd_Worker * const dehyd, union Mail * const mail);
static void sso_dehyd_temperature_monitor_update(union SSO_Dehyd_Worker * const dehyd, union Mail * const mail);
static void sso_dehyd_pid_timeout(union SSO_Dehyd_Worker * const dehyd, union Mail * const mail);

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
    int32_t sunlight_reading = *(int32_t *)mail->payload;
    if(dehyd->sunlight_reading != sunlight_reading)
    {
        dehyd->sunlight_reading = *(int32_t *)mail->payload;
        IPC_Send_Self(SSO_DEHYD_INT_SUNLIGHT_UPDATE_MID, mail->payload, mail->pay_size);
    }
}

void sso_dehyd_temperature_monitor_update(union SSO_Dehyd_Worker * const dehyd, union Mail * const mail)
{
    int32_t temp_reading = *(int32_t *)mail->payload;
    if(dehyd->temp_reading != temp_reading)
    {
        dehyd->temp_reading = *(int32_t *)mail->payload;
        IPC_Send_Self(SSO_DEHYD_INT_TEMP_UPDATE_MID, mail->payload, mail->pay_size);
    }
}

void sso_dehyd_pid_timeout(union SSO_Dehyd_Worker * const dehyd, union Mail * const mail)
{
    if(dehyd->heater_ctl->is_running)
        dehyd->heater_ctl->vtbl->feed_pid(dehyd->heater_ctl, dehyd->temp_reading);

    if(dehyd->cooler_ctl.is_running)
        dehyd->cooler_ctl->vtbl->feed_pid(dehyd->heater_ctl, dehyd->temp_reading);
}