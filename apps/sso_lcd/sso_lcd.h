#ifndef SSO_LCD_H_
#define SSO_LCD_H_

#include "mail.h"

union SSO_LCD_Worker;
typedef union SSO_LCD
{
        struct SSO_LCD_Class _private * _private vtbl;
        struct
        {
                struct Object Object;
                union SSO_LCD _private * _private next;
                char const * _private fmt;
                uint32_t _private cursor;
        };
}SSO_LCD_T;

typedef struct SSO_LCD_Class
{
        struct Class Class;
        void (* _private append)(union SSO_LCD * const, union SSO_LCD * const);
        void (* _private update)(union SSO_LCD * const, union SSO_LCD_Worker * const);
        void (* _private print)(union SSO_LCD * const, ...);
}SSO_LCD_Class_T;

extern struct SSO_LCD_Class _private SSO_LCD_Class;

extern void Populate_SSO_LCD(union SSO_LCD * const lcd,
        char const * const fmt, uint32_t const cursor);

#endif /* SSO_LCD_H_ */
