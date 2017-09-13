/*=====================================================================================*/
/**
 * snack_power_mode.h
 * author : puch
 * date : Oct 22 2015
 *
 * description : Any comments
 *
 */
/*=====================================================================================*/
#ifndef SNACK_POWER_MODE_H_
#define SNACK_POWER_MODE_H_
/*=====================================================================================*
 * Project Includes
 *=====================================================================================*/
#include "st_machine.h"
#include "snack_power_mode_types.h"
/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported X-Macros
 *=====================================================================================*/

/*=====================================================================================*
 * Exported Define Macros
 *=====================================================================================*/
#define SSO_PMode_INHERITS BASE_CLASS

#define SSO_PMode_MEMBERS(_member, _class) \
	_member(union State_Machine _private, hsm)

#define SSO_PMode_METHODS(_method, _class) \
_method(void, _class, set_state, PMode_State_T const) \
_method(PMode_State_T, _class, get_state, void)

/*=====================================================================================* 
 * Exported Type Declarations
 *=====================================================================================*/
#ifdef __cplusplus
extern "C"
{
#endif
/*=====================================================================================* 
 * Exported Object Declarations
 *=====================================================================================*/
CLASS_DECL(SSO_PMode)
/*=====================================================================================* 
 * Exported Function Prototypes
 *=====================================================================================*/
extern union SSO_PMode SSO_PMode(void);
extern union SSO_PMode * SSO_PMode_New(void);
/*=====================================================================================* 
 * Exported Function Like Macros
 *=====================================================================================*/
#ifdef __cplusplus
}/*extern "C"*/
#endif
/*=====================================================================================* 
 * snack_power_mode.h
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
#endif /*SNACK_POWER_MODE_H_*/
