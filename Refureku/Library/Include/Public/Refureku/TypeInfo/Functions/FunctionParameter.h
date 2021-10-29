/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Entity/Entity.h"
#include "Refureku/TypeInfo/Type.h"

namespace rfk
{
	class FunctionParameter final : public Entity
	{
		public:
			REFUREKU_INTERNAL FunctionParameter(char const*		name,
												std::size_t		id,
												Type const&		type,
												Entity const*	outerEntity = nullptr)	noexcept;
			FunctionParameter(FunctionParameter const&)									= delete;
			REFUREKU_INTERNAL FunctionParameter(FunctionParameter&&)					noexcept;
			REFUREKU_INTERNAL ~FunctionParameter()										noexcept;

			/**
			*	@brief Get the type of the function parameter.
			* 
			*	@return The type of the function parameter.
			*/
			RFK_NODISCARD REFUREKU_API Type const& getType()	const	noexcept;

		private:
			//Forward declaration
			class FunctionParameterImpl;

			RFK_GEN_GET_PIMPL(FunctionParameterImpl, Entity::getPimpl())
	};
}