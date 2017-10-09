/*
 * spi.h
 *
 *  Created on: Oct 8, 2017
 *      Author: Puch
 */

#ifndef SPI_H_
#define SPI_H_

#include "spi_setup.h"
#include "dio.h"
#include "object.h"
#include <stdio.h>

#define SPI_INHERITS BASE_CLASS

#define SPI_MEMBERS(_member, _class) \
_member(SPI_Port_T _private, spi_port) \
_member(FILE _private, stream) \

#define SPI_METHODS(_method, _class) \
_method(SPI_RC_T, _class, open, void) \
_method(SPI_RC_T, _class, close, void) \
_method(SPI_RC_T, _class, scanf, void *, char const * const, ...) \
_method(SPI_RC_T, _class, printf, SPI_Callee_T const *, uint32_t, char const * const, ...) \

enum
{
	SPI_PORT_LIST(SPI_PORT_ENUM)
	SPI_PORT_MAX
};

typedef uint8_t SPI_Port_T;

enum
{
	SPI_SUCCESS,
	SPI_FILE_NOT_OPENED,
	SPI_FILE_NOT_CLOSED,
	SPI_FILE
};

typedef uint8_t SPI_RC_T ;

typedef uint16_t SPI_Speed_Kbps_T;

typedef DIO_T SPI_Callee_T;

extern union SPI SPI_Master(SPI_Port_T const, SPI_Speed_Kbps_T const speed_kbps,
   SPI_Callee_T const * callee_list, uint32_t callee_num);

extern union SPI * SPI__Master_New(SPI_Port_T const, SPI_Speed_Kbps_T const speed_kbps,
    SPI_Callee_T const * callee_list, uint32_t callee_num);

#endif /* SPI_H_ */
