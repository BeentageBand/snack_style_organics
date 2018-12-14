/*==========NA===========================================================================*/
/**
 * chimney_ctl.cpp
 * author : puch
 * date : Oct 22 2015
 *
 * description : Any comments
 *
 */
/*=====================================================================================*/
#define COBJECT_IMPLEMENTATION
/*=====================================================================================*
 * Project Includes
 *=====================================================================================*/
/*
#include "dio.h"
*/
#include "chimney_ctl.h"
#include "mutex.h"
/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/

/*=====================================================================================* 
 * Local X-Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Define Macros
 *=====================================================================================*/
#define CHIMNEY_LOCK_MS (2000)
/*=====================================================================================* 
 * Local Type Definitions
 *=====================================================================================*/
static void chimney_ctl_delete(struct Object * const obj);
static void chimney_ctl_set(union Chimney_Ctl * const this, Chimney_Clearance_Millis_T const clearance);
static uint16_t chimney_ctl_make_pulse(Chimney_Clearance_Millis_T const clearance);
/*=====================================================================================* 
 * Local Object Definitions
 *=====================================================================================*/
static union Chimney_Ctl Chimney_Ctl = {NULL};
static Chimney_Clearance_Millis_T Chimney_Clearance_Milis = 0;
static union Mutex Chimney_Lock = {NULL};
/*=====================================================================================* 
 * Exported Object Definitions
 *=====================================================================================*/
struct Chimney_Ctl_Class Chimney_Ctl_Class =
{
        {chimney_ctl_delete, NULL},
        chimney_ctl_set
};
/*=====================================================================================* 
 * Local Function Prototypes
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Inline-Function Like Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Definitions
 *=====================================================================================*/
void chimney_ctl_delete(struct Object * const obj)
{
}

void chimney_ctl_set(union Chimney_Ctl * const this, Chimney_Clearance_Millis_T const clearance)
{
    if(!Chimney_Lock.vtbl->lock(&Chimney_Lock, CHIMNEY_LOCK_MS)) return;
    *this->clearance = clearance;
    uint16_t pulse = chimney_ctl_make_pulse(clearance);

    Chimney_Lock.vtbl->unlock(&Chimney_Lock);
}
uint16_t chimney_ctl_make_pulse(Chimney_Clearance_Millis_T const clearance)
{
    uint16_t pulse;
    //According to drive spec.
    pulse = clearance;//TODO conversion
    return pulse;
}
/*=====================================================================================* 
 * Exported Function Definitions
 *=====================================================================================*/
void Populate_Chimney_Ctl(union Chimney_Ctl * const this)
{
    if(NULL == Chimney_Ctl.vtbl)
    {
        Chimney_Ctl.vtbl = &Chimney_Ctl_Class;
        Chimney_Ctl.clearance = &Chimney_Clearance_Milis;
        Populate_Mutex(&Chimney_Lock);
    }
    _clone(this, Chimney_Ctl);
}
/*=====================================================================================* 
 * chimney_ctl.cpp
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
