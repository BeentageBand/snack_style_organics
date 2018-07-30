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
#ifdef SSO_PM_ENABLE
#include "pwm.h"
#endif
#include "ipc.h"
#include "sso_power_mode.h"
#include "sso_power_mode_ext.h"
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
static void sso_pm_init(void);
static void sso_pm_delete(struct Object * const obj);
static void sso_pm_request(union SSO_PM * const this);
static void sso_pm_release(union SSO_PM * const this);
static void sso_pm_get_handle_id(union SSO_PM * const this);
static bool sso_pm_is_active(union SSO_PM * const this);
/*=====================================================================================* 
 * Local Object Definitions
 *=====================================================================================*/
#undef PMODE_STATE
#define PMODE_STATE(st) \
const Change_Of_State_T st##_State PROGMEM = \
{\
   pmode::Enter_##st, \
   pmode::Exit_##st   \
};\


static union SSO_PM SSO_PM = {NULL};
struct SSO_PM_Class SSO_PM_Class =
{
    {sso_pm_delete, NULL},
    sso_pm_release,
    sso_pm_request
};
/*=====================================================================================* 
 * Exported Object Definitions
 *=====================================================================================*/
/*=====================================================================================* 
 * Local Function Prototypes
 *=====================================================================================*/
#undef PMODE_SOURCE
#define PMODE_SOURCE(src, osc) \
   src##_init();

#ifdef SSO_PM_ENABLE
void pmode::Init(void)
{
   POWER_MODE_SOURCES_TB
}
#endif

/*=====================================================================================* 
 * Local Inline-Function Like Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Definitions
 *=====================================================================================*/

void sso_pm_delete(struct Object * const obj)
{
    union SSO_PM * const this = (union SSO_PM *)Object_Cast(&SSO_PM_Class.Class, obj);
    Isnt_Nullptr(this,);
    if(this->is_active)
    {
        this->vtbl->sso_pm_release(this);
    }
    memset(this, 0, sizeof(SSO_PM));
}

void sso_pm_request(union SSO_PM * const this)
{
    switch(this->source)
    {
        case SSO_PM_12VDC_SOURCE:
        {
            IPC_Send(SSO_PM_TID, SSO_PM_INT_12VDC_REQ_MID, this->handle_id, sizeof(this->handle_id));
            break;
        }
        case SSO_PM_120AC_SOURCE:
        {
            IPC_Send(SSO_PM_TID, SSO_PM_INT_120AC_REQ_MID, this->handle_id, sizeof(this->handle_id));
            break;
        }
        default : 
        {
            Dbg_Warn("%s: tid %d has invalid source %d",
                    __func__,
                    IPC_Self(),
                    this->source);
                    return;
        }
    }
    sso_pm_get_handle_id(this);
}

void sso_pm_release(union SSO_PM * const this)
{
    switch(this->source)
    {
        case SSO_PM_12VDC_SOURCE: IPC_Send(SSO_PM_TID, SSO_PM_12VDC_REL_MID, this->handle_id, sizeof(this->handle_id)); break;
        case SSO_PM_120AC_SOURCE: IPC_Send(SSO_PM_TID, SSO_PM_120AC_REL_MID, this->handle_id, sizeof(this->handle_id)); break;
        default : 
        {
            Dbg_Warn("%s: tid %d has invalid source %d",
                    __func__,
                    IPC_Self(),
                    this->source);
                    return;
        }
    }
    sso_pm_get_handle_id(this);
}
void sso_pm_get_handle_id(union SSO_PM * const this)
{
    union Mail mail = {NULL};
    IPC_TID_T mid = SSO_PM_INT_SOURCE_RESP_MID;
    if(IPC_Retrieve_From_Mailist(&mid, 1, &mail, IPC_TIMEOUT_MS))
    {
        SSO_PM_Handle_Req_T handle = *(SSO_PM_Handle_Req_T * const) mail.payload;
        if(handle->source == this->source)
        {
            this->handle_id = this->handle_id;
        }
    }

}

bool sso_pm_is_active(union SSO_PM * const this)
{
    return 0 < this->handle_id;
}
/*=====================================================================================* 
 * Exported Function Definitions
 *=====================================================================================*/
void Populate_SSO_PM(union SSO_PM * const this, SSO_PM_Source_T const source)
{
    if(NULL == SSO_PM.vtbl)
    {
        SSO_PM.vtbl = &SSO_PM_Class;
        SSO_PM.handle_id = 0;
        SSO_PM.source = 0;
    }
    SSO_PM.source = source;
    memcpy(this, &SSO_PM, sizeof(SSO_PM));
}

void SSO_PM_Release_All(void)
{
    IPC_Send(SSO_PM_TID, SSO_PM_INT_REL_ALL_MID, NULL, 0);
}

#ifdef SSO_PM_ENABLE
void pmode::Shut(void)
{
   pmode::Set_State(PMODE_ALL_OFF_STATE);
}
#endif
/*=====================================================================================* 
 * snack_power_mode.cpp
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/