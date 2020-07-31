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
	class ReturnTypeMismatch : public TypeMismatch
	{
		public:
			explicit ReturnTypeMismatch(std::string const& errorMessage)	noexcept;
			ReturnTypeMismatch(ReturnTypeMismatch const&)					= default;
			ReturnTypeMismatch(ReturnTypeMismatch&&)						= default;
			~ReturnTypeMismatch()											= default;
	};
}