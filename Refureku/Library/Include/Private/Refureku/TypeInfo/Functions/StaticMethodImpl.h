/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Functions/StaticMethodAPI.h"
#include "Refureku/TypeInfo/Functions/MethodBaseImpl.h"

namespace rfk
{
	class StaticMethodAPI::StaticMethodImpl final : public MethodBaseAPI::MethodBaseImpl
	{
		public:
			inline StaticMethodImpl(char const*		name,
									std::size_t		id,
									TypeAPI const&		returnType,
									ICallable*			internalMethod,
									EMethodFlags		flags,
									EntityAPI const*	outerEntity)	noexcept;
	};

	#include "Refureku/TypeInfo/Functions/StaticMethodImpl.inl"
}