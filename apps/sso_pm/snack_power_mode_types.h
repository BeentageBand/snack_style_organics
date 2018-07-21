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
#include "snack_power_mode_uset.h"
#include "std_reusehine.h"
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
   PMODE_SOURCE_MAX
}PMODE_SOURCES_T;

typedef uint8_t PMode_Sources_T;

typedef enum
{
   PMODE_ALL_OFF_STID, /*No source is on*/             
   PMODE_AC_OFF_STID , /*Just Neg DC is on*/           
   PMODE_ALL_ON_STID , /*AC and Neg DC sources are on*/
   PMODE_MAX_STID
}PMODE_STATE_T;

typedef uint8_t PMode_State_T;
/*=====================================================================================* 
 * snack_power_mode_types.h
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
#endif /*SNACK_POWER_MODE_TYPES_H_*/
