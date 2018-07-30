/**
 * snack_power_mode.h
 * author : puch
 * date : Oct 22 2015
 *
 * description : Any comments
 *
 */
/*=====================================================================================*/
#ifndef SSO_POWER_MODE_PROCESS_H_
#define SSO_POWER_MODE_PROCESS_H_
/*=====================================================================================*
 * Project Includes
 *=====================================================================================*/
#include "sso_power_mode_uset.h"
#include "sso_power_mode_wn.h"
#include "ipc_types.h"
/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported X-Macros
 *=====================================================================================*/
#define SSO_PM_PROCESS_MAILIST(X) \
SSO_PM_SUBSCRIPTION_MAILIST(X) \
X(SSO_PM_INT_REL_ALL_MID,    "Release all handles from all sources") \
X(SSO_PM_INT_12VDC_REQ_MID,  "12VDC Source Power Request") \
X(SSO_PM_INT_12VDC_REL_MID,  "12VDC Source Power Release Request") \
X(SSO_PM_INT_12VDC_INIT_MID, "12VDC Source Init") \
X(SSO_PM_INT_12VDC_SHUT_MID, "12VDC Source Shutdown") \
X(SSO_PM_INT_120AC_REQ_MID,  "120AC Source Power Request") \
X(SSO_PM_INT_120AC_REL_MID,  "120AC Source Power Release Request") \
X(SSO_PM_INT_120AC_INIT_MID, "120AC Source Init") \
X(SSO_PM_INT_120AC_SHUT_MID, "120AC Source Shutdown") \
X(SSO_PM_INT_SHUTDOWN_MID,   "Shutdown sequence start") \

/*=====================================================================================*
 * Exported Define Macros
 *=====================================================================================*/
/*=====================================================================================* 
 * Exported Type Declarations
 *=====================================================================================*/
#ifdef __cplusplus
extern "C"
{
#endif

typedef void (* SSO_PM_Process_T)(union SSO_PM_Worker * sso_pm, union Mail * const);

#define CHash_Map_Params(IPC_MID, SSO_PM_Process_T)
#include "chash_map.h"
#undef CHash_Map_Params
typedef CHash_Map_IPC_MID_SSO_PM_Process_T SSO_PM_Dispatcher_T;
typedef CHash_Map_IPC_MID_SSO_PM_Process_Pair_T SSO_PM_Processed_MID_T;
/*=====================================================================================* 
 * Exported Object Declarations
 *=====================================================================================*/
extern IPC_MID_T SSO_PM_Subscription_Mailist [];
extern SSO_PM_Processed_MID_T SSO_Process_List [];
extern SSO_PM_Dispatcher_T SSO_PM_Dispatcher = {NULL};
extern CQueue_SSO_PM_Handle_Req_T SSO_PM_Handle_Req_Queue = {NULL};
/*=====================================================================================* 
 * Exported Function Prototypes
 *=====================================================================================*/
/*=====================================================================================* 
 * Exported Function Like Macros
 *=====================================================================================*/
#ifdef __cplusplus
}/*extern "C"*/
#endif
/*=====================================================================================* 
 * snack_power_mode.h
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
#endif /*SSO_POWER_MODE_PROCESS_H_*/
