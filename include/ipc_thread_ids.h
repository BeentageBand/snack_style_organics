#ifndef IPC_USET_H_
#define IPC_USET_H_
 
#define IPC_THREAD_LIST(X) \
X(APP_WORKER_TID,         "Application Manager ") \
X(SSO_DEHYD_WORKER_TID,   "Dehydrator Control") \
X(SSO_LCD_WORKER_TID,     "LCD Listener") \
X(SSO_PM_WORKER_TID,      "Power Mode") \

#endif /*IPC_USET_H_*/
