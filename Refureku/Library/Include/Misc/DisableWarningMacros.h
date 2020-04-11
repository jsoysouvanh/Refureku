#pragma once

#if defined(_MSC_VER)

#define __RFK_DISABLE_WARNING_PUSH				__pragma(warning(push))
#define __RFK_DISABLE_WARNING_POP				__pragma(warning(pop)) 
#define __RFK_DISABLE_WARNING(warningNumber)	__pragma(warning(disable: warningNumber))

#define __RFK_DISABLE_WARNING_INIT_SEG			__RFK_DISABLE_WARNING(4073)
#define __RFK_DISABLE_WARNING_OFFSETOF
#define __RFK_DISABLE_WARNING_UNSCOPED_ENUM		__RFK_DISABLE_WARNING(26812)

#elif defined(__GNUC__) || defined(__clang__)

#define __RFK_PRAGMATIZE(param)					_Pragma(#param)
#define __RFK_DISABLE_WARNING_PUSH				__RFK_PRAGMATIZE(GCC diagnostic push)
#define __RFK_DISABLE_WARNING_POP				__RFK_PRAGMATIZE(GCC diagnostic pop) 
#define __RFK_DISABLE_WARNING(warningName)		__RFK_PRAGMATIZE(GCC diagnostic ignored #warningName)

#define __RFK_DISABLE_WARNING_INIT_SEG
#define __RFK_DISABLE_WARNING_OFFSETOF			__RFK_DISABLE_WARNING(-Winvalid-offsetof)
#define __RFK_DISABLE_WARNING_UNSCOPED_ENUM

#else

#define __RFK_DISABLE_WARNING_PUSH
#define __RFK_DISABLE_WARNING_POP
#define __RFK_DISABLE_WARNING(param)

#define __RFK_DISABLE_WARNING_INIT_SEG
#define __RFK_DISABLE_WARNING_OFFSETOF
#define __RFK_DISABLE_WARNING_UNSCOPED_ENUM

#endif