/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <vector>

#include "Refureku/Config.h"
#include "Refureku/TypeInfo/Entity/Entity.h"

namespace rfk
{
	class NamespaceFragment final : public Entity
	{
		public:
			/** Collection of all entities contained in this namespace fragment. */
			std::vector<Entity const*>	nestedEntities;

			REFUREKU_API NamespaceFragment(std::string&& newName,
										   uint64		 newId	= 0u)	noexcept;
			NamespaceFragment(NamespaceFragment const&)		= delete;
			NamespaceFragment(NamespaceFragment&&)			= default;
			~NamespaceFragment()							= default;

			/**
			*	@brief Add a nested entity to the namespace.
			*	
			*	@param nestedEntity The nested entity to add to the namespace fragment.
			*	
			*	@param this.
			*/
			REFUREKU_API NamespaceFragment* addNestedEntity(Entity const* nestedEntity) noexcept;
	};
}