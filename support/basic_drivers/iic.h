/*
 * iic.h
 *
 *  Created on: Oct 8, 2017
 *      Author: Puch
 */

#ifndef IIC_H_
#define IIC_H_

#include "iic_setup.h"
#include "dio.h"
#include "object.h"
#include <stdio.h>

#define IIC_INHERITS BASE_CLASS

#define IIC_MEMBERS(_member, _class) \
_member(IIC_Port_T _private, iic_port) \
_member(FILE _private, stream) \

#define IIC_METHODS(_method, _class) \
_method(IIC_RC_T, _class, open, void) \
_method(IIC_RC_T, _class, close, void) \
_method(IIC_RC_T, _class, scanf, void *, char const * const, ...) \
_method(IIC_RC_T, _class, printf, IIC_Callee_T const *, uint32_t, char const * const, ...) \

enum
{
	IIC_PORT_LIST(IIC_PORT_ENUM)
	IIC_PORT_MAX
};

typedef uint8_t IIC_Port_T;

enum
{
	IIC_SUCCESS,
	IIC_FILE_NOT_OPENED,
	IIC_FILE_NOT_CLOSED,
	IIC_FILE
};

typedef uint8_t IIC_RC_T ;

typedef uint16_t IIC_Speed_Kbps_T;

typedef uint8_t IIC_Callee_T;

extern union IIC IIC_Master(IIC_Port_T const, IIC_Speed_Kbps_T const speed_kbps,
   IIC_Callee_T const * callee_list, uint32_t callee_num);

extern union IIC * IIC__Master_New(IIC_Port_T const, IIC_Speed_Kbps_T const speed_kbps,
    IIC_Callee_T const * callee_list, uint32_t callee_num);

#endif /* IIC_H_ */
