/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#define REFUREKU_VERSION_MAJOR 2
#define REFUREKU_VERSION_MINOR 0
#define REFUREKU_VERSION_PATCH 0

#ifndef NDEBUG

	#define REFUREKU_DEBUG		1
	#define REFUREKU_RELEASE	0

#else	//RELEASE

	#define REFUREKU_DEBUG		0
	#define REFUREKU_RELEASE	1

#endif

//Dynamic library import/export macros
#if defined(KODGEN_PARSING)

	#define REFUREKU_API
	#define REFUREKU_INTERNAL

#elif defined(_WIN32) || defined(__CYGWIN__)

	#if defined(REFUREKU_EXPORT)

		#if defined(__GNUC__)
			#define REFUREKU_API __attribute__((dllexport))
		#else
			#define REFUREKU_API __declspec(dllexport)
		#endif

	#else

		#if defined(__GNUC__)
			#define REFUREKU_API	__attribute__((dllimport))
		#else
			#define REFUREKU_API	__declspec(dllimport)
		#endif

  #endif

	#define REFUREKU_INTERNAL

#else

	#if __GNUC__ >= 4

		#define REFUREKU_API		__attribute__((visibility("default")))
		#define REFUREKU_INTERNAL	__attribute__((visibility("hidden")))

	#else

		#define REFUREKU_API
		#define REFUREKU_INTERNAL

	#endif

#endif