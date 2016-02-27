/*=====================================================================================*/
/**
 * arduino_fwk_ext.h
 * author : puch
 * date : Oct 22 2015
 *
 * description : Any comments
 *
 */
/*=====================================================================================*/

/*=====================================================================================*
 * Project Includes
 *=====================================================================================*/
#include "pid_ctl_types.h"
#include "pid_ctl_uset.h"
/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Define Macros
 *=====================================================================================*/
#define PID_CTL_FIX32_PARSE_FACTOR  (10000000UL)
/*=====================================================================================* 
 * Exported Type Declarations
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Object Declarations
 *=====================================================================================*/
namespace pid{
#undef PID_CTL_CHANNEL
#define PID_CTL_CHANNEL(ch) \
   extern void Put_##ch(const Fix32_T uout); \
   extern Fix32_T Get_##ch(void); \

PID_CTL_CHANNELS_TABLE
}
/*=====================================================================================* 
 * Exported Function Prototypes
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Function Like Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * arduino_fwk_ext.h
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/


