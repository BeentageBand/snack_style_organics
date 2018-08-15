#ifndef IPC_USET_H_
#define IPC_USET_H_
 
#define IPC_THREAD_LIST(TASK_ID) \
TASK_ID(APP_WORKER_TID,         "Application Manager ") \
TASK_ID(SSO_DEHYD_WORKER_TID,   "Dehydrator Control") \
TASK_ID(SSO_PM_WORKER_TID,             "Power Mode") \

#endif /*IPC_USET_H_*/
