/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Functions/MethodBase.h"

namespace rfk::internal
{
	/** Base declaration of the helper. */
	template <typename T>
	class MethodHelper;

	/** Overload for normal methods. */
	template <typename ReturnType, typename... ArgTypes>
	class MethodHelper<ReturnType(ArgTypes...)>
	{
		public:
			static bool hasSameSignature(MethodBase const& method) noexcept;
	};

	/** Overload for noexcept methods. */
	template <typename ReturnType, typename... ArgTypes>
	class MethodHelper<ReturnType(ArgTypes...) noexcept>
	{
		public:
			static bool hasSameSignature(MethodBase const& method) noexcept;
	};

	/** Overload for const methods. */
	template <typename ReturnType, typename... ArgTypes>
	class MethodHelper<ReturnType(ArgTypes...) const>
	{
		public:
			static bool hasSameSignature(MethodBase const& method) noexcept;
	};

	/** Overload for const noexcept methods. */
	template <typename ReturnType, typename... ArgTypes>
	class MethodHelper<ReturnType(ArgTypes...) const noexcept>
	{
		public:
			static bool hasSameSignature(MethodBase const& method) noexcept;
	};

	#include "Refureku/TypeInfo/Functions/MethodHelper.inl"
}