#include "sso_hid_fsm.h"

static bool sso_hid_lcd_ready_guard(union State_Machine * const, union St_Machine_State * const);
static bool sso_hid_confirm_run_guard(union State_Machine * const, union St_Machine_State * const);
static bool sso_hid_settime_end_guard(union State_Machine * const, union St_Machine_State * const);
static bool sso_hid_times_up_guard(union State_Machine * const, union St_Machine_State * const);
static bool sso_hid_times_up_guard(union State_Machine * const, union St_Machine_State * const);
static void sso_hid_start_lcd(union State_Machine * const);
static void sso_hid_settime(union State_Machine * const);
static void sso_hid_dehyd_run(union State_Machine * const);
static void update_settime(union State_Machine * const);
static void sso_hid_select(union State_Machine * const);
static void sso_hid_update_timer(union State_Machine * const);
static void sso_hid_dehyd_stop(union State_Machine * const);
static void sso_hid_update_timer(union State_Machine * const);
static void sso_hid_dehyd_stop(union State_Machine * const);
static void sso_hid_idle(union State_Machine * const);

struct SSO_HID_FSM_Class _private SSO_HID_FSM_Class =
{
        {NULL, NULL}
};

bool sso_hid_lcd_ready_guard(union State_Machine * const st_m, union St_Machine_State * const state)
{
    union SSO_HID_FSM * const this = _cast(SSO_HID_FSM, st_m);
    Isnt_Nullptr(this, false);
    return this->is_lcd_ready;
}

bool sso_hid_confirm_run_guard(union State_Machine * const, union St_Machine_State * const)
{

}

bool sso_hid_settime_end_guard(union State_Machine * const, union St_Machine_State * const);
bool sso_hid_times_up_guard(union State_Machine * const, union St_Machine_State * const);
bool sso_hid_times_up_guard(union State_Machine * const, union St_Machine_State * const);
void sso_hid_start_lcd(union State_Machine * const);
void sso_hid_settime(union State_Machine * const);
void sso_hid_dehyd_run(union State_Machine * const);
void update_settime(union State_Machine * const);
void sso_hid_select(union State_Machine * const);
void sso_hid_update_timer(union State_Machine * const);
void sso_hid_dehyd_stop(union State_Machine * const);
void sso_hid_update_timer(union State_Machine * const);
void sso_hid_dehyd_stop(union State_Machine * const);
void sso_hid_idle(union State_Machine * const);
