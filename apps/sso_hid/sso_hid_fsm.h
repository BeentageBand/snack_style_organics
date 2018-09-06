/*
 * sso_hid_fsm.h
 *
 *  Created on: Sep 5, 2018
 *      Author: uids6144
 */

#ifndef SSO_HID_FSM_H_
#define SSO_HID_FSM_H_

#include "fsm.h"

#define SSO_DEHYD_FSM_DEF(cb) \
FSM_STATE_DEF(cb, SSO_HID_IDLE, \
     FSM_TRANSITION_DEF(cb, SSO_HID_INT_LP_START_MID,     SSO_HID_STBY_STID,          sso_hid_lcd_ready_guard,   sso_hid_start_lcd) \
FSM_STATE_DEF(cb, SSO_HID_STBY_STID, \
     FSM_TRANSITION_DEF(cb, SSO_HID_INT_LP_SELECT_MID,    SSO_HID_SETTIME_STID,       NULL,                      sso_hid_settime) \
     FSM_TRANSITION_DEF(cb, SSO_HID_INT_LP_START_MID,     SSO_HID_DEHYD_RUNNING_STID, sso_hid_confirm_run_guard, sso_hid_dehyd_run) \
FSM_STATE_DEF(cb, SSO_HID_SETTIME_STID, \
     FSM_TRANSITION_DEF(cb, SSO_HID_INT_SP_SELECT_MID,    SSO_HID_SETTIME_STID,       NULL,                      sso_hid_update_settime) \
     FSM_TRANSITION_DEF(cb, SSO_HID_INT_SP_START_MID,     SSO_HID_STBY_STID,          sso_hid_settime_end_guard, sso_hid_select) \
FSM_STATE_DEF(cb, SSO_HID_DEHYD_RUNNING_STID, \
     FSM_TRANSITION_DEF(cb, SSO_HID_INT_TIMER_UPDATE_MID, SSO_HID_DEHYD_RUNNING_STID, NULL,                      sso_hid_update_timer) \
     FSM_TRANSITION_DEF(cb, SSO_HID_INT_TIMEOUT_MID,      SSO_HID_DEHYD_STOP_STID,    sso_hid_times_up_guard,    sso_hid_dehyd_stop) \
FSM_STATE_DEF(cb, SSO_HID_DEHYD_STOP_STID, \
     FSM_TRANSITION_DEF(cb, SSO_HID_INT_SP_SELECT_MID,    SSO_HID_DEHYD_RUNNING_STID, NULL,                      sso_hid_update_timer) \
     FSM_TRANSITION_DEF(cb, SSO_HID_INT_LP_SELECT_MID,    SSO_HID_DEHYD_STOP_STID,    sso_hid_times_up_guard,    sso_hid_dehyd_stop) \
     FSM_TRANSITION_DEF(cb, SSO_HID_INT_SP_START_MID,     SSO_HID_DEHYD_STBY_STID,    NULL,                      sso_hid_idle) \
     FSM_TRANSITION_DEF(cb, SSO_HID_INT_LP_START_MID,     SSO_HID_DEHYD_STBY_STID,    NULL,                      sso_hid_idle) \

typedef union SSO_HID_FSM
{
        union SSO_HID_FSM_Class _private * _private vtbl;
        struct
        {
                struct Object Object;
                bool is_lcd_ready;
        };
}SSO_HID_FSM_T;


typedef union SSO_HID_FSM_Class
{
        struct Class Class;
        struct State_Machine_Class State_Machine;
        union FSM_Class FSM;
}SSO_HID_FSM_Class_T;

extern struct SSO_HID_FSM_Class _private SSO_HID_FSM_Class;
#endif /* SSO_HID_FSM_H_ */
