#define COBJECT_IMPLEMENTATION
#include "pid_driver.h"

static void pid_driver_delete(struct Object * const obj);
static void pid_driver_write_u(union PID_Driver * const this, PID_Fix32_T const u);
static void pid_driver_cbk_dummy(union PID_Driver * const this, PID_Fix32_T const u);
static void pid_driver_tune(union PID_Driver * const this, PID_Fix32_T const ki,
                PID_Fix32_T const kp, PID_Fix32_T const tau);

static union PID_Driver PID_Driver = {NULL};

struct PID_Driver_Class PID_Driver_Class =
{
    {pid_driver_delete, NULL},
    pid_driver_write_u,
    pid_driver_tune
};

void pid_driver_delete(struct Object * const obj)
{}

void pid_driver_write_u(union PID_Driver * const this, PID_Fix32_T const u)
{
    this->cbk(this, u);
}

void pid_driver_cbk_dummy(union PID_Driver * const this, PID_Fix32_T const u){}

void pid_driver_tune(union PID_Driver * const this, PID_Fix32_T const ki,
                PID_Fix32_T const kp, PID_Fix32_T const tau)
{
    struct PID_Laws * const law = &this->laws;
    law->tau = tau * 1000UL;
    law->a = 1U;
      /* b = kp + (ki*tau)/2 */\
    law->b = ( kp + ( ( ki * (law->tau) ) >> 1U ) );
      /* c = (ki*tau)/2 - kp */\
    law->c = ( ( ( ki * (law->tau) ) >> 1U ) - kp);
}

void Populate_PID_Driver(union PID_Driver * const this, PID_Driver_Cbk_T cbk)
{
    if(NULL == PID_Driver.vtbl)
    {
        PID_Driver.vtbl = &PID_Driver_Class;
        PID_Driver.cbk = pid_driver_cbk_dummy;
        pid_driver_tune(&PID_Driver, 0, 0, 1);
    }
    _clone(this, PID_Driver);
    this->cbk = cbk;
}