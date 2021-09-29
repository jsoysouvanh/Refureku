/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Variables/VariableBaseAPI.h"
#include "Refureku/TypeInfo/Entity/EntityImpl.h"

namespace rfk
{
	class VariableBaseAPI::VariableBaseImpl : public EntityAPI::EntityImpl
	{
		private:
			/** Type of this variable. */
			TypeAPI const&	_type;

		public:
			inline VariableBaseImpl(char const*			name,
									std::size_t			id,
									EEntityKind			kind,
									TypeAPI const&		type,
									EntityAPI const*	outerEntity)	noexcept;

			/**
			*	@brief Getter for the field _type.
			* 
			*	@return _type.
			*/
			inline TypeAPI const& getType() const noexcept;
	};

	#include "Refureku/TypeInfo/Variables/VariableBaseImpl.inl"
}