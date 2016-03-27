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

#if HOST
#undef HAMA_SCHED_APP
#define HAMA_SCHED_APP(app, init, run, stop) const Pgm_Char_T Hama_Sched_##app[] PROGMEM = #app;

HAMA_SCHED_APPS_TABLE

#undef HAMA_SCHED_APP
#define HAMA_SCHED_APP(app, init, run, stop) Hama_Sched_##app,

const Pgm_Char_T * const Sched_Apps_Names[] PROGMEM =
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
         const Hama_Apps_T * app = reinterpret_cast<const Hama_Apps_T *>(pgm_read_ptr(Scheduled_Apps + app_id));
         void (*run)(void) = reinterpret_cast<void(*)(void)>(pgm_read_ptr(&app->run));

         if(0 != run)
         {
#if HOST
            TR_INFO_1("Main - %s", Sched_Apps_Names[app_id]);
#else
            TR_INFO_1("Main ", app_id);
#endif
            run();
         }
         else
         {
            TR_INFO("Null run");
         }
      }
   }
}

static void hamatora_sched_start(void)
{
   for(uint8_t app_id = 0; app_id < pgm_read_byte(Num_Of_Scheduled_Apps); app_id++)
   {
      const Hama_Apps_T * app = reinterpret_cast<const Hama_Apps_T *>(pgm_read_ptr(Scheduled_Apps + app_id));
      void (*init)(void) = reinterpret_cast<void(*)(void)>(pgm_read_ptr(&app->init));
      if(0 != init)
      {
#if HOST
         TR_INFO_1("Init - %s", Sched_Apps_Names[app_id]);
#else
         TR_INFO_1("Init - ", app_id);
#endif
         init();
      }
      else
      {
         TR_INFO("Null Init");
      }
   }
}

static void hamatora_sched_stop(void)
{
   for(uint8_t app_id = 0; app_id < Num_Of_Scheduled_Apps; app_id++)
   {
      const Hama_Apps_T * app = reinterpret_cast<const Hama_Apps_T *>(pgm_read_ptr(Scheduled_Apps + app_id));
      void (*stop)(void) = reinterpret_cast<void(*)(void)>(pgm_read_ptr(&app->stop));
      if(0 != stop)
      {
#if HOST
         TR_INFO_1("Stop - %s", Sched_Apps_Names[app_id]);
#else
         TR_INFO_1("Stop - ", app_id);
#endif
         stop();
      }
      else
      {
         TR_INFO("NULL Stop");
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
