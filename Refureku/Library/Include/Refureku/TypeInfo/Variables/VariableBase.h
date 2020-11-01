/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <string>

#include "Refureku/TypeInfo/Entity.h"
#include "Refureku/TypeInfo/Type.h"
#include "Refureku/Misc/FundamentalTypes.h"

namespace rfk
{
	/** Base class for all variables related entities (member, non-member). */
	class VariableBase : public Entity
	{
		protected:
			VariableBase()							= delete;
			VariableBase(std::string&&	name,
						 uint64			id,
						 EEntityKind	newKind,
						 Type const&	type)		noexcept;
			VariableBase(VariableBase const&)		= delete;
			VariableBase(VariableBase&&)			= delete;
			~VariableBase()							= default;
			
		public:
			/** Type of this variable. */
			Type const& type;
	};
}