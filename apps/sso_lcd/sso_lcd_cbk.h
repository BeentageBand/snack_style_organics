#ifndef SSO_LCD_CBK_H_
#define SSO_LCD_CBK_H_
#include "sso_lcd_worker.h"

typedef union SSO_LCD_Cbk
{
        struct SSO_LCD_Cbk_Class _private * _private vtbl;
        struct
        {
                struct Object Object;
                FILE * _private stream;
        };
}SSO_LCD_Cbk_T;

typedef struct SSO_LCD_Cbk_Class
{
        struct Class Class;
}SSO_LCD_Cbk_Class_T;

extern struct SSO_LCD_Cbk_Class _private SSO_LCD_Cbk_Class;

extern void Populate_SSO_LCD_Cbk(union SSO_LCD_Cbk * const cbk);

#endif /* SSO_LCD_CBK_H_ */
