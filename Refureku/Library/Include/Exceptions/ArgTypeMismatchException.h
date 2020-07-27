/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <stdexcept>
#include <string>

namespace rfk
{
	class ArgTypeMismatchException : public std::logic_error
	{
		public:
			explicit ArgTypeMismatchException(std::string const& errorMessage)	noexcept;
			ArgTypeMismatchException(ArgTypeMismatchException const&)			= default;
			ArgTypeMismatchException(ArgTypeMismatchException&&)				= default;
			~ArgTypeMismatchException()											= default;
	};
}