/*
 * snack_style_organics_launcher.cpp
 *
 * Created: 07/01/2016 12:51:27 a.m.
 * Author : ASUS
 */ 

/*================================================================================================*
 * Project Includes
 *================================================================================================*/
#include "arduino_fwk_dio.h"
#include "arduino_fwk_clk.h"
#include "hamatora_sched.h"
#include "hamatora_sched_ext.h"
#include "hama_dbg_trace.h"
#include "std_def.h"
#include "snack_style_organics_task_def.h"

/*================================================================================================*
 * Standard Includes
 *================================================================================================*/

/*================================================================================================*
 * Local Prototypes
 *================================================================================================*/
#define SSO_Task_Build(object, id, desc) (& CAT(object, _New_Tid)(id)->Node),
/*================================================================================================*
 * Local Object Definitions
 *================================================================================================*/
static Node * SSO_Nodes[] =
{
	SSO_TASKS_TABLE(SSO_Task_Build)
};
/*================================================================================================*
 * Local Main Definition
 *================================================================================================*/

/*================================================================================================*
 * Local Main Definition
 *================================================================================================*/

int main(void)
{
	static SSO_Dispatcher_T passive_dispatcher = SSO_Dispatcher();

	for(Node * it = SSO_Nodes; it != SSO_Nodes+1; ++it)
	{
		passive_dispatcher.vtbl->register_node(&SSO_Dispatcher, it);
	}

	passive_dispatcher.vtbl->on_start(&passive_dispatcher);

	while(true)
	{
		Mail_T * mail = IPC_Retrieve(500);

		passive_dispatcher.vtbl->on_periodic(&passive_dispatcher);

		if(NULL != mail)
		{
			passive_dispatcher.vtbl->on_message(&passive_dispatcher, mail);

			if(WORKER_SHUTDOWN == mail->mid)
			{
				break;
			}
		}
	}

	passive_dispatcher.vtbl->on_stop(&passive_dispatcher);

	for(Node * it = SSO_Nodes; it != SSO_Nodes+1; ++it)
	{
		_delete(it);
	}
}

