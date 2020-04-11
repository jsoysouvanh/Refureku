#pragma once

#if defined(_MSC_VER)

#define DISABLE_WARNING_PUSH			__pragma(warning(push))
#define DISABLE_WARNING_POP				__pragma(warning(pop)) 
#define DISABLE_WARNING(warningNumber)	__pragma(warning(disable: warningNumber))

#define DISABLE_WARNING_INIT_SEG		DISABLE_WARNING(4073)
#define DISABLE_WARNING_OFFSETOF
#define DISABLE_WARNING_UNSCOPED_ENUM	DISABLE_WARNING(26812)

#elif defined(__GNUC__) || defined(__clang__)

#define PRAGMATIZE(param)				_Pragma(#param)
#define DISABLE_WARNING_PUSH			PRAGMATIZE(GCC diagnostic push)
#define DISABLE_WARNING_POP				PRAGMATIZE(GCC diagnostic pop) 
#define DISABLE_WARNING(warningName)	PRAGMATIZE(GCC diagnostic ignored #warningName)

#define DISABLE_WARNING_INIT_SEG
#define DISABLE_WARNING_OFFSETOF		DISABLE_WARNING(-Winvalid-offsetof)
#define DISABLE_WARNING_UNSCOPED_ENUM

#else

#define DISABLE_WARNING_PUSH
#define DISABLE_WARNING_POP

#define DISABLE_WARNING_INIT_SEG
#define DISABLE_WARNING_OFFSETOF
#define DISABLE_WARNING_UNSCOPED_ENUM

#endif