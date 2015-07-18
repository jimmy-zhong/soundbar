/**
*  @file      tym_type.h
*  @brief    Common type define
*  @author    Bill Wu
*  @date      11 -2013
*  @copyright Tymphany Ltd.
*/

#ifndef __TYM_TYPE_H__
#define __TYM_TYPE_H__

#include "stm8s_type.h"

#ifndef NULL
#define NULL ((void *)0)
#endif

typedef unsigned long  uint32;
typedef unsigned short uint16;
typedef long           int32;
typedef short          int16;
typedef signed char    int8;
typedef unsigned char  uint8;

#ifndef TRUE
#define TRUE           ((bool)1)
#endif
#ifndef FALSE
#define FALSE          ((bool)0)
#endif


#endif /* __TYM_TYPE_H__ */

