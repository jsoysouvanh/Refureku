/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <cassert>

#include "Refureku/TypeInfo/Entity/DefaultEntityRegistererAPI.h"
#include "Refureku/TypeInfo/Entity/Entity.h"
#include "Refureku/TypeInfo/DatabaseImpl.h"

namespace rfk
{
	class internal::DefaultEntityRegistererImpl final
	{
		private:
			EntityAPI const& _registeredEntity;

		public:
			inline DefaultEntityRegistererImpl(EntityAPI const& entity)	noexcept;
			inline ~DefaultEntityRegistererImpl()						noexcept;

			/**
			*	@brief Getter for the field _registeredEntity.
			* 
			*	@return _registeredEntity.
			*/
			inline EntityAPI const& getRegisteredEntity() const noexcept;
	};

	#include "Refureku/TypeInfo/Entity/DefaultEntityRegistererImpl.inl"
}