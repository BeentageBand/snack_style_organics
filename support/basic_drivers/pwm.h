/*
 * pwm.h
 *
 *  Created on: Oct 8, 2017
 *      Author: Puch
 */

#ifndef PWM_H_
#define PWM_H_

#include "pwm_setup.h"
#include "reuse.h"
#include "dio.h"

enum
{
   PWM_PORT_LIST(PWM_PORT_ENUM)
   PWM_PORT_MAX
};

typedef uint8_t PWM_T;

enum
{
	PWM_SUCCESS,
	PWM_FILE_NOT_OPENED,
	PWM_FILE_NOT_CLOSED,
	PWM_FILE
};

typedef uint8_t PWM_RC_T ;

union PWM_Data
{
	uint8_t w8b;
	uint16_t w16b;
	uint32_t w32b;
};

extern PWM_RC_T PWM_Config(PWM_T const pwm, uint32_t const freq);

extern PWM_RC_T PWM_Write(PWM_T const pwm, union PWM_Data width);

#endif /* PWM_H_ */
