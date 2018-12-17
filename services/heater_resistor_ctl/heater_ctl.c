/*=====================================================================================*/
/**
 * heater_ctl.c
 * author : puch
 * date : Oct 22 2015
 *
 * description : Any comments
 *
 */
/*=====================================================================================*/
#define COBJECT_IMPLEMENTATION
/*=====================================================================================*
 * Project Includes
 *=====================================================================================*/
/* 
 #include "heater_ctl_pwm.h"
*/
#include "heater_ctl.h"
#include "heater_ctl_set.h"
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

/*=====================================================================================* * Local Function Prototypes
 *=====================================================================================*/
static void heater_ctl_delete(struct Object * const obj);
static void heater_ctl_set(union Heater_Ctl * const this, uint8_t const out);
static uint8_t heater_ctl_get(union Heater_Ctl * const this);

/*=====================================================================================* 
 * Exported Object Definitions
 *=====================================================================================*/
struct Heater_Ctl_Class Heater_Ctl_Class =
{
    {heater_ctl_delete, NULL},
    heater_ctl_set,
    heater_ctl_get
};
/*=====================================================================================* 
 * Local Object Definitions
 *=====================================================================================*/
static union Heater_Ctl Heater_Ctl = {NULL};
//const TODO arduino_PWM_CHANNEL_T HEATER_CTL_PWM_CHANNEL = TODO arduino_PWM_CHANNEL_1;
/*=====================================================================================* 
 * Local Inline-Function Like Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Definitions
 *=====================================================================================*/
void heater_ctl_delete(struct Object * const obj)
{
   //TODO arduino::Stop_PWM(HEATER_CTL_PWM_CHANNEL);
}

void heater_ctl_set(union Heater_Ctl * const this, uint8_t const out)
{
   if(out < HEATER_MAX_OUTPUT &&
      out > HEATER_MIN_OUTPUT)
   {
      this->out = out;
   }
   else if (out >= HEATER_MAX_OUTPUT)
   {
      this->out = HEATER_MAX_OUTPUT;
   }
   else
   {
      this->out = HEATER_MIN_OUTPUT;
   }
   //TODO arduino::Set_PWM(HEATER_CTL_PWM_CHANNEL, out);
}

uint8_t heater_ctl_get(union Heater_Ctl * const this)
{
   return this->out;
}

/*=====================================================================================* 
 * Exported Function Definitions
 *=====================================================================================*/

void Populate_Heater_Ctl(union Heater_Ctl * const this)
{
    if (NULL == Heater_Ctl.vtbl)
    {
        Heater_Ctl.vtbl = &Heater_Ctl_Class;
       //TODO arduino::Init_PWM(HEATER_CTL_PWM_CHANNEL);
    }
    _clone(this, Heater_Ctl);
}

/*=====================================================================================* 
 * heater_ctl.c
 *=====================================================================================*
 * Log History
 *
*=====================================================================================*/
