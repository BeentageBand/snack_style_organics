/*
 * adc.h
 *
 *  Created on: Oct 8, 2017
 *      Author: Puch
 */

#ifndef ADC_H_
#define ADC_H_

#include "adc_setup.h"
#include "reuse.h"
#include "dio.h"

enum
{
	ADC_PORT_LIST(ADC_PORT_ENUM)
	ADC_PORT_MAX
};

typedef uint8_t ADC_T;

typedef uint16_t ADC_Res_T;

typedef uint16_t ADC_Limit_T;

enum
{
	ADC_SUCCESS,
	ADC_FILE_NOT_OPENED,
	ADC_FILE_NOT_CLOSED,
	ADC_FILE
};

typedef uint8_t ADC_RC_T ;

union ADC_Data_T
{
	uint8_t r8b;
	uint16_t r16b;
	uint32_t r32b;
};

extern ADC_RC_T ADC_Config(ADC_T const port, ADC_Res_T const resolution, ADC_Limit_T const adc_max);

extern union ADC_Data_T ADC_Read(ADC_T const port);

#endif /* ADC_H_ */
