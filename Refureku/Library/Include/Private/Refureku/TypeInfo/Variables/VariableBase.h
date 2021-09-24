/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <string>

#include "Refureku/TypeInfo/Entity/EntityImplementation.h"
#include "Refureku/TypeInfo/Type.h"
#include "Refureku/Misc/FundamentalTypes.h"

namespace rfk
{
	/** Base class for all variables related entities (member, non-member). */
	class VariableBase : public Entity
	{
		private:
			/** Type of this variable. */
			Type const&	_type;

		protected:
			VariableBase(std::string&&	name,
						 std::size_t	id,
						 EEntityKind	newKind,
						 Type const&	type,
						 Entity const*	outerEntity = nullptr)	noexcept;
			VariableBase(VariableBase const&)					= delete;
			VariableBase(VariableBase&&)						= delete;
			
		public:
			/**
			*	@brief Getter for the field _type.
			* 
			*	@return _type.
			*/
			inline Type const& getType() const noexcept;


			VariableBase& operator=(VariableBase const&)	= delete;
			VariableBase& operator=(VariableBase&&)			= delete;
	};

	#include "Refureku/TypeInfo/Variables/VariableBase.inl"
}