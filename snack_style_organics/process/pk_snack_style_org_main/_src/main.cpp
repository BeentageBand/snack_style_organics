/*
 * snack_style_organics.cpp
 *
 * Created: 07/01/2016 12:51:27 a.m.
 * Author : ASUS
 */ 

#include "hamatora_sched_def.h"
#include "hamatora_sched.h"
#include "hamatora_sched_ext.h"

#undef HAMA_SCHED_APP
#define HAMA_SCHED_APP(app, init, run, stop) {app, init, run, stop},

const Hama_Apps_T Scheduled_Apps[] =
{
   HAMA_SCHED_APPS_TABLE
};

const uint8_t Num_Of_Scheduled_Apps = sizeof(Scheduled_Apps)/sizeof(Scheduled_Apps[0]);

int main(void)
{
   /* Replace with your application code */
   hama::Run_All_Apps();
   return 0;
}

