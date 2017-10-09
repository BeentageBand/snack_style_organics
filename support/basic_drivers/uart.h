/*
 * uart.h
 *
 *  Created on: Oct 8, 2017
 *      Author: Puch
 */

#ifndef UART_H_
#define UART_H_

#include "uart_setup.h"
#include "dio.h"
#include "object.h"
#include <stdio.h>

#define UART_INHERITS BASE_CLASS

#define UART_MEMBERS(_member, _class) \
_member(UART_Port_T _private, uart_port) \
_member(FILE _private, stream) \

#define UART_METHODS(_method, _class) \
_method(UART_RC_T, _class, open, void) \
_method(UART_RC_T, _class, close, void) \
_method(UART_RC_T, _class, scanf, void *, char const * const, ...) \
_method(UART_RC_T, _class, printf, UART_Callee_T const *, uint32_t, char const * const, ...) \

enum
{
	UART_PORT_LIST(UART_PORT_ENUM)
	UART_PORT_MAX
};

typedef uint8_t UART_Port_T;

enum
{
	UART_SUCCESS,
	UART_FILE_NOT_OPENED,
	UART_FILE_NOT_CLOSED,
	UART_FILE
};

typedef uint8_t UART_RC_T ;

typedef uint16_t UART_Baudrate_T;

typedef uint8_t UART_Callee_T;

extern union UART UART_Master(UART_Port_T const, UART_Baudrate_T const baudrate);

extern union UART * UART__Master_New(UART_Port_T const, UART_Baudrate_T const baudrate);



#endif /* UART_H_ */
