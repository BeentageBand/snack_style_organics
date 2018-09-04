#ifndef IPC_MAIL_LIST_H_
#define IPC_MAIL_LIST_H_
 
#include "application_mailist.h"
#include "sso_dehydrator_mailist.h"
#include "sso_power_mode_mailist.h"
#include "worker_mailist.h"

#define IPC_INTERNAL_MAILIST(X) \
   APP_INT_MAILIST(X) \
   SSO_DEHYD_INT_MAILIST(X) \
   SSO_PM_INT_MAILIST(X) \
   WORKER_INT_MAILIST(X)  \

#define IPC_PUBLIC_MAILIST(X) \
   APP_PBC_MAILIST(X) \
   SSO_DEHYD_PBC_MAILIST(X) \
   SSO_PM_PBC_MAILIST(X) \
   WORKER_PBC_MAILIST(X)  \

#define IPC_RETRIEVE_TOUT_MS (500U)

#endif /*IPC_MAIL_LIST_H_*/
