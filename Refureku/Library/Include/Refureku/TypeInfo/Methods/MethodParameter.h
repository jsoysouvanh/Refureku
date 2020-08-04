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
	class MethodParameter
	{
		public:
			/** Name of this parameter. Can be unspecified (empty). */
			std::string	name;

			/** Type of this parameter */
			Type		type;

			MethodParameter()									= default;
			MethodParameter(std::string&& name, Type&& type)	noexcept;
			MethodParameter(MethodParameter const&)				= default;
			MethodParameter(MethodParameter&&)					= default;
			~MethodParameter()									= default;

			MethodParameter& operator=(MethodParameter const&)	= default;
			MethodParameter& operator=(MethodParameter&&)		= default;
	};
}