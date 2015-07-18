/**
*  @file      tym_assert.h
*  @brief    Assert API
*  @author    Bill Wu
*  @date      10 -2014
*  @copyright Tymphany Ltd.
*/

#ifndef __TYM_ASSERT_H__
#define __TYM_ASSERT_H__

#include <stdlib.h>
#include <stdio.h>

#ifndef RELEASE
#define TYM_ASSERT_ENABLED
#endif

#ifdef TYM_ASSERT_ENABLED
#define TYM_ASSERT(x) \
    { \
    if (!(x)) \
        { \
        printf("\nAssert [%d]\n", __LINE__); \
        exit(0); \
        } \
    }
#else
#define TYM_ASSERT(x)
#endif

#endif /* __TYM_ASSERT_H__ */

