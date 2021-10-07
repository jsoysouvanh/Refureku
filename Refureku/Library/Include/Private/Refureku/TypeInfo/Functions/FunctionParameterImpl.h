/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <string>

#include "Refureku/TypeInfo/Functions/FunctionParameterAPI.h"
#include "Refureku/TypeInfo/Entity/EntityImpl.h"

namespace rfk
{
	class FunctionParameterAPI::FunctionParameterImpl : public Entity::EntityImpl
	{
		private:
			/** Type of this parameter. */
			Type const&	_type;

		public:
			FunctionParameterImpl(char const*		name,
								  std::size_t		id,
								  Type const&	type,
								  Entity const*	outerEntity)	noexcept;

			/**
			*	@brief Getter for the field _type.
			* 
			*	@return _type;
			*/
			RFK_NODISCARD Type const& getType()	const	noexcept;
	};

	#include "Refureku/TypeInfo/Functions/FunctionParameterImpl.inl"
}