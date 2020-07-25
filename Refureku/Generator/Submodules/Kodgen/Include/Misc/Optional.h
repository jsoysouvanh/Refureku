/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#if __has_include(<optional>)
	#include <optional>
	namespace opt = std;
#elif __has_include(<experimental/optional>)
	#include <experimental/optional>
	namespace opt = std::experimental;
#else
	#error "No optional support"
#endif