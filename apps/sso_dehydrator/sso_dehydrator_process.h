#ifndef SSO_DEHYDRATOR_PROCESS_H_
#define SSO_DEHYDRATOR_PROCESS_H_

#include "sso_dehydrator_types.h"
#include "sso_dehydrator_uset.h"
#include "sso_dehydrator_worker.h"

#define SSO_DEHYD_PROCESS_MAILIST(X) \
SSO_DEHYD_SUBSCRIPTION_MAILIST(X) \
X(SSO_DEHYD_INT_SUNLIGHT_UPDATE_MID,  sso_dehyd_sunlight_monitor_update)\
X(SSO_DEHYD_INT_TEMP_UPDATE_MID,      sso_dehyd_temperature_monitor_update) \
X(SSO_DEHYD_INT_TIMER_UPDATE_MID,     sso_dehyd_pid_timeout) \

#ifdef __cplusplus
extern "C"{
#endif

typedef void (* SSO_Dehyd_Process_T)(union SSO_Dehyd_Worker * const, union Mail * const);

#define CHash_Map_Params IPC_MID, SSO_Dehyd_Process
#include "chash_map.h"
#undef CHash_Map_Params 

typedef CHash_Map_IPC_MID_SSO_Dehyd_Process_T SSO_Dehyd_Dispatcher_T;
extern SSO_Dehyd_Dispatcher_T SSO_Dehyd_Dispatcher[];

extern IPC_MID_T SSO_Dehyd_Mailist[];

#ifdef __cplusplus
}
#endif
#endif /*SSO_DEHYDRATOR_PROCESS_H_*/