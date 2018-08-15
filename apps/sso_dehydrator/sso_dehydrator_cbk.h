#ifndef SSO_DEHYDRATOR_CBK_H_
#define SSO_DEHYDRATOR_CBK_H_

#ifdef __cplusplus
extern "C"{
#endif

typedef union SSO_Dehyd_Cbk
{
    struct SSO_Dehyd_Cbk_Class _private * _private vtbl;
    struct Object Object;
}SSO_Dehyd_Cbk_T;

typedef struct SSO_Dehyd_Cbk_Class
{
    struct Class Class;
    union PID_Driver * (* _private get_driver)(union SSO_Dehyd_Cbk * const, PID_Channel_T const);
    struct PID_Laws (* _private get_laws)(union SSO_Dehyd_Cbk * const, PID_Channel_T const);
}SSO_Dehyd_Cbk_Class_T;

extern struct SSO_Dehyd_Cbk_Class _private SSO_Dehyd_Cbk_Class;

extern void Populate_SSO_Dehyd_Cbk(union SSO_Dehyd_Cbk * const cbk);

#ifdef __cplusplus
}
#endif
#endif /*SSO_DEHYDRATOR_CBK_H_*/