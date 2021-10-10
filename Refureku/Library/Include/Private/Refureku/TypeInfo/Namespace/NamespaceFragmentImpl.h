/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <vector>

#include "Refureku/TypeInfo/Namespace/NamespaceFragment.h"
#include "Refureku/TypeInfo/Entity/EntityImpl.h"

namespace rfk
{
	class NamespaceFragment::NamespaceFragmentImpl final : public Entity::EntityImpl
	{
		private:
			/** Collection of all entities contained in this namespace fragment. */
			std::vector<Entity const*>	_nestedEntities;	

		public:
			inline NamespaceFragmentImpl(char const* name,
										 std::size_t id)	noexcept;

			/**
			*	@brief Add a nested entity to the namespace.
			*	
			*	@param nestedEntity The nested entity to add to the namespace fragment.
			*/
			inline void									addNestedEntity(Entity const* nestedEntity)		noexcept;

			/**
			*	@brief	Set the number of nested entities for this entity.
			*			Useful to avoid reallocations when adding a lot of entities.
			*			If the number of entities is already >= to the provided count, this method has no effect.
			* 
			*	@param capacity The number of entities of this namespace fragment.
			*/
			inline void									setNestedEntitiesCapacity(std::size_t capacity)		noexcept;

			/**
			*	@brief Getter for the field _nestedEntities.
			* 
			*	@return _nestedEntities.
			*/
			inline std::vector<Entity const*> const&	getNestedEntities()							const	noexcept;
	};

	#include "Refureku/TypeInfo/Namespace/NamespaceFragmentImpl.inl"
}