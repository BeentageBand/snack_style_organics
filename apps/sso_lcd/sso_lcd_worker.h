#ifndef SSO_LCD_WORKER_H_
#define SSO_LCD_WORKER_H_

#include "sso_lcd.h"
#include "worker.h"

typedef union SSO_LCD_Worker
{
        union SSO_LCD_Worker_Class _private * _private vtbl;
        struct Object Object;
        union Thread Thread;
        struct
        {
                union Worker Worker;
                union SSO_LCD * lcd;
        };
}SSO_LCD_Worker_T;

typedef union SSO_LCD_Worker_Class
{
        struct Class Class;
        struct Thread_Class Thread;
        union Worker_Class Worker;
}SSO_LCD_Worker_Class_T;

extern union SSO_LCD_Worker_Class _private SSO_LCD_Worker_Class;

extern void Populate_SSO_LCD_Worker(union SSO_LCD_Worker * const lcd);

#endif /*SSO_LCD_H_*/
