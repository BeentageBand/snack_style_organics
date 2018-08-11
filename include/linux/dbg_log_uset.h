#ifndef DBG_LOG_USET_H_
#define DBG_LOG_USET_H_

#define DBG_FID_LIST(FID) \
	/*  Feature ID,        Dbg Level,    Description */ \
   FID(APP_FID,            DBG_INFO_LVL, "Application") \
   FID(IPC_FID,            DBG_WARN_LVL, "IPC FrameWork") \
   FID(STATE_MACHINE_FID,  DBG_WARN_LVL, "State Machine") \
   FID(SSO_PM_FID,         DBG_WARN_LVL, "Snack Style Organics Power Mode App") \

#define Dbg_Log_Print(feat_id, lvl, line, ...) \
    Dbg_Log(lvl, IFF_1(__VA_ARGS__), feat_id, \
    IF(NOT(CHECK(__VA_ARGS__)))(line, line, IFF_0(__VA_ARGS__)))
 
#endif /*DBG_LOG_USET_H_*/
