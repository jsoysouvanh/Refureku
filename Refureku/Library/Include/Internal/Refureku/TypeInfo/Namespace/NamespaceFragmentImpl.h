/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include <vector>

#include "Refureku/TypeInfo/Namespace/NamespaceFragment.h"
#include "Refureku/TypeInfo/Namespace/Namespace.h"
#include "Refureku/TypeInfo/Entity/EntityImpl.h"
#include "Refureku/Misc/SharedPtr.h"

namespace rfk
{
	class NamespaceFragment::NamespaceFragmentImpl final : public Entity::EntityImpl
	{
		private:
			/** Collection of all entities contained in this namespace fragment. */
			std::vector<Entity const*>	_nestedEntities;

			/** Pointer to the namespace this fragment merged to. */
			SharedPtr<Namespace>		_mergedNamespace;

		public:
			inline NamespaceFragmentImpl(char const*			name,
										 std::size_t			id,
										 SharedPtr<Namespace>&&	mergedNamespace)	noexcept;

			/**
			*	@brief Add a nested entity to the fragment as well as the merged namespace.
			*	
			*	@param nestedEntity The nested entity to add to the namespace fragment.
			*/
			inline void								addNestedEntity(Entity const& nestedEntity)			noexcept;

			/**
			*	@brief	Add a property to this namespace fragment.
			*			The property is immediately added to the merged namespace.
			*	
			*	@param property The property to add.
			*	
			*	@return	true if the property was added,
			*			false if it failed to be added (allow multiple is false and the property is already in the entity for example).
			*/
			inline bool								addProperty(Property const& property)				noexcept;

			/**
			*	@brief	Set the number of nested entities for this entity.
			*			Useful to avoid reallocations when adding a lot of entities.
			*			If the number of entities is already >= to the provided count, this method has no effect.
			* 
			*	@param capacity The number of entities of this namespace fragment.
			*/
			inline void								setNestedEntitiesCapacity(std::size_t capacity)		noexcept;

			/**
			*	@brief Getter for the field _nestedEntities.
			* 
			*	@return _nestedEntities.
			*/
			RFK_NODISCARD inline
				std::vector<Entity const*> const&	getNestedEntities()							const	noexcept;

			/**
			*	@brief Getter for the field _mergedNamespace.
			* 
			*	@return _mergedNamespace.
			*/
			RFK_NODISCARD inline
				rfk::SharedPtr<Namespace> const&	getMergedNamespace()						const	noexcept;

			/**
			*	@brief Remove this fragment entities from the merged namespace.
			*/
			inline void								unmergeFragment()							const	noexcept;
	};

	#include "Refureku/TypeInfo/Namespace/NamespaceFragmentImpl.inl"
}