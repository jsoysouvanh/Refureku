/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#ifndef NDEBUG

#define KODGEN_DEBUG	1
#define KODGEN_RELEASE	0

#else	//RELEASE

#define KODGEN_DEBUG	0
#define KODGEN_RELEASE	1

#endif

#define KODGEN_VERSION_MAJOR 1
#define KODGEN_VERSION_MINOR 1
#define KODGEN_VERSION_PATCH 0