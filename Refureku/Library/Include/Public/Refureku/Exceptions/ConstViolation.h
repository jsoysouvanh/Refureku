/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include <stdexcept>

namespace rfk
{
	class ConstViolation : public std::logic_error
	{
		public:
			using std::logic_error::logic_error;
	};
}