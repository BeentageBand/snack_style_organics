#ifndef SSO_DEHYDRATOR_PROCESS_H_
#define SSO_DEHYDRATOR_PROCESS_H_

#include "sso_dehydrator_types.h"

SSO_DEHYD_PROCESS_MAILIST(X) \
SSO_DEHYD_SUBSCRIPTION_MAILIST(X) \
X(SSO_DEHYD_INT_SUNLIGHT_UPDATE_MID,  SSO_Dehyd_Update_Sunlight_Reading)\
X(SSO_DEHYD_INT_TEMP_UPDATE_MID,      SSO_Dehyd_Update_Temperature_Reading) \
X(SSO_DEHYD_INT_TIMER_UPDATE_MID,     SSO_Dehyd_Timer_Timeout) \

#ifdef __cplusplus
extern "C"{
#endif

typedef void (* SSO_Dehyd_Process_T)(union SSO_Dehyd_Worker * const, union Mail * const);

#define CHash_Map_Params IPC_MID, SSO_Dehyd_Process
#include "chash_map.h"
#undef CHash_Map_Params 

typedef CHash_Map_IPC_MID_SSO_Dehyd_Process_T SSO_Dehyd_Dispatcher_T;
extern SSO_Dehyd_Dispatcher_T SSO_Dehyd_Dispatcher[] =
{
    SSO_DEHYD_PROCESS_MAILIST(SSO_DEHYD_POPULATE_DISPATCHER)
};

extern IPC_MID_T SSO_Dehyd_Mailist[] =
{
    SSO_DEHYD_SUBSCRIPTION_MAILIST(SSO_DEHYD_POPULATE_SUBSCRIPTION)
};

#ifdef __cplusplus
}
#endif
#endif /*SSO_DEHYDRATOR_PROCESS_H_*/