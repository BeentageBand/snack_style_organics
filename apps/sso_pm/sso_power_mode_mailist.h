/*=====================================================================================*/
/**
 * snack_power_mode_evs.h
 * author : puch
 * date : Oct 22 2015
 *
 * description : Any comments
 *
 */
/*=====================================================================================*/
#ifndef SSO_POWER_MODE_EVS_H_
#define SSO_POWER_MODE_EVS_H_
/*=====================================================================================*
 * Project Includes
 *=====================================================================================*/

/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported X-Macros
 *=====================================================================================*/
#define SSO_PM_INT_MAILIST(X) \
X(SSO_PM_INT_REL_ALL_MID,           "Release all handles from all sources") \
X(SSO_PM_INT_POWER_ACQUIRE_REQ_MID, "Source Power Acquire Request") \
X(SSO_PM_INT_POWER_RELEASE_REQ_MID, "Source Power Release Request") \
X(SSO_PM_INT_12VDC_INIT_MID,        "Source Init") \
X(SSO_PM_INT_12VDC_SHUT_MID,        "Source Shutdown") \
X(SSO_PM_INT_120AC_INIT_MID,        "Source Init") \
X(SSO_PM_INT_120AC_SHUT_MID,        "Source Shutdown") \
X(SSO_PM_INT_POWER_REQUEST_RES_MID, "Power Request Response") \
X(SSO_PM_INT_SHUTDOWN_MID,          "Shutdown sequence start") \

#define SSO_PM_PBC_MAILIST(X) \
X(SSO_PM_PBC_FORCE_RELEASE_REQ_MID, "Request to release")
/*=====================================================================================* 
 * Exported Define Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Type Declarations
 *=====================================================================================*/

/*=====================================================================================* 
 * snack_power_mode_evs.h
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
#endif /*SNACK_POWER_MODE_EVS_H_*/
