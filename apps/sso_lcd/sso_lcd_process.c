#define COBJECT_IMPLEMENTATION
#include "sso_lcd_process.h"

#define CHash_Map_Params IPC_MID, SSO_LCD_Process
#include "chash_map.c"
#undef CHash_Map_Params

static SSO_LCD_Dispatcher_T SSO_LCD_Dispatcher = {NULL};
static SSO_LCD_Process_MID_T SSO_LCD_Process_Mailist[] =
{

};

void Populate_SSO_LCD_Dispatcher(SSO_LCD_Dispatcher_T * const this)
{
    if(NULL == SSO_LCD_Dispatcher.vtbl)
    {
        Populate_CHash_Map_IPC_MID_SSO_LCD_Process(&SSO_LCD_Dispatcher,
                SSO_LCD_Process_Mailist,
                Num_Elems(SSO_LCD_Process_Mailist),
                NULL);

    }
    _clone(this, SSO_LCD_Dispatcher);
}
