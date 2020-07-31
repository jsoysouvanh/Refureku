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
	class TypeMismatch : public std::logic_error
	{
		public:
			explicit TypeMismatch(std::string const& errorMessage)	noexcept;
			TypeMismatch(TypeMismatch const&)						= default;
			TypeMismatch(TypeMismatch&&)							= default;
			~TypeMismatch()											= default;
	};
}