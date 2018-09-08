#ifndef SSO_HID_PROCESS_H_
#define SSO_HID_PROCESS_H_

#include "sso_hid_worker.h"

#define CHash_Set_HID CHash_Set_Pair_IPC_MID_SSO_HID_Process
typedef void (* SSO_HID_Process_T )(union SSO_HID_Worker * const, union Mail * const);

#define CHash_Map_Params IPC_MID, SSO_HID_Process
#include "chash_map.h"
#undef CHash_Map_Params

typedef CHash_Map_IPC_MID_SSO_HID_Process_T SSO_HID_Dispatcher_T;
typedef Pair_IPC_MID_SSO_HID_Process_T SSO_HID_Process_MID_T;

extern void Populate_SSO_HID_Dispatcher(SSO_HID_Dispatcher_T * const dispatcher);

#endif /* SSO_HID_PROCESS_H_ */
