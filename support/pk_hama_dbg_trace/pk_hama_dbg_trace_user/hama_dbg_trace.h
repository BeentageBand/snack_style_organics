/*=====================================================================================*/
/**
 * hama_dbg_trace.h
 * author : puch
 * date : Oct 22 2015
 *
 * description : Any comments
 *
 */
/*=====================================================================================*/
#ifndef HAMA_DBG_TRACE_H_
#define HAMA_DBG_TRACE_H_
/*=====================================================================================*
 * Project Includes
 *=====================================================================================*/

/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/
#if HOST
#include <cstdio>
#include <iostream>
#include <unistd.h>
/*=====================================================================================* 
 * Exported X-Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Define Macros
 *=====================================================================================*/
#define TR_PRINT_FILE printf("TR_INFO %s %d -  ", __FILE__, __LINE__)
#define TR_PRINT_LINE std::cout << std::endl; usleep(250000);

#else
#include "arduino_fwk_uart.h"
#endif
/*=====================================================================================* 
 * Exported Type Declarations
 *=====================================================================================*/

namespace dbg
{
/*=====================================================================================* 
 * Exported Object Declarations
 *=====================================================================================*/
#if HOST

#else
extern const Arduino_UART_T UART_Init;
extern const char CR[] PROGMEM;
#endif
/*=====================================================================================* 
 * Exported Function Prototypes
 *=====================================================================================*/
   extern void Init(void);
   extern void Shut(void);
}
/*=====================================================================================* 
 * Exported Function Like Macros
 *=====================================================================================*/
#if HOST

#define TR_INFO(msg)                       TR_PRINT_FILE; printf(msg);                    TR_PRINT_LINE
#define TR_INFO_1(msg, a1)                 TR_PRINT_FILE; printf(msg, a1);                TR_PRINT_LINE
#define TR_INFO_2(msg, a1, a2)             TR_PRINT_FILE; printf(msg, a1, a2);            TR_PRINT_LINE
#define TR_INFO_3(msg, a1, a2, a3)         TR_PRINT_FILE; printf(msg, a1, a2, a3);        TR_PRINT_LINE
#define TR_INFO_4(msg, a1, a2, a3, a4)     TR_PRINT_FILE; printf(msg, a1, a2, a3, a4);    TR_PRINT_LINE
#define TR_INFO_5(msg, a1, a2, a3, a4, a5) TR_PRINT_FILE; printf(msg, a1, a2, a3, a4, a5);TR_PRINT_LINE

#else

#define STR_LINE(l) #l
#define TR_INFO_INS(tr_info,l) tr_info##l

#define TR_INFO(msg)                       static const char TR_INFO_INS(tr_file, __LINE__)[] PROGMEM = __FILE__ " \0"; arduino::Print_UART_P( dbg::UART_Init.channel, TR_INFO_INS(tr_file, __LINE__) ); arduino::Print_UART( dbg::UART_Init.channel, __LINE__);  static const char TR_INFO_INS(tr_info, __LINE__)[] PROGMEM = " - "msg "\0"; arduino::Print_UART_P( dbg::UART_Init.channel, TR_INFO_INS(tr_info, __LINE__) ); arduino::Print_UART_P(dbg::UART_Init.channel, dbg::CR)
#define TR_INFO_1(msg, a1)                 static const char TR_INFO_INS(tr_file, __LINE__)[] PROGMEM = __FILE__ " \0"; arduino::Print_UART_P( dbg::UART_Init.channel, TR_INFO_INS(tr_file, __LINE__) ); arduino::Print_UART( dbg::UART_Init.channel, __LINE__);  static const char TR_INFO_INS(tr_info, __LINE__)[] PROGMEM = " - "msg "\0"; arduino::Print_UART_P( dbg::UART_Init.channel, TR_INFO_INS(tr_info, __LINE__) ); arduino::Print_UART(dbg::UART_Init.channel, a1); arduino::Print_UART_P(dbg::UART_Init.channel, dbg::CR)
#define TR_INFO_2(msg, a1, a2)             static const char TR_INFO_INS(tr_file, __LINE__)[] PROGMEM = __FILE__ " \0"; arduino::Print_UART_P( dbg::UART_Init.channel, TR_INFO_INS(tr_file, __LINE__) ); arduino::Print_UART( dbg::UART_Init.channel, __LINE__);  static const char TR_INFO_INS(tr_info, __LINE__)[] PROGMEM = " - "msg "\0"; arduino::Print_UART_P( dbg::UART_Init.channel, TR_INFO_INS(tr_info, __LINE__) ); arduino::Print_UART(dbg::UART_Init.channel, a1); arduino::Print_UART(dbg::UART_Init.channel,a2); arduino::Print_UART(dbg::UART_Init.channel, dbg::CR)
#define TR_INFO_3(msg, a1, a2, a3)         static const char TR_INFO_INS(tr_file, __LINE__)[] PROGMEM = __FILE__ " \0"; arduino::Print_UART_P( dbg::UART_Init.channel, TR_INFO_INS(tr_file, __LINE__) ); arduino::Print_UART( dbg::UART_Init.channel, __LINE__);  static const char TR_INFO_INS(tr_info, __LINE__)[] PROGMEM = " - "msg "\0"; arduino::Print_UART_P( dbg::UART_Init.channel, TR_INFO_INS(tr_info, __LINE__) ); arduino::Print_UART(dbg::UART_Init.channel, a1); arduino::Print_UART(dbg::UART_Init.channel,a2); arduino::Print_UART(dbg::UART_Init.channel, a3); arduino::Print_UART_P(dbg::UART_Init.channel, dbg::CR)
#define TR_INFO_4(msg, a1, a2, a3, a4)     static const char TR_INFO_INS(tr_file, __LINE__)[] PROGMEM = __FILE__ " \0"; arduino::Print_UART_P( dbg::UART_Init.channel, TR_INFO_INS(tr_file, __LINE__) ); arduino::Print_UART( dbg::UART_Init.channel, __LINE__);  static const char TR_INFO_INS(tr_info, __LINE__)[] PROGMEM = " - "msg "\0"; arduino::Print_UART_P( dbg::UART_Init.channel, TR_INFO_INS(tr_info, __LINE__) ); arduino::Print_UART(dbg::UART_Init.channel, a1); arduino::Print_UART(dbg::UART_Init.channel,a2); arduino::Print_UART(dbg::UART_Init.channel, a3); arduino::Print_UART(dbg::UART_Init.channel, a4); arduino::Print_UART_P(dbg::UART_Init.channel, dbg::CR)
#define TR_INFO_5(msg, a1, a2, a3, a4, a5) static const char TR_INFO_INS(tr_file, __LINE__)[] PROGMEM = __FILE__ " \0"; arduino::Print_UART_P( dbg::UART_Init.channel, TR_INFO_INS(tr_file, __LINE__) ); arduino::Print_UART( dbg::UART_Init.channel, __LINE__);  static const char TR_INFO_INS(tr_info, __LINE__)[] PROGMEM = " - "msg "\0"; arduino::Print_UART_P( dbg::UART_Init.channel, TR_INFO_INS(tr_info, __LINE__) ); arduino::Print_UART(dbg::UART_Init.channel, a1); arduino::Print_UART(dbg::UART_Init.channel,a2); arduino::Print_UART(dbg::UART_Init.channel, a3); arduino::Print_UART(dbg::UART_Init.channel, a4); arduino::Print_UART(dbg::UART_Init.channel, a5); arduino::Print_UART_P(dbg::UART_Init.channel, dbg::CR)

#endif
/*=====================================================================================* 
 * hama_dbg_trace.
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
#endif /*HAMA_DBG_TRACE_H_*/
