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
#include "hama_dbg_trace.h"
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
   bool is_running;
}Pid_Ctl_Channel_T;

typedef struct
{
   void (*u_out_func)(const Fix32_T);
   Fix32_T (*feedback_func)(void);
}Pid_Ctl_Callback_T;

typedef struct
{
   Fix32_T a;
   Fix32_T b;
   Fix32_T c;
}Pid_Ctl_T;
/*=====================================================================================* 
 * Local Object Definitions
 *=====================================================================================*/
#undef PID_CTL_CHANNEL
#define PID_CTL_CHANNEL(ch) const Pid_Ctl_Callback_T Callback_##ch PROGMEM = {pid::Put_##ch, pid::Get_##ch};

PID_CTL_CHANNELS_TABLE

#undef PID_CTL_CHANNEL
#define PID_CTL_CHANNEL(ch) &Callback_##ch,

const Pid_Ctl_Callback_T * const Pid_Callback[2] PROGMEM =
{
   PID_CTL_CHANNELS_TABLE
};

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
 * Local Function Prototypes
 *=====================================================================================*/
static void Pid_Ctl_Calculate_Err(const uint8_t channel);
static void Pid_Ctl_Set_Output(const uint8_t channel);
static void Pid_Ctl_Read_FeedBack(const uint8_t channel);
static bool Wait_For_Sample(void);
/*=====================================================================================* 
 * Local Inline-Function Like Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Definitions
 *=====================================================================================*/
void Pid_Ctl_Calculate_Err(const uint8_t channel)
{
   const Pid_Ctl_T * pid_ptr = reinterpret_cast<const Pid_Ctl_T *>( pgm_read_ptr(Pid_Laws_Coeff + channel));
   Pid_Ctl_T pid_coeffs =
   {
         static_cast<Fix32_T>( pgm_read_dword(pid_ptr->a) ),
         static_cast<Fix32_T>( pgm_read_dword(pid_ptr->b) ),
         static_cast<Fix32_T>( pgm_read_dword(pid_ptr->c) )
   };

   Pid_Channels[channel].err[0] =
            Pid_Channels[channel].set_point - Pid_Channels[channel].feedback;

   Pid_Channels[channel].u_out[0] =
            ( pid_coeffs.a * Pid_Channels[channel].u_out[1U]) +
            ( pid_coeffs.b * Pid_Channels[channel].err[0]) +
            ( pid_coeffs.c * Pid_Channels[channel].err[1U]);
}

void Pid_Ctl_Set_Output(const uint8_t channel)
{
   const Pid_Ctl_Callback_T * pid_cbk = reinterpret_cast<const Pid_Ctl_Callback_T *>(pgm_read_ptr(Pid_Callback + channel) );
   void (*u_out_func)(const Fix32_T) = reinterpret_cast<void (*)(const Fix32_T)>(pgm_read_ptr(&pid_cbk->u_out_func));
   u_out_func( Pid_Channels[channel].u_out[0] );
}

void Pid_Ctl_Read_FeedBack(const uint8_t channel)
{
   const Pid_Ctl_Callback_T * pid_cbk = reinterpret_cast<const Pid_Ctl_Callback_T *>(pgm_read_ptr(Pid_Callback + channel));
   Fix32_T (*feedback_func)(void) = reinterpret_cast< Fix32_T (*)(void)>( pgm_read_ptr( &pid_cbk->feedback_func) );
   Pid_Channels[channel].feedback = feedback_func();
}

bool Wait_For_Sample(void)
{
   uint32_t time_now = pid::Get_Sample_Time();
   TR_INFO_2("Waiting %ld == %ld", (long)time_now, (long)Sample_Tout);
   return ( (time_now -  Sample_Tout) >= PID_CTL_TAU_COEFF_MS);
}
/*=====================================================================================* 
 * Exported Function Definitions
 *=====================================================================================*/
void pid::Init(void)
{
   memset(Pid_Channels, 0, sizeof(Pid_Channels) );
   Sample_Tout = pid::Get_Sample_Time();
}

void pid::Set_Point(const PID_CHANNEL_T channel, const Fix32_T val)
{
   TR_INFO_2("pid::Set_Point pid_ch = %d, val %d", channel,(int32_t)val);
   Pid_Channels[channel].set_point = val;
}

Fix32_T pid::Get_Feedback(const PID_CHANNEL_T channel)
{
   return Pid_Channels[channel].feedback;
}

void pid::Run(const PID_CHANNEL_T channel)
{
   Pid_Channels[channel].is_running = true;
}

void pid::Stop(const PID_CHANNEL_T channel)
{
   Pid_Channels[channel].is_running = false;
}

void pid::Main(void)
{
   if(Wait_For_Sample())
   {
      Sample_Tout = pid::Get_Sample_Time();
      for(uint8_t i =0; i < PID_CTL_MAX_CHANNELS ;i++)
      {
         if(Pid_Channels[i].is_running)
         {

            Pid_Channels[i].u_out[1U] = Pid_Channels[i].u_out[0];
            Pid_Channels[i].err[1U] = Pid_Channels[i].err[0];

            Pid_Ctl_Read_FeedBack(i);
            Pid_Ctl_Calculate_Err(i);
            Pid_Ctl_Set_Output(i);
         }
      }
   }
}
/*=====================================================================================* 
 * arduino_fwk.cpp
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/


