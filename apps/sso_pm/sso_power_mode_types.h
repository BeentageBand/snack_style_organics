/*=====================================================================================*/
/**
 * snack_power_mode_types.h
 * author : puch
 * date : Oct 22 2015
 *
 * description : Any comments
 *
 */
/*=====================================================================================*/
#ifndef SNACK_POWER_MODE_TYPES_H_
#define SNACK_POWER_MODE_TYPES_H_
/*=====================================================================================*
 * Project Includes
 *=====================================================================================*/
#include "ipc_types.h"
#include "sso_power_mode_uset.h"
#include "std_reuse.h"
/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Define Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Type Declarations
 *=====================================================================================*/
#undef PMODE_SOURCE
#define PMODE_SOURCE(src, osc) src,

typedef enum
{
   POWER_MODE_SOURCES_TB
   SSO_PM_MAX_SOURCE
};
typedef uint8_t SSO_PM_Source_T;

typedef enum SSO_PM_STID
{
    SSO_PM_IDLE_STID, /* Board power (5V), Sensors, Data Logger) */
    SSO_PM_12VDC_ON_STID, /* Add +-12VDC, fan, drivers */
    SSO_PM_120AC_ON_STID, /* Inversor ON, heater */
    SSO_PM_SHUT_STID, /* Remove Board power (5V)*, manual power cycle */
    SSO_PM_MAX_STID
};

enum SSO_Power_Req_Type
{
	SSO_POWER_ACQUIRE_REQ,
	SSO_POWER_RELEASE_REQ
};

typedef struct SSO_PM_Handle_Req
{
    IPC_TID_T tid;
    uint8_t handle_id;
	struct
	{
		SSO_PM_Source_T req_type :2;
		SSO_PM_Source_T source :6;
	};
}SSO_PM_Handle_Req_T;
/*=====================================================================================* 
 * snack_power_mode_types.h
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
#endif /*SNACK_POWER_MODE_TYPES_H_*/
