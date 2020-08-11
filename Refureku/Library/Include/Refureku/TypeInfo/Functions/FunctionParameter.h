/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <string>

#include "Refureku/TypeInfo/Type.h"

namespace rfk
{
	class FunctionParameter
	{
		public:
			/** Name of this parameter. Can be unspecified (empty). */
			std::string	name;

			/** Type of this parameter */
			Type const&	type;

			FunctionParameter()										= delete;
			FunctionParameter(std::string&& name, Type const& type)	noexcept;
			FunctionParameter(FunctionParameter const&)				= default;
			FunctionParameter(FunctionParameter&&)					= default;
			~FunctionParameter()									= default;
	};
}