/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <cassert>

#include "Refureku/TypeInfo/Functions/FunctionBase.h"

namespace rfk::internal
{
	template <typename T>
	class FunctionHelper
	{
		public:
			static bool hasSamePrototype(FunctionBase const&) noexcept;
	};

	template <typename ReturnType, typename... ArgTypes>
	class FunctionHelper<ReturnType(ArgTypes...)>
	{
		public:
			static bool hasSamePrototype(FunctionBase const& function) noexcept;
	};

	#include "Refureku/TypeInfo/Functions/FunctionHelper.inl"
}