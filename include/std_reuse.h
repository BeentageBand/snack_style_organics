#ifndef STD_REUSE_H_
#define STD_REUSE_H_
/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef __cplusplus
#include <iostream>

extern "C" {
#endif

/*=====================================================================================* 
 * Exported Type Declarations
 *=====================================================================================*/
typedef bool bool_t;

/*=====================================================================================* 
 * Exported Function Like Macros
 *=====================================================================================*/
#define Num_Elems(array) (sizeof(array)/sizeof(array[0]))
#define Isnt_Nullptr(obj, retval) if(NULL == obj) return retval

#ifdef __cplusplus
}
#endif
#endif /*STD_REUSE_H_*/
