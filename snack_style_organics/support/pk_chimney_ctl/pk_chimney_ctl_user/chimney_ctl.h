/*=====================================================================================*/
/**
 * chimney_ctl.h
 * author : puch
 * date : Oct 22 2015
 *
 * description : Any comments
 *
 */
/*=====================================================================================*/
#ifndef CHIMNEY_CTL_H_
#define CHIMNEY_CTL_H_
/*=====================================================================================*
 * Project Includes
 *=====================================================================================*/
#include "chimney_ctl_types.h"
/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported X-Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Define Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Type Declarations
 *=====================================================================================*/
namespace chim{
/*=====================================================================================* 
 * Exported Object Declarations
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Function Prototypes
 *=====================================================================================*/
extern void Init(void);
extern void Set_State(Chimney_State_T state);
extern Chimney_State_T Get_State(void);
extern void Shut(void);
/*=====================================================================================* 
 * Exported Function Like Macros
 *=====================================================================================*/
} /*namespace chim*/
/*=====================================================================================* 
 * chimney_ctl.h
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
#endif /*CHIMNEY_CTL_H_*/
