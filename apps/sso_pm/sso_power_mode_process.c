/*=====================================================================================*/
/**
 * snack_power_mode.cpp
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
#include "sso_power_mode_process.h"
#include "sso_power_mode_ext.h"
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
#define SSO_PM_PROCESS_POPULATE_SUBSCRIPTION(mid, func) mid,
#define SSO_PM_PROCESS_POPULATE_DISPATCHER(mid, func) {mid, func},
#define CHash_Set_Dispatcher CHash_Set_Pair_IPC_MID_SSO_PM_Process
/*=====================================================================================* 
 * Local Type Definitions
 *=====================================================================================*/
#define CHash_Map_Params IPC_MID, SSO_PM_Process
#include "chash_map.c"
#undef CHash_Map_Params
/*=====================================================================================* 
 * Local Function Prototypes
 *=====================================================================================*/
static void sso_pm_release_all(union SSO_PM_Worker * const sso_pm, union Mail * const mail);
static void sso_pm_power_request(union SSO_PM_Worker * const sso_pm, union Mail * const mail);
/*=====================================================================================* 
 * Local Object Definitions
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Object Definitions
 *=====================================================================================*/
SSO_PM_Processed_MID_T SSO_Process_List [] =
{
   SSO_PM_PROCESS_MAILIST(SSO_PM_PROCESS_POPULATE_DISPATCHER)
};
SSO_PM_Dispatcher_T SSO_PM_Dispatcher = {NULL};
CQueue_SSO_PM_Handle_Req_T SSO_PM_Handle_Req_Queue = {NULL};
/*=====================================================================================* 
 * Local Inline-Function Like Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Definitions
 *=====================================================================================*/
void sso_pm_release_all(union SSO_PM_Worker * const sso_pm, union Mail * const mail)
{

}

void sso_pm_power_request(union SSO_PM_Worker * const sso_pm, union Mail * const mail)
{
   SSO_PM_Handle_Req_T pm_req = *(SSO_PM_Handle_Req_T *)mail->payload;
   SSO_PM_Handle_Req_Queue.vtbl->push_front(&SSO_PM_Handle_Req_Queue, pm_req);
}

/*=====================================================================================* 
 * Exported Function Definitions
 *=====================================================================================*/
/*=====================================================================================* 
 * snack_power_mode.c
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
