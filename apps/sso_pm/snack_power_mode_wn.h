/*=====================================================================================*/
/**
 * snack_power_mode_wn.h
 * author : puch
 * date : Oct 22 2015
 *
 * description : Any comments
 *
 */
/*=====================================================================================*/
#ifndef SNACK_POWER_MODE_WN_H_
#define SNACK_POWER_MODE_WN_H_
/*=====================================================================================*
 * Project Includes
 *=====================================================================================*/
#include "snack_power_mode_uset.h"
#include "snack_power_mode_types.h"
#include "worker.h"
/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Define Macros
 *=====================================================================================*/
#define SSO_PMode_WN_INHERITS Worker_Node
#define SSO_PMode_WN_MEMBERS(_member, _class) \

#define SSO_PMode_WN_METHODS(_method, _class) \

#ifdef __cplusplus
extern "C"
{
#endif
/*=====================================================================================* 
 * Exported Type Declarations
 *=====================================================================================*/
typedef union Worker_Class SSO_PM_Worker_Class_T;

typedef union SSO_PM_Worker
{
    SSO_PM_Worker_Class_T _private * private vtbl;
    union Worker Worker;
    struct Object Object;
}SSO_PM_Worker_T;
/*=====================================================================================*
 * Exported Object Declarations
 *=====================================================================================*/
extern SSO_PM_Worker_Class_T _private SSO_PM_Worker_Class;
/*=====================================================================================* 
 * Exported Function Prototypes
 *=====================================================================================*/
#undef PMODE_SOURCE
#define PMODE_SOURCE(src, osc) \
   extern void src##_init(void);

POWER_MODE_SOURCES_TB

#undef PMODE_STATE
#define PMODE_STATE(st) \
   extern void Enter_##st(void); \
   extern void Exit_##st(void);  \

POWER_MODE_STATES_TB

extern void Populate_SSO_PM_Worker(union SSO_PM_Worker * const sso_pm_worker);

#ifdef __cplusplus
}
#endif/*extern "C"*/
/*=====================================================================================* 
 * Exported Function Like Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * snack_power_mode_wn.h
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
#endif /*SNACK_POWER_MODE_WN_H_*/
