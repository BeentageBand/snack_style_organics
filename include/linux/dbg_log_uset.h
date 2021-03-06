#ifndef DBG_LOG_USET_H_
#define DBG_LOG_USET_H_
/*===============================================================================*
 * X-Macros
 *===============================================================================*/
#define DBG_FID_LIST(FID) \
	/*  Feature ID,        Dbg Level,    Description */ \
   FID(APP_FID,            DBG_INFO_LVL, "Application") \
   FID(IPC_FID,            DBG_WARN_LVL, "IPC FrameWork") \
   FID(PID_FID,            DBG_INFO_LVL, "PID Controller") \
   FID(STATE_MACHINE_FID,  DBG_INFO_LVL, "State Machine") \
   FID(SSO_LAUNCHER_FID,   DBG_INFO_LVL, "Snack Style Organics launcher App") \
   FID(SSO_HID_FID,        DBG_INFO_LVL, "Snack Style Organics Human Interface Device App") \
   FID(SSO_LCD_FID,        DBG_INFO_LVL, "Snack Style Organics LCD Listener App") \
   FID(SSO_PM_FID,         DBG_INFO_LVL, "Snack Style Organics Power Mode App") \

/*===============================================================================*
 * Function-Like Macros
 *===============================================================================*/
#define Dbg_Log_Print(feat_id, lvl, line, ...) \
    Dbg_Log(lvl, IFF_1(__VA_ARGS__), feat_id, \
    IF(NOT(CHECK(__VA_ARGS__)))(line, line, IFF_0(__VA_ARGS__)))
 
#endif /*DBG_LOG_USET_H_*/
