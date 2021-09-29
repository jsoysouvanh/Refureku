/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Entity/Entity.h"
#include "Refureku/TypeInfo/TypeAPI.h"

namespace rfk
{
	class VariableBaseAPI : public EntityAPI
	{
		public:
			/**
			*	@brief Get the type of this variable.
			* 
			*	@return The type of the variable.
			*/
			REFUREKU_API TypeAPI const& getType() const noexcept;

		protected:
			//Forward declaration
			class VariableBaseImpl;

			REFUREKU_INTERNAL VariableBaseAPI(VariableBaseImpl* implementation)	noexcept;
			REFUREKU_INTERNAL ~VariableBaseAPI()								noexcept;
	};
}