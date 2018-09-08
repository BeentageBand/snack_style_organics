#define COBJECT_IMPLEMENTATION
#define Dbg_FID SSO_LCD_FID,0
#include <stdarg.h>
#include "sso_lcd_cbk.h"
#include "sso_lcd_worker.h"

static void sso_lcd_delete(struct Object * const obj);
static void sso_lcd_append(union SSO_LCD * const this, union SSO_LCD * const lcd);
static void sso_lcd_update(union SSO_LCD * const this, union SSO_LCD_Worker * const mail);
static void sso_lcd_print(union SSO_LCD * const this, ...);

static union SSO_LCD SSO_LCD = {NULL};

struct SSO_LCD_Class SSO_LCD_Class =
{
        {sso_lcd_delete, NULL},
        sso_lcd_append,
        sso_lcd_update,
        sso_lcd_print
};

static union SSO_LCD_Cbk SSO_LCD_Cbk = {NULL};

void sso_lcd_delete(struct Object * const obj){}

void sso_lcd_print(union SSO_LCD * const this, ...)
{
    FILE * stream = SSO_LCD_Cbk.stream;
    Isnt_Nullptr(stream, );
    va_list stack;
    va_start(stack, this);
    vfprintf(stream, this->fmt, stack);
    va_end(stack);
}

void sso_lcd_update(union SSO_LCD * const this, union SSO_LCD_Worker * const worker)
{
    union SSO_LCD * head = this->next;
    while(NULL != head)
    {
        head->vtbl->update(head, worker);
        sso_lcd_print(head);
        head = head->next;
    }
}

void sso_lcd_append(union SSO_LCD * const this, union SSO_LCD * const lcd)
{
    union SSO_LCD * head = this;
    while(NULL != head->next)
    {
        if(head == lcd)
            return;
        head = head->next;
    }
    head->next = lcd;

}

void Populate_SSO_LCD(union SSO_LCD * const this,
        char const * const fmt, uint32_t const cursor)
{
    if(NULL == SSO_LCD.vtbl)
    {
        SSO_LCD.vtbl = &SSO_LCD_Class;
        SSO_LCD.next = NULL;
        SSO_LCD.fmt = "";
        SSO_LCD.cursor = 0;
        Populate_SSO_LCD_Cbk(&SSO_LCD_Cbk);
    }
    _clone(this, SSO_LCD);
}
