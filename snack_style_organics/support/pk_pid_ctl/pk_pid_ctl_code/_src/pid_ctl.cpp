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
#include "pid_ctl_ext.h"
#include "pid_ctl_set.h"
#include "std_def.h"
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


typedef struct
{
Fix32_T set_point;
Fix32_T feedback;
Fix32_T u_out[2U];
Fix32_T err[2U];
Fix32_T a;
Fix32_T b;
Fix32_T c;
}Pid_Ctl_Channel_T;

typedef struct
{
   bool is_running;
   void (*u_out_func)(const Fix32_T);
   Fix32_T (*feedback_func)(void);
}Pid_Ctl_Callback_T;

typedef struct
{
Fix32_T kp;
Fix32_T ki;
}Pid_Ctl_T;
/*=====================================================================================* 
 * Local Object Definitions
 *=====================================================================================*/
#undef PID_CTL_CHANNEL
#define PID_CTL_CHANNEL(ch) {false, pid::Put_##ch, pid::Get_##ch},

static Pid_Ctl_Callback_T Pid_Callback[PID_CTL_MAX_CHANNELS] =
{
   PID_CTL_CHANNELS_TABLE
};

#undef PID_CTL_LAWS
#define PID_CTL_LAWS(ch, kp, ki) {kp,ki},

const Pid_Ctl_T Pid_Laws_Coeff[PID_CTL_MAX_CHANNELS]=
{
   PID_CTL_LAW_COEFFS_TB
};

static Pid_Ctl_Channel_T Pid_Channels[PID_CTL_MAX_CHANNELS];

const  Fix32_T TAU_MS = PID_CTL_TAU_COEFF_MS * 1000UL;

/*=====================================================================================* 
 * Exported Object Definitions
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Prototypes
 *=====================================================================================*/
static void Pid_Ctl_Calculate_Err(const uint8_t channel);
static void Pid_Ctl_Set_Output(const uint8_t channel);
static void Pid_Ctl_Read_FeedBack(const uint8_t channel);
static void Pid_Tau_Timeout(void);

/*=====================================================================================* 
 * Local Inline-Function Like Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Definitions
 *=====================================================================================*/
void Pid_Ctl_Calculate_Err(const uint8_t channel)
{
   Pid_Channels[channel].err[0] =
            Pid_Channels[channel].set_point - Pid_Channels[channel].feedback;

   Pid_Channels[channel].u_out[0] =
            (Pid_Channels[channel].a*Pid_Channels[channel].u_out[1U]) +
            (Pid_Channels[channel].b*Pid_Channels[channel].err[0]) +
            (Pid_Channels[channel].c*Pid_Channels[channel].err[1U]);
}

void Pid_Ctl_Set_Output(const uint8_t channel)
{
   Pid_Callback[channel].u_out_func( Pid_Channels[channel].u_out[0] );
}

void Pid_Ctl_Read_FeedBack(const uint8_t channel)
{
   Pid_Channels[channel].feedback = Pid_Callback[channel].feedback_func();
}

/*=====================================================================================* 
 * Exported Function Definitions
 *=====================================================================================*/
void pid::Init(void)
{
   uint8_t i = PID_CTL_MAX_CHANNELS;
   memset(Pid_Channels, 0, sizeof(Pid_Channels) );

   while(--i)
   {
      Pid_Channels[i].a = 1U;

      Pid_Channels[i].b = /* b = kp + (ki*tau)/2 */
               Pid_Laws_Coeff[i].kp + ((Pid_Laws_Coeff[i].ki*TAU_MS)>> 1U );

      Pid_Channels[i].c = /* c = (ki*tau)/2 - kp */
               ((Pid_Laws_Coeff[i].ki*TAU_MS)>> 1U ) - Pid_Laws_Coeff[i].kp;
   }
}

void pid::Set_Point(const PID_CHANNEL_T channel, const Fix32_T val)
{
   Pid_Channels[channel].set_point = val;
}

Fix32_T pid::Get_Feedback(const PID_CHANNEL_T channel)
{
   return Pid_Channels[channel].feedback;
}

void pid::Run(const PID_CHANNEL_T channel)
{
   Pid_Callback[channel].is_running = true;
}

void pid::Stop(const PID_CHANNEL_T channel)
{
   Pid_Callback[channel].is_running = false;
}

void pid::Main(void)
{
   Pid_Tau_Timeout();
   for(uint8_t i =0; i < PID_CTL_MAX_CHANNELS ;i++)
   {
      if(Pid_Callback[i].is_running)
      {
         Pid_Channels[i].u_out[1U] = Pid_Channels[i].u_out[0];
         Pid_Channels[i].err[1U] = Pid_Channels[i].err[0];

         Pid_Ctl_Read_FeedBack(i);
         Pid_Ctl_Calculate_Err(i);
         Pid_Ctl_Set_Output(i);
      }
   }
}
/*=====================================================================================* 
 * arduino_fwk.cpp
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/


