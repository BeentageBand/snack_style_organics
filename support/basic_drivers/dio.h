/*
 * dio.h
 *
 *  Created on: Oct 8, 2017
 *      Author: Puch
 */

#ifndef DIO_H_
#define DIO_H_

#include "dio_set.h"
#include "std_reuse.h"

#define DIO_ITEM_ENUM(pin, desc) pin,

#ifdef __cplusplus
extern "C"{
#endif

enum
{
	DIO_LIST(DIO_ITEM_ENUM)
	DIO_IO_MAX
};

typedef uint16_t DIO_T;

enum
{
	DIO_READO,
	DIO_WRITEO,
	DIO_PULLPUP_READO,
};

typedef uint8_t DIO_Config_T;

enum
{
	DIO_LOW,
	DIO_HIGH,
	DIO_UNINIT,
	DIO_LOCKED,
};

typedef uint8_t DIO_Pin_Lvl_T;

extern DIO_Pin_Lvl_T DIO_Config(DIO_T const pin, DIO_Config_T const cfg);

extern DIO_Pin_Lvl_T DIO_Write(DIO_T const pin, DIO_Pin_Lvl_T const wlvl);

extern DIO_Pin_Lvl_T DIO_Read(DIO_T const pin);

#ifdef __cplusplus
}
#endif
#endif /* DIO_H_ */
