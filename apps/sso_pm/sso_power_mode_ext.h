/*=====================================================================================*/
/**
 * snack_power_mode_ext.h
 * author : puch
 * date : Oct 22 2015
 *
 * description : Any comments
 *
 */
/*=====================================================================================*/
#ifndef SSO_POWER_MODE_EXT_H_
#define SSO_POWER_MODE_EXT_H_
/*=====================================================================================*
 * Project Includes
 *=====================================================================================*/
#include "cobject.h"
#include "sso_power_mode_uset.h"
#include "sso_power_mode_types.h"
/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Define Macros
 *=====================================================================================*/
/*=====================================================================================* 
 * Exported Type Declarations
 *=====================================================================================*/
#ifdef __cplusplus
extern "C"{
#endif

typedef union SSO_PM_Source_Cbk
{
	struct SSO_PM_Source_Cbk_Class _private * _private vtbl;
	struct
	{
		struct Object Object;
		bool is_active;
		uint8_t handles;
	};
}SSO_PM_Source_Cbk_T;

typedef struct SSO_PM_Source_Cbk_Class
{
	struct Class Class;
	void (* _private subscribe)(union SSO_PM_Source_Cbk * const);
	void (* _private unsubscribe)(union SSO_PM_Source_Cbk * const);
	void (* _private init_source)(union SSO_PM_Source_Cbk * const);
	void (* _private shut_source)(union SSO_PM_Source_Cbk * const);
	void (* _private acquire_source)(union SSO_PM_Source_Cbk * const);
	void (* _private release_source)(union SSO_PM_Source_Cbk * const);
}SSO_PM_Source_Cbk_Class_T;
/*=====================================================================================*
 * Exported Object Declarations
 *=====================================================================================*/
extern SSO_PM_Source_Cbk_T _private SSO_PM_Source_Cbk_Class;
extern union SSO_PM_Source_Cbk SSO_PM_Source_Cbk[SSO_PM_MAX_SOURCE];
/*=====================================================================================* 
 * Exported Function Prototypes
 *=====================================================================================*/
/*=====================================================================================* 
 * Exported Function Like Macros
 *=====================================================================================*/
#ifdef __cplusplus
}
#endif
/*=====================================================================================* 
 * snack_power_mode_ext.h
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
#endif /*SSO_POWER_MODE_EXT_H_*/
