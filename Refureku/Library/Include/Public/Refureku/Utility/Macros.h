/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

//Compiler dependant macros
#if defined(__GNUC__)

#elif defined(__clang__)

#elif defined(_MSC_VER)

#else

#endif

//Utility macros
#ifndef _RFK_UNPACK_IF_NOT_PARSING

//This macro "KODGEN_PARSING" must match the name defined by the kodgen parser when parsing source files
//It is used by the generated code to hide some portions of code to the parser
#ifdef KODGEN_PARSING
#define RFK_UNPACK_IF_NOT_PARSING(...)
#else
#define RFK_UNPACK_IF_NOT_PARSING(...) __VA_ARGS__
#endif

#endif