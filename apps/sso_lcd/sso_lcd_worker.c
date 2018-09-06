#define COBJECT_IMPLEMENTATION
#define Dbg_FID SSO_LCD_FID, 0
#include "dbg_log.h"
#include "ipc.h"
#include "sso_lcd.h"
#include "sso_lcd_process.h"
#include "sso_lcd_worker.h"

static void sso_lcd_worker_delete(struct Object * const obj);
static void sso_lcd_worker_on_mail(union Worker * const super, union Mail * const mail);
static void sso_lcd_worker_on_start(union Worker * const super);
static void sso_lcd_worker_on_stop(union Worker * const super);
static void sso_lcd_worker_on_loop(union Worker * const super);


static union SSO_LCD_Worker SSO_LCD_Worker = {NULL};
static union Mail SSO_LCD_Mailbox_Buff[64] = {0};
static SSO_LCD_Dispatcher_T SSO_LCD_Dispatcher = {NULL};

union SSO_LCD_Worker_Class SSO_LCD_Worker_Class =
{
        {sso_lcd_worker_delete, NULL}
};

void sso_lcd_worker_delete(struct Object * const obj)
{
}

void SSO_LCD_Worker_on_mail(union Worker * const super, union Mail * const mail)
{
    union SSO_LCD_Worker * const this = _cast(SSO_LCD_Worker, super);
    Isnt_Nullptr(this, );
    SSO_LCD_Process_MID_T * found = SSO_LCD_Dispatcher.vtbl->find(&SSO_LCD_Dispatcher, mail->mid);
    if(found != SSO_LCD_Dispatcher.CHash_Set_LCD.vtbl->end(&SSO_LCD_Dispatcher.CHash_Set_LCD))
    {
        found->obj(this, mail);
    }
}

void SSO_LCD_Worker_on_start(union Worker * const super)
{
}

void sso_lcd_worker_on_stop(union Worker * const super)
{

}

void SSO_LCD_Worker_on_loop(union Worker * const super)
{
    union SSO_LCD_Worker * const this = _cast(SSO_LCD_Worker, super);
    Isnt_Nullptr(this, );
    this->lcd->vtbl->update(this->lcd, this);
    Dbg_Info("%s: is alive", __func__);

}

void Populate_SSO_LCD_Worker(union SSO_LCD_Worker * const this)
{
    if(NULL == SSO_LCD_Worker.vtbl)
    {
        Populate_Worker(&SSO_LCD_Worker.Worker,
                SSO_LCD_WORKER_TID,
                SSO_LCD_Mailbox_Buff,
                Num_Elems(SSO_LCD_Mailbox_Buff));
        Populate_SSO_LCD_Dispatcher(&SSO_LCD_Dispatcher);
    }
    _clone(this, SSO_LCD_Worker);
}
