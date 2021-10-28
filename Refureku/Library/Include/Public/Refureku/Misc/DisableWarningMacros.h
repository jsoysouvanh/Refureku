/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#if defined(__GNUC__) || defined(__clang__)

#define __RFK_PRAGMATIZE(param)						_Pragma(#param)
#define __RFK_DISABLE_WARNING_PUSH					__RFK_PRAGMATIZE(GCC diagnostic push)
#define __RFK_DISABLE_WARNING_POP					__RFK_PRAGMATIZE(GCC diagnostic pop) 
#define __RFK_DISABLE_WARNING(warningName)			__RFK_PRAGMATIZE(GCC diagnostic ignored #warningName)

#define __RFK_DISABLE_WARNING_INIT_SEG
#define __RFK_DISABLE_WARNING_OFFSETOF				__RFK_DISABLE_WARNING(-Winvalid-offsetof)
#define __RFK_DISABLE_WARNING_UNSCOPED_ENUM
#define __RFK_DISABLE_WARNING_UNUSED_RESULT			__RFK_DISABLE_WARNING(-Wunused-result)

#if defined (__clang__)
//clang specific warning flags
#define __RFK_DISABLE_WARNING_UNUSED_PRIVATE_FIELD		__RFK_DISABLE_WARNING(-Wunused-private-field)
#define __RFK_DISABLE_WARNING_LANGUAGE_EXTENSION_TOKEN	__RFK_DISABLE_WARNING(-Wlanguage-extension-token)
#define __RFK_DISABLE_WARNING_MISSING_OVERRIDE			__RFK_DISABLE_WARNING(-Winconsistent-missing-override)
#define __RFK_DISABLE_WARNING_UNDEFINED_INLINE			__RFK_DISABLE_WARNING(-Wundefined-inline)

#else
//gcc specific warning flags
#define __RFK_DISABLE_WARNING_UNUSED_PRIVATE_FIELD
#define __RFK_DISABLE_WARNING_LANGUAGE_EXTENSION_TOKEN
#define __RFK_DISABLE_WARNING_MISSING_OVERRIDE
#define __RFK_DISABLE_WARNING_UNDEFINED_INLINE

#endif

#elif defined(_MSC_VER)

#define __RFK_DISABLE_WARNING_PUSH					__pragma(warning(push))
#define __RFK_DISABLE_WARNING_POP					__pragma(warning(pop)) 
#define __RFK_DISABLE_WARNING(warningNumber)		__pragma(warning(disable: warningNumber))

#define __RFK_DISABLE_WARNING_INIT_SEG				__RFK_DISABLE_WARNING(4073)
#define __RFK_DISABLE_WARNING_OFFSETOF
#define __RFK_DISABLE_WARNING_UNSCOPED_ENUM			__RFK_DISABLE_WARNING(26812)
#define __RFK_DISABLE_WARNING_UNUSED_PRIVATE_FIELD
#define __RFK_DISABLE_WARNING_LANGUAGE_EXTENSION_TOKEN
#define __RFK_DISABLE_WARNING_UNUSED_RESULT			__RFK_DISABLE_WARNING(4834)
#define __RFK_DISABLE_WARNING_MISSING_OVERRIDE
#define __RFK_DISABLE_WARNING_UNDEFINED_INLINE

#else

#define __RFK_DISABLE_WARNING_PUSH
#define __RFK_DISABLE_WARNING_POP
#define __RFK_DISABLE_WARNING(param)

#define __RFK_DISABLE_WARNING_INIT_SEG
#define __RFK_DISABLE_WARNING_OFFSETOF
#define __RFK_DISABLE_WARNING_UNSCOPED_ENUM
#define __RFK_DISABLE_WARNING_UNUSED_PRIVATE_FIELD
#define __RFK_DISABLE_WARNING_LANGUAGE_EXTENSION_TOKEN
#define __RFK_DISABLE_WARNING_UNUSED_RESULT
#define __RFK_DISABLE_WARNING_MISSING_OVERRIDE
#define __RFK_DISABLE_WARNING_UNDEFINED_INLINE

#endif