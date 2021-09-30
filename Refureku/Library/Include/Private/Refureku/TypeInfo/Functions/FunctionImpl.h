/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Functions/FunctionAPI.h"
#include "Refureku/TypeInfo/Functions/FunctionBaseImpl.h"

namespace rfk
{
	class FunctionAPI::FunctionImpl final : public FunctionBaseAPI::FunctionBaseImpl
	{
		private:
			/** Flags describing this function. */
			EFunctionFlags	_flags	= EFunctionFlags::Default;

		public:
			inline FunctionImpl(char const*		name, 
								std::size_t		id,
								TypeAPI const&	returnType,
								ICallable*		internalFunction,
								EFunctionFlags	flags)			noexcept;

			/**
			*	@brief Getter for the field _flags.
			* 
			*	@return _flags.
			*/
			RFK_NODISCARD inline EFunctionFlags getFlags() const noexcept;
	};

	#include "Refureku/TypeInfo/Functions/FunctionImpl.inl"
}