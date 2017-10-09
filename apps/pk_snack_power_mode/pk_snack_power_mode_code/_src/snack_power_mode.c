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
#include "snack_power_mode.h"

#include "pwm.h"
#include "snack_power_mode_types.h"
#include "snack_power_mode_ext.h"
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
typedef struct
{
   void(*enter)(void);
   void(*exit)(void);
}Change_Of_State_T;

CLASS_DEF(SSO_PMode)
/*=====================================================================================* 
 * Local Object Definitions
 *=====================================================================================*/
#undef PMODE_STATE
#define PMODE_STATE(st) \
const Change_Of_State_T st##_State PROGMEM = \
{\
   pmode::Enter_##st, \
   pmode::Exit_##st   \
};\

POWER_MODE_STATES_TB

#undef PMODE_STATE
#define PMODE_STATE(st) \
&st##_State,\

const Change_Of_State_T * const PMode_SM[] PROGMEM =
{
   POWER_MODE_STATES_TB
};

static PMode_State_T Current_State = 0;
static PMode_State_T New_State = 0;
/*=====================================================================================* 
 * Exported Object Definitions
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Prototypes
 *=====================================================================================*/
#undef PMODE_SOURCE
#define PMODE_SOURCE(src, osc) \
   src##_init();

void pmode::Init(void)
{
   POWER_MODE_SOURCES_TB
}
void pmode::Main(void)
{
   if(New_State != Current_State)
   {
      const Change_Of_State_T * sm = reinterpret_cast<const Change_Of_State_T *>( pgm_read_ptr(PMode_SM + Current_State) );
      void (*handler)(void) = reinterpret_cast< void (*)(void)>(pgm_read_ptr(&sm->exit));
      handler();

      sm = reinterpret_cast<const Change_Of_State_T *>( pgm_read_ptr(PMode_SM + New_State) );
      handler = reinterpret_cast< void (*)(void)>(pgm_read_ptr(&sm->enter) );
      handler();

      Current_State = New_State;
   }
}

void pmode::Set_State(PMode_State_T state)
{
   if(New_State < PMODE_MAX_STATES)
   {
      New_State = state;
   }
}

PMode_State_T pmode::Get_State(void)
{
   return Current_State;
}
void pmode::Shut(void)
{
   pmode::Set_State(PMODE_ALL_OFF_STATE);
}
/*=====================================================================================* 
 * Local Inline-Function Like Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Definitions
 *=====================================================================================*/
void SSO_PMode_Init(void)
{
}

void SSO_PMode_Delete(struct Object * const obj)
{}

union SSO_PMode SSO_PMode_Default(void)
{
	union SSO_PMode sso_pmode;
	if(!SSO_PMode_Class)
	{
		SSO_PMode_Init();
		SSO_PMode_Obj.vbtl = &SSO_PMode_Class;
	}
	return sso_pmode;
}

/*=====================================================================================* 
 * Exported Function Definitions
 *=====================================================================================*/
union SSO_PMode SSO_PMode(void)
{
	union SSO_PMode this = SSO_PMode_Default();

	return this;
}
union SSO_PMode * SSO_PMode_New(void)
{
	union SSO_PMode * const _new = malloc(sizeof(SSO_PMode_Default()));
	Isnt_Nullptr(_new, NULL);

	memcpy(_new, &SSO_PMode_Obj, sizeof(SSO_PMode_Obj));
	return _new;
}

void SSO_PMode_set_state(union SSO_PMode * const this, PMode_State_T const state)
{
   if(this->current_state < PMODE_MAX_STATES)
   {
	   this->hsm->vtbl->dispatch(&this->hsm, state, NULL);
   }
}

PMode_State_T SSO_PMode_get_state(union SSO_PMode * const this)
{
   return this->hsm->vtbl->state;
}

void pmode::Shut(void)
{
   pmode::Set_State(PMODE_ALL_OFF_STATE);
}
/*=====================================================================================* 
 * snack_power_mode.cpp
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
