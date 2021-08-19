/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#if defined(__GNUC__) || defined(__clang__)

#define PRAGMATIZE(param)						_Pragma(#param)
#define DISABLE_WARNING_PUSH					PRAGMATIZE(GCC diagnostic push)
#define DISABLE_WARNING_POP						PRAGMATIZE(GCC diagnostic pop) 
#define DISABLE_WARNING(warningName)			PRAGMATIZE(GCC diagnostic ignored #warningName)

#define DISABLE_WARNING_INIT_SEG
#define DISABLE_WARNING_OFFSETOF				DISABLE_WARNING(-Winvalid-offsetof)
#define DISABLE_WARNING_UNSCOPED_ENUM
#define DISABLE_WARNING_UNINIT_VALUE
#define DISABLE_WARNING_NOEXCEPT
#define DISABLE_WARNING_ARITHMETIC_OVERFLOW

#elif defined(_MSC_VER)

#define DISABLE_WARNING_PUSH					__pragma(warning(push))
#define DISABLE_WARNING_POP						__pragma(warning(pop)) 
#define DISABLE_WARNING(warningNumber)			__pragma(warning(disable: warningNumber))

#define DISABLE_WARNING_INIT_SEG				DISABLE_WARNING(4073)
#define DISABLE_WARNING_OFFSETOF
#define DISABLE_WARNING_UNSCOPED_ENUM			DISABLE_WARNING(26812)
#define DISABLE_WARNING_UNINIT_VALUE			DISABLE_WARNING(26495)
#define DISABLE_WARNING_NOEXCEPT				DISABLE_WARNING(26439)
#define DISABLE_WARNING_ARITHMETIC_OVERFLOW		DISABLE_WARNING(26451)

#else

#define DISABLE_WARNING_PUSH
#define DISABLE_WARNING_POP

#define DISABLE_WARNING_INIT_SEG
#define DISABLE_WARNING_OFFSETOF
#define DISABLE_WARNING_UNSCOPED_ENUM
#define DISABLE_WARNING_UNINIT_VALUE
#define DISABLE_WARNING_NOEXCEPT
#define DISABLE_WARNING_ARITHMETIC_OVERFLOW

#endif