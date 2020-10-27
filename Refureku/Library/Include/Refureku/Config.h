/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#ifndef NDEBUG

	#define REFUREKU_DEBUG		1
	#define REFUREKU_RELEASE	0

#else	//RELEASE

	#define REFUREKU_DEBUG		0
	#define REFUREKU_RELEASE	1

#endif

#define REFUREKU_VERSION_MAJOR 1
#define REFUREKU_VERSION_MINOR 3
#define REFUREKU_VERSION_PATCH 0