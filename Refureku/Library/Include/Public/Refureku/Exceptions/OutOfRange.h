/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <stdexcept>

namespace rfk
{
	class OutOfRange : public std::out_of_range
	{
		public:
			using std::out_of_range::out_of_range;
	};
}