/**
*  @file      tym_debug.h
*  @brief    Debug config of TYM platform
*  @author    Bill Wu
*  @date      11 -2013
*  @copyright Tymphany Ltd.
*/

#ifndef __TYM_DEBUG_H__
#define __TYM_DEBUG_H__

#include <stdio.h>

#ifndef RELEASE
/* TYM debug switch */
#define TYM_DEBUG_ENABLED
#endif

#ifdef TYM_DEBUG_ENABLED
#define TYM_DEBUG(x) {printf x;}
#else
#define TYM_DEBUG(x)
#endif

#endif /* __TYM_DEBUG_H__ */

