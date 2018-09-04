/*=====================================================================================*/
/**
 * snack_power_mode.c
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
static void sso_pm_delete(struct Object * const obj);
static void sso_pm_acquire(union SSO_PM * const this);
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
    sso_pm_acquire,
    sso_pm_release
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
    if(this->vtbl->is_active(this))
    {
        this->vtbl->release(this);
    }
    memset(this, 0, sizeof(SSO_PM));
}

void sso_pm_acquire(union SSO_PM * const this)
{
   SSO_PM_Handle_Req_T pm_req = 
   {
      IPC_Self(),
      this->handle_id,
      { SSO_POWER_ACQUIRE_REQ, this->source}
   };

   IPC_Send(SSO_PM_WORKER_TID, SSO_PM_INT_POWER_ACQUIRE_REQ_MID, &pm_req, sizeof(pm_req));
    sso_pm_get_handle_id(this);
}

void sso_pm_release(union SSO_PM * const this)
{
   SSO_PM_Handle_Req_T pm_req = 
   {
      IPC_Self(),
      this->handle_id,
      { SSO_POWER_RELEASE_REQ, this->source}
   };

   IPC_Send(SSO_PM_WORKER_TID, SSO_PM_INT_POWER_RELEASE_REQ_MID, &pm_req, sizeof(pm_req));
    sso_pm_get_handle_id(this);
}
void sso_pm_get_handle_id(union SSO_PM * const this)
{
    union Mail mail = {NULL};
    IPC_TID_T mid = SSO_PM_INT_POWER_REQUEST_RES_MID;
    if(IPC_Retrieve_From_Mailist(&mail, IPC_TIMEOUT_MS, &mid, 1UL))
    {
        SSO_PM_Handle_Req_T handle = *(SSO_PM_Handle_Req_T * const) mail.payload;
        if(handle.source == this->source)
        {
            //TODO WTF? this->handle_id = this->handle_id;
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
    IPC_Send(SSO_PM_WORKER_TID, SSO_PM_INT_REL_ALL_MID, NULL, 0);
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
