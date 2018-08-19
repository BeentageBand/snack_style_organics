/*=====================================================================================*/
/**
 * arduino_fwk.cpp
 * author : puch
 * date : Oct 22 2015
 *
 * description : Any comments
 *
 */
/*=====================================================================================*/

/*=====================================================================================*
 * Project Includes
 *=====================================================================================*/
#include "pid_ctl.h"
#include "pid_ctl_set.h"
#include "dbg_log.h"
#include "ipc.h"
/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/

/*=====================================================================================* 
 * Local X-Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Define Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Type Definitions
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Prototypes
 *=====================================================================================*/
static void pid_ctl_set_point(union PID_Ctl * const this, PID_Fix32_T const set_point);
static void pid_ctl_start(union PID_Ctl * const this, union PID_Driver * const driver);
static void pid_ctl_stop(union PID_Ctl * const this);
static void pid_ctl_loop(union PID_Ctl * const this, PID_Fix32_T const input);
static PID_Fix32_T pid_ctl_feedback(union PID_Ctl * const this);

static void pid_ctl_calculate_err(union PID_Ctl * const this);
static void pid_ctl_set_output(union PID_Ctl * const this);
static void pid_ctl_read_feedback(union PID_Ctl * const this);
static bool pid_ctl_wait_for_sample(void);
/*=====================================================================================* 
 * Local Object Definitions
 *=====================================================================================*/

const  Fix32_T TAU_MS PROGMEM = PID_CTL_TAU_COEFF_MS * 1000UL;

#undef PID_CTL_LAWS
#define PID_CTL_LAWS(ch, kp, ki) \
const Pid_Ctl_T ch##_Coeffs PROGMEM = \
   {\
      1U,\
      /* b = kp + (ki*tau)/2 */\
      ( kp + ( ( ki * (PID_CTL_TAU_COEFF_MS * 1000UL) ) >> 1U ) ),\
      /* c = (ki*tau)/2 - kp */\
      ( ( ( ki * (PID_CTL_TAU_COEFF_MS * 1000UL) ) >> 1U ) - kp)\
   };

PID_CTL_LAW_COEFFS_TB

#undef PID_CTL_LAWS
#define PID_CTL_LAWS(ch, kp, ki) &ch##_Coeffs,

const Pid_Ctl_T * const Pid_Laws_Coeff[PID_CTL_MAX_CHANNELS] PROGMEM=
{
   PID_CTL_LAW_COEFFS_TB
};

static Pid_Ctl_Channel_T Pid_Channels[PID_CTL_MAX_CHANNELS];

static uint32_t Sample_Tout = 0;
/*=====================================================================================* 
 * Exported Object Definitions
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Inline-Function Like Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Definitions
 *=====================================================================================*/
void pid_ctl_calculate_err(union PID_Ctl * const this)
{
   struct PID_Laws * const laws = &this->driver->laws;
   this->err[0] =
            this->set_point - this->feedback;
   this->u_out[0] =
            ( laws->a * this->u_out[1U]) +
            ( laws->b * this->err[0]) +
            ( laws->c * this->err[1U]);
}

void pid_ctl_set_output(union PID_Ctl * const this)
{
      Isnt_Nullptr(this->driver, );
      this->driver->vtbl->write_u(this->driver, this->u_out[0]);
}

void pid_ctl_read_feedback(PID_Ctl * const this)
{
      this->err[0] = this->set_point - this->feedback;
}

bool pid_ctl_wait_for_sample(union PID_Ctl * const this)
{
   uint32_t time_now = IPC_Clock();
   TR_INFO_2("Waiting %ld == %ld", (long)time_now, (long)this->time);
   Isnt_Nullptr(this->driver, false);
   return ( (time_now -  this->time) >= this->sample_tout);
}
/*=====================================================================================* 
 * Exported Function Definitions
 *=====================================================================================*/
void pid_ctl_start(union PID_Ctl * const this, union PID_Driver * const driver);
{
      this->time_now = IPC_Clock();
      this->driver = driver;
}

void pid_ctl_set_point(union PID_Ctl * const this, PID_Fix32_T const set_point)
{
   TR_INFO_2("pid::Set_Point pid_ch = %d, val %d", this->channel,(int32_t)set_point);
   this->set_point = set_point;
}

PID_Fix32_T pid_ctl_feedback(union PID_Ctl * const this)
{
      return this->feedback;
}

void pid_ctl_stop(union PID_Ctl * const this)
{
   this->driver = NULL;
}

void pid_ctl_loop(union PID_Ctl * const this, PID_Fix32_T const input_sample)
{
      while(!pid_ctl_wait_sample()){}
      this->time = sample_tout;

      if (this->driver)
      {
            this->u_out[1U] = this->u_out[0];
            this->err[1U] = this->err[0];
            pid_ctl_read_feedback(this);
            pid_ctl_calculate_err(this);
            pid_ctl_set_output(this);
      }
}