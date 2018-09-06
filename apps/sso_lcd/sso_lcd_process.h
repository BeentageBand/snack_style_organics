#ifndef SSO_LCD_PROCESS_H_
#define SSO_LCD_PROCESS_H_

#include "sso_lcd_worker.h"

#define CHash_Set_LCD CHash_Set_Pair_IPC_MID_SSO_LCD_Process
typedef void (* SSO_LCD_Process_T )(union SSO_LCD_Worker * const, union Mail * const);

#define CHash_Map_Params IPC_MID, SSO_LCD_Process
#include "chash_map.h"
#undef CHash_Map_Params

typedef CHash_Map_IPC_MID_SSO_LCD_Process_T SSO_LCD_Dispatcher_T;
typedef Pair_IPC_MID_SSO_LCD_Process_T SSO_LCD_Process_MID_T

extern void Populate_SSO_LCD_Dispatcher(SSO_LCD_Dispatcher_T * const dispatcher);

#endif /* SSO_LCD_PROCESS_H_ */
