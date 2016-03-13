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
#include "hamatora_sched.h"
#include "hamatora_sched_def.h"
#include "hamatora_sched_ext.h"
#include "hama_dbg_trace.h"
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
 * Local Object Definitions
 *=====================================================================================*/
static bool Stop_Hama_Sched = true;

#ifdef HOST
#undef HAMA_SCHED_APP
#define HAMA_SCHED_APP(app, init, run, stop) #app,
const char * Sched_Apps_Names[] =
{
      HAMA_SCHED_APPS_TABLE
};
#endif
/*=====================================================================================* 
 * Exported Object Definitions
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Prototypes
 *=====================================================================================*/
static void hamatora_sched_main(void);
static void hamatora_sched_start(void);
static void hamatora_sched_stop(void);
/*=====================================================================================* 
 * Local Inline-Function Like Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Definitions
 *=====================================================================================*/
void hamatora_sched_main(void)
{
   while (Stop_Hama_Sched)
   {
      for(uint8_t app_id = 0; app_id < Num_Of_Scheduled_Apps; app_id++)
      {
         if(0 != Scheduled_Apps[app_id].run)
         {
            TR_INFO_1("Main - %s", Sched_Apps_Names[app_id]);
            Scheduled_Apps[app_id].run();
         }
      }
   }
}

static void hamatora_sched_start(void)
{

   for(uint8_t app_id = 0; app_id < Num_Of_Scheduled_Apps; app_id++)
   {
      if(0 != Scheduled_Apps[app_id].init)
      {
         TR_INFO_1("Init - %s", Sched_Apps_Names[app_id]);
         Scheduled_Apps[app_id].init();
      }
   }
}

static void hamatora_sched_stop(void)
{
   for(uint8_t app_id = 0; app_id < Num_Of_Scheduled_Apps; app_id++)
   {
      if(0 != Scheduled_Apps[app_id].stop)
      {
         TR_INFO_1("Stop - %s", Sched_Apps_Names[app_id]);
         Scheduled_Apps[app_id].stop();
      }
   }
}
/*=====================================================================================* 
 * Exported Function Definitions
 *=====================================================================================*/
void hama::Run_All_Apps(void)
{
   Stop_Hama_Sched = true;
   hamatora_sched_start();
   hamatora_sched_main();
   hamatora_sched_stop();
}

void hama::Shut(void)
{
   Stop_Hama_Sched = false;
}
/*=====================================================================================* 
 * arduino_fwk.cpp
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
