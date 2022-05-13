/**
*	Copyright (c) 2020-2022 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

//Version
#define REFUREKU_VERSION_MAJOR 2
#define REFUREKU_VERSION_MINOR 2
#define REFUREKU_VERSION_PATCH 0
#define REFUREKU_VERSION (REFUREKU_VERSION_MAJOR * 10000 + REFUREKU_VERSION_MINOR * 100 + REFUREKU_VERSION_PATCH)

//Features
/**
*	RFK_TEMPLATE_TEMPLATE_SUPPORT: Can reflect class templates using template template parameters
* 
*	RFK_NON_PUBLIC_NESTED_CLASS_TEMPLATE_SUPPORT: Can reflect non-public class templates nested in structs/classes.
*/
#if !defined(_MSC_VER) || defined(__clang__)
	#define RFK_TEMPLATE_TEMPLATE_SUPPORT					1
	#define RFK_NON_PUBLIC_NESTED_CLASS_TEMPLATE_SUPPORT	1
#else
	#define RFK_TEMPLATE_TEMPLATE_SUPPORT 0
	#define RFK_NON_PUBLIC_NESTED_CLASS_TEMPLATE_SUPPORT 0
#endif

//Debug / Release flags
#ifndef NDEBUG

	#define RFK_DEBUG	1
	#define RFK_RELEASE	0

#else	//RELEASE

	#define RFK_DEBUG	0
	#define RFK_RELEASE	1

#endif

//Attributes
#define RFK_NODISCARD	[[nodiscard]]
#define RFK_NORETURN	[[noreturn]]

//Dynamic library import/export
#if defined(KODGEN_PARSING)

	#define REFUREKU_API				__attribute__((dllexport))
	#define REFUREKU_INTERNAL
	#define REFUREKU_TEMPLATE_API(...)

#elif defined(_WIN32) || defined(__CYGWIN__)

	#if defined(REFUREKU_EXPORT)

		#if defined(__GNUC__)
			#define REFUREKU_API			__attribute__((dllexport))
		#else
			#define REFUREKU_API			__declspec(dllexport)
		#endif

		#define REFUREKU_TEMPLATE_API_DEF 	REFUREKU_API
		#define REFUREKU_TEMPLATE_API(...)	extern template class __VA_ARGS__

	#else

		#if defined(__GNUC__)
			#define REFUREKU_API __attribute__((dllimport))
		#else
			#define REFUREKU_API __declspec(dllimport)
		#endif

		#define REFUREKU_TEMPLATE_API(...)	template class REFUREKU_API __VA_ARGS__

  #endif

	#define REFUREKU_INTERNAL

#else

	#if __GNUC__ >= 4

		#if defined(REFUREKU_EXPORT)

			#define REFUREKU_API				__attribute__((visibility("default")))
			#define REFUREKU_INTERNAL			__attribute__((visibility("hidden")))
			#define REFUREKU_TEMPLATE_API_DEF
			#define REFUREKU_TEMPLATE_API(...)	extern template class REFUREKU_API __VA_ARGS__

		#else

			#define REFUREKU_API
			#define REFUREKU_INTERNAL
			#define REFUREKU_TEMPLATE_API(...)

		#endif

	#else

		#define REFUREKU_API
		#define REFUREKU_INTERNAL
		#define REFUREKU_TEMPLATE_API(...)

	#endif

#endif