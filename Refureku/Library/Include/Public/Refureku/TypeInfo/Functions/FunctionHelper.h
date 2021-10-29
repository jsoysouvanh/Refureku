/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Functions/Function.h"

namespace rfk::internal
{
	/** Base declaration of the helper. */
	template <typename T>
	class FunctionHelper;

	/** Overload for normal functions. */
	template <typename ReturnType, typename... ArgTypes>
	class FunctionHelper<ReturnType(ArgTypes...)>
	{
		public:
			static bool hasSameSignature(Function const& function) noexcept;
	};

	/** Overload for noexcept functions. */
	template <typename ReturnType, typename... ArgTypes>
	class FunctionHelper<ReturnType(ArgTypes...) noexcept>
	{
		public:
			static bool hasSameSignature(Function const& function) noexcept;
	};

	#include "Refureku/TypeInfo/Functions/FunctionHelper.inl"
}