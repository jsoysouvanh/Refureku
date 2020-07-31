/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Exceptions/TypeMismatch.h"

namespace rfk
{
	class ArgTypeMismatch : public TypeMismatch
	{
		public:
			explicit ArgTypeMismatch(std::string const& errorMessage)	noexcept;
			ArgTypeMismatch(ArgTypeMismatch const&)						= default;
			ArgTypeMismatch(ArgTypeMismatch&&)							= default;
			~ArgTypeMismatch()											= default;
	};
}