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
#define COBJECT_IMPLEMENTATION
#define Dbg_FID PID_FID, 0
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
static void pid_ctl_delete(struct Object * const this);
static void pid_ctl_set_point(union PID_Ctl * const this, PID_Fix32_T const set_point);
static void pid_ctl_start(union PID_Ctl * const this, union PID_Driver * const driver);
static void pid_ctl_stop(union PID_Ctl * const this);
static void pid_ctl_loop(union PID_Ctl * const this, PID_Fix32_T const input);
static PID_Fix32_T pid_ctl_feedback(union PID_Ctl * const this);

static void pid_ctl_calculate_err(union PID_Ctl * const this);
static void pid_ctl_set_output(union PID_Ctl * const this);
static void pid_ctl_read_feedback(union PID_Ctl * const this);
static bool pid_ctl_wait_for_sample(union PID_Ctl * const this);
/*=====================================================================================* 
 * Local Object Definitions
 *=====================================================================================*/
static union PID_Ctl PID_Ctl = {NULL};
/*=====================================================================================* 
 * Exported Object Definitions
 *=====================================================================================*/
struct PID_Ctl_Class PID_Ctl_Class =
{
     {pid_ctl_delete, NULL},
     pid_ctl_set_point,
     pid_ctl_start,
     pid_ctl_stop,
     pid_ctl_loop,
     pid_ctl_feedback
};
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

void pid_ctl_read_feedback(union PID_Ctl * const this)
{
      this->err[0] = this->set_point - this->feedback;
}

bool pid_ctl_wait_for_sample(union PID_Ctl * const this)
{
   uint32_t time_now = IPC_Clock();
   Dbg_Info("Waiting %ld == %ld", time_now, this->time);
   Isnt_Nullptr(this->driver, false);
   
   return ( (time_now -  this->time) >= this->sample_tout);
}
/*=====================================================================================* 
 * Exported Function Definitions
 *=====================================================================================*/
void pid_ctl_delete(struct Object * const this){}

void pid_ctl_start(union PID_Ctl * const this, union PID_Driver * const driver)
{
      this->time = IPC_Clock();
      this->driver = driver;
}

void pid_ctl_set_point(union PID_Ctl * const this, PID_Fix32_T const set_point)
{
   Dbg_Info("%s val %d", __func__, set_point);
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
      while(!pid_ctl_wait_for_sample(this)){}
      this->u_out[0] = input_sample;

      if (this->driver)
      {
            this->u_out[1U] = this->u_out[0];
            this->err[1U] = this->err[0];
            pid_ctl_read_feedback(this);
            pid_ctl_calculate_err(this);
            pid_ctl_set_output(this);
      }
}

void Populate_PID_Ctl(union PID_Ctl * const this)
{
      if(NULL == PID_Ctl.vtbl)
      {
            PID_Ctl.vtbl = &PID_Ctl_Class;
      }
      _clone(this, PID_Ctl);
}
