#define OBJECT_IMPLEMENTATION

#include "sso_lcd_worker.h"

static void sso_lcd_worker_on_mail(union Worker * const super, union Mail * const mail);
static void sso_lcd_worker_on_start(union Worker * const super);
static void sso_lcd_worker_on_loop(union Worker * const super);


CLASS_DEF(SSO_LCD_Worker)

void SSO_LCD_Worker_Init(void)
{
   SSO_LCD.tid = SSO_LCD_TID;
}

void SSO_LCD_Worker_Delete(struct Object * const obj)
{
}

union SSO_LCD_Worker SSO_LCD_Worker(void)
{
}

union SSO_LCD_Worker SSO_LCD_Worker_New(void)
{
   Constructor_New_Impl(SSO_LCD_Worker, void);
}

void SSO_LCD_Worker_on_mail(union Worker * const super, union Mail * const mail)
{
}
void SSO_LCD_Worker_on_start(union Worker * const super)
{
}
void SSO_LCD_Worker_on_loop(union Worker * const super)
{
}
