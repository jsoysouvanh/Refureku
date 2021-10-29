/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Entity/Entity.h"

namespace rfk
{
	//Forward declaration
	class Namespace;

	class NamespaceFragment final : public Entity
	{
		public:
			REFUREKU_API NamespaceFragment(char const*	name,
										   std::size_t	id = 0u)	noexcept;
			NamespaceFragment(NamespaceFragment&&)					= delete;
			REFUREKU_API ~NamespaceFragment()						noexcept;

			/**
			*	@brief Add a nested entity to the namespace.
			*	
			*	@param nestedEntity The nested entity to add to the namespace fragment.
			*	
			*	@param this.
			*/
			REFUREKU_API void						addNestedEntity(Entity const& nestedEntity)				noexcept;

			/**
			*	@brief	Set the number of nested entities for this entity.
			*			Useful to avoid reallocations when adding a lot of entities.
			*			If the number of entities is already >= to the provided count, this method has no effect.
			* 
			*	@param capacity The number of entities of this namespace fragment.
			*/
			REFUREKU_API void						setNestedEntitiesCapacity(std::size_t capacity)			noexcept;

			/**
			*	@brief	Add a property to this namespace fragment.
			*			The property is immediately added to the merged namespace.
			*	
			*	@param property The property to add.
			*	
			*	@return	true if the property was added,
			*			false if it failed to be added (allow multiple is false and the property is already in the entity for example).
			*/
			REFUREKU_API bool						addProperty(Property const& property)					noexcept;

			/**
			*	@brief Get the namespace this fragment is merged to.
			* 
			*	@return The namespace this fragment is merged to.
			*/
			REFUREKU_API Namespace const&			getMergedNamespace()							const	noexcept;

			/**
			*	@brief Execute the given visitor on all nested entities.
			* 
			*	@param visitor	Visitor function to call. Return false to abort the foreach loop.
			*	@param userData	Optional user data forwarded to the visitor.
			* 
			*	@return	The last visitor result before exiting the loop.
			*			If the visitor is nullptr, return false.
			* 
			*	@exception Any exception potentially thrown from the provided visitor.
			*/
			REFUREKU_INTERNAL bool					foreachNestedEntity(Visitor<Entity>	visitor,
																		void*			userData)	const;

			/**
			*	@brief Unmerge the fragment from the merged namespace.
			*/
			REFUREKU_INTERNAL void					unmergeFragment()								const	noexcept;

		private:
			//Forward declaration
			class NamespaceFragmentImpl;

			RFK_GEN_GET_PIMPL(NamespaceFragmentImpl, Entity::getPimpl())
	};
}