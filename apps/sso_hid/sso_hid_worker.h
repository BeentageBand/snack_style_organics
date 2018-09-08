/*
 * sso_hid_worker.h
 *
 *  Created on: Sep 6, 2018
 *      Author: uids6144
 */

#ifndef SSO_HID_WORKER_H_
#define SSO_HID_WORKER_H_

#include "sso_hid_types.h"
#include "state_machine.h"
#include "worker.h"

typedef union SSO_HID_Worker
{
        union SSO_HID_Worker_Class _private * _private vtbl;
        struct Object Object;
        union Thread Thread;
        struct
        {
                union Worker Worker;
                union State_Machine _private * _private st_m;
        };
}SSO_HID_Worker_T;

typedef union SSO_HID_Worker_Class
{
        struct Class Class;
        struct Thread_Class Thread;
        union Worker_Class Worker;
}SSO_HID_Worker_Class_T;

extern SSO_HID_Worker_Class_T _private SSO_HID_Worker_Class;

extern void Populate_SSO_HID_Worker(union SSO_HID_Worker * const sso_hid);

#endif /* SSO_HID_WORKER_H_ */
