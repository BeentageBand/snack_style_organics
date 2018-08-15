#ifndef SSO_DEHYD_TYPES_H_
#define SSO_DEHYD_TYPES_H_

#include "std_reuse.h"

#ifdef __cplusplus
extern "C" {
#endif

enum SSO_DEHYD_STID
{
    SSO_DEHYD_IDLE_STID,
    SSO_DEHYD_READY_STID,
    SSO_DEHYD_DARK_STBY_STID,
    SSO_DEHYD_SUNLIGHT_STBY_STID,
    SSO_DEHYD_DARK_OP_STID,
    SSO_DEHYD_SUNLIGHT_OP_STID,
    SSO_DEHYD_MAX_STID
};

#ifdef __cplusplus
}
#endif
#endif /*SSO_DEHYD_TYPES_H_*/