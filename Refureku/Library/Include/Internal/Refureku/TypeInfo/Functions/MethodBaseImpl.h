/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Functions/MethodBase.h"
#include "Refureku/TypeInfo/Functions/FunctionBaseImpl.h"

namespace rfk
{
	class MethodBase::MethodBaseImpl : public FunctionBase::FunctionBaseImpl
	{
		private:
			/** Flags qualifying this method. */
			EMethodFlags	_flags	= EMethodFlags::Default;

		public:
			inline MethodBaseImpl(char const*		name, 
								  std::size_t		id,
								  Type const&	returnType,
								  ICallable*		internalMethod,
								  EMethodFlags		flags,
								  Entity const*	outerEntity)	noexcept;

			RFK_NODISCARD inline EMethodFlags getFlags()	const	noexcept;
	};

	#include "Refureku/TypeInfo/Functions/MethodBaseImpl.inl"
}