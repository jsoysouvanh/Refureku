/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Functions/StaticMethod.h"
#include "Refureku/TypeInfo/Functions/MethodBaseImpl.h"

namespace rfk
{
	class StaticMethod::StaticMethodImpl final : public MethodBase::MethodBaseImpl
	{
		public:
			inline StaticMethodImpl(char const*		name,
									std::size_t		id,
									Type const&		returnType,
									ICallable*			internalMethod,
									EMethodFlags		flags,
									Entity const*	outerEntity)	noexcept;
	};

	#include "Refureku/TypeInfo/Functions/StaticMethodImpl.inl"
}