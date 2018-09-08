#define COBJECT_IMPLEMENTATION
#define Dbg_FID SSO_HID_FID, 0
#include "dbg_log.h"
#include "ipc.h"
#include "sso_hid_process.h"
#include "sso_hid_worker.h"

static void sso_hid_worker_delete(struct Object * const obj);
static void sso_hid_worker_on_mail(union Worker * const super, union Mail * const mail);
static void sso_hid_worker_on_start(union Worker * const super);
static void sso_hid_worker_on_stop(union Worker * const super);
static void sso_hid_worker_on_loop(union Worker * const super);


static union SSO_HID_Worker SSO_HID_Worker = {NULL};
static union Mail SSO_HID_Mailbox_Buff[64] = {0};
static SSO_HID_Dispatcher_T SSO_HID_Dispatcher = {NULL};

union SSO_HID_Worker_Class SSO_HID_Worker_Class =
{
        {sso_hid_worker_delete, NULL}
};

void sso_hid_worker_delete(struct Object * const obj)
{
}

void sso_hid_worker_on_mail(union Worker * const super, union Mail * const mail)
{
    union SSO_HID_Worker * const this = _cast(SSO_HID_Worker, super);
    Isnt_Nullptr(this, );
    SSO_HID_Process_MID_T * found = SSO_HID_Dispatcher.vtbl->find(&SSO_HID_Dispatcher, mail->mid);
    if(found != SSO_HID_Dispatcher.CHash_Set_HID.vtbl->end(&SSO_HID_Dispatcher.CHash_Set_HID))
    {
        found->obj(this, mail);
    }
}

void sso_hid_worker_on_start(union Worker * const super)
{
}

void sso_hid_worker_on_stop(union Worker * const super)
{

}

void sso_hid_worker_on_loop(union Worker * const super)
{
    union SSO_HID_Worker * const this = _cast(SSO_HID_Worker, super);
    Isnt_Nullptr(this, );
    Dbg_Info("%s: is alive", __func__);

}

void Populate_SSO_HID_Worker(union SSO_HID_Worker * const this)
{
    if(NULL == SSO_HID_Worker.vtbl)
    {
        Populate_Worker(&SSO_HID_Worker.Worker,
                SSO_HID_WORKER_TID,
                SSO_HID_Mailbox_Buff,
                Num_Elems(SSO_HID_Mailbox_Buff));

        Object_Init(&SSO_HID_Worker.Object,
                &SSO_HID_Worker_Class.Class,
                sizeof(SSO_HID_Worker_Class.Worker));

        SSO_HID_Worker_Class.Worker.on_loop = sso_hid_worker_on_loop;
        SSO_HID_Worker_Class.Worker.on_start = sso_hid_worker_on_start;
        SSO_HID_Worker_Class.Worker.on_stop = sso_hid_worker_on_stop;
        SSO_HID_Worker_Class.Worker.on_mail = sso_hid_worker_on_mail;
        Populate_SSO_HID_Dispatcher(&SSO_HID_Dispatcher);
    }
    _clone(this, SSO_HID_Worker);
}

