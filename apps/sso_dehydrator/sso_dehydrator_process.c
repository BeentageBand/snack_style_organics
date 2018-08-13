#include "pc.h"
#include "sso_dehydrator_process.h"

static void sso_dehyd_sunlight_monitor_update(union SSO_Dehyd_Worker * const dehyd, union Mail * const mail);
static void sso_dehyd_temperature_monitor_update(union SSO_Dehyd_Worker * const dehyd, union Mail * const mail);
static void sso_dehyd_pid_timeout(union SSO_Dehyd_Worker * const dehyd, union Mail * const mail);

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