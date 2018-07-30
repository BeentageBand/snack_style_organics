/*=====================================================================================*/
/**
 * snack_power_mode_uset.h
 * author : puch
 * date : Oct 22 2015
 *
 * description : Any comments
 *
 */
/*=====================================================================================*/
#ifndef SNACK_POWER_MODE_USET_H_
#define SNACK_POWER_MODE_USET_H_
/*=====================================================================================*
 * Project Includes
 *=====================================================================================*/

/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported X-Macros
 *=====================================================================================*/
#define POWER_MODE_SOURCES_TB \
   /*            CHANNEL,               OSC VALUE */ \
   PMODE_SOURCE(SSO_PM_120AC_SOURCE,        60       ) \
   PMODE_SOURCE(SSO_PM_12VDC_SOURCE,    1000     ) \

#define SSO_PM_SUBSCRIPTION_MAILIST(X)
/*=====================================================================================* 
 * Exported Define Macros
 *=====================================================================================*/
#define SSO_PM_SOURCE_REQ_SIZE (64)
/*=====================================================================================* 
 * Exported Type Declarations
 *=====================================================================================*/

/*=====================================================================================* 
 * snack_power_mode_uset.h
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
#endif /*SNACK_POWER_MODE_USET_H_*/
