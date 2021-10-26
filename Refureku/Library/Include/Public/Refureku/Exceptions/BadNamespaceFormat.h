/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include <stdexcept>

namespace rfk
{
	class BadNamespaceFormat : public std::invalid_argument
	{
		public:
			using std::invalid_argument::invalid_argument;
	};
}