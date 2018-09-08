#define COBJECT_IMPLEMENTATION
#include "sso_hid_process.h"

#define CHash_Map_Params IPC_MID, SSO_HID_Process
#include "chash_map.c"
#undef CHash_Map_Params

static SSO_HID_Dispatcher_T SSO_HID_Dispatcher = {NULL};
static SSO_HID_Process_MID_T SSO_HID_Process_Mailist[] =
{

};

void Populate_SSO_HID_Dispatcher(SSO_HID_Dispatcher_T * const this)
{
    if(NULL == SSO_HID_Dispatcher.vtbl)
    {
        Populate_CHash_Map_IPC_MID_SSO_HID_Process(&SSO_HID_Dispatcher,
                SSO_HID_Process_Mailist,
                Num_Elems(SSO_HID_Process_Mailist),
                NULL);

    }
    _clone(this, SSO_HID_Dispatcher);
}
