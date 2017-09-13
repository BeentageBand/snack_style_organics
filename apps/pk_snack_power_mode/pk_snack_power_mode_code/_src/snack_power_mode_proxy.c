/*=====================================================================================*/
/**
 * snack_power_mode.cpp
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
#include "snack_power_mode_proxy.h"
#include "snack_power_mode_types.h"
#include "snack_power_mode_ext.h"
#include "ipc.h"
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
CLASS_DEF(SSO_PMode_Proxy)
/*=====================================================================================* 
 * Local Object Definitions
 *=====================================================================================*/
static struct Mail_Node_Subcription_Handler SSO_PMode_Mail_Handle[] =
{
	SSO_PMODE_PROC_MESSAGE_LIST(MAIL_NODE_POPULATE)
};
/*=====================================================================================* 
 * Exported Object Definitions
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Prototypes
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Inline-Function Like Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Definitions
 *=====================================================================================*/
void SSO_PMode_Proxy_Init(void)
{

}
union SSO_PMode SSO_PMode(void)
{
	union Mail_Node super = Mail_Node_Subscription(SSO_PMODE_TID, SSO_PMode_Mail_Handle, Num_Elems(SSO_PMode_Mail_Handle));
}
union SSO_PMode * SSO_PMode_New(void)
{
	return NULL;
}
/*=====================================================================================* 
 * Exported Function Definitions
 *=====================================================================================*/
void SSO_PMode_set_state(union SSO_PMode * const this, PMode_State_T const state)
{
	if(state < PMODE_MAX_STATES)
	{
		IPC_Send(SSO_PMODE_INT_CHANGE_STATE, SSO_PMODE_TID, &state, sizeof(state));
	}
}

PMode_State_T SSO_PMode_get_state(union SSO_PMode * const this)
{
	union SSO_PMode_Proxy * const this = _dynamic_cast(SSO_PMode_Proxy, super);
	return this->current_state;
}

void SSO_PMode_Proxy_SSO_PMode_On_State_Change(union SSO_PMode * const super, union Mail * const mail)
{
	union SSO_PMode_Proxy * const this = _dynamic_cast(SSO_PMode_Proxy, super);
	Isnt_Nullptr(this,);
	Isnt_Nullptr(mail,);
	Isnt_Nullptr(mail->data,);
	this->current_state = *(PMode_State_T * const) mail->data;
}
/*=====================================================================================* 
 * snack_power_mode.cpp
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
