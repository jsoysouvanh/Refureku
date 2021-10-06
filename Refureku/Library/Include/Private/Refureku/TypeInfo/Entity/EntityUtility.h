/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <type_traits>

#include "Refureku/TypeInfo/Entity/EntityImpl.h"
#include "Refureku/Containers/Vector.h"
#include "Refureku/Misc/Visitor.h"

namespace rfk
{
	class EntityUtility
	{
		public:
			EntityUtility()		= delete;
			~EntityUtility()	= delete;

			/**
			*	@brief Execute the given visitor on all entities of the container.
			*
			*	@param container Container containing all the entities the visitor should run on.
			*	@param visitor	 Visitor function to call. Return false to abort the foreach loop.
			*	@param userData	 Optional user data forwarded to the visitor.
			* 
			*	@return	The last visitor result before exiting the loop.
			*			If the visitor is nullptr, return false.
			* 
			*	@exception Any exception potentially thrown from the provided visitor.
			*/
			template <typename EntityType, typename ContainerType>
			RFK_NODISCARD static bool								foreachEntity(ContainerType const&	container,
																				  Visitor<EntityType>	visitor,
																				  void*					userData);

			/**
			*	@brief Get an entity from a container entities.
			*	
			*	@param container Container containing entities (can by ptr or value).
			*	@param predicate Predicate defining valid entities.
			* 
			*	@return A pointer to the first entity matching the given predicate if any, else nullptr.
			* 
			*	@exception Any exception potentially thrown from the provided predicate.
			*/
			template <typename ContainerType, typename Predicate>
			RFK_NODISCARD static auto								getEntityByPredicate(ContainerType const&	container,
																						 Predicate				predicate)			-> typename std::remove_pointer_t<typename ContainerType::value_type> const*;

			/**
			*	@brief Get a list of all entities satisfying the given predicate.
			* 
			*	@param container Container containing entities (can by ptr or value).
			*	@param predicate Predicate defining valid entities.
			* 
			*	@return A list of all entities satisfying the given predicate.
			* 
			*	@exception Any exception potentially thrown from the provided predicate.
			*/
			template <typename ContainerType, typename Predicate>
			RFK_NODISCARD static auto								getEntitiesByPredicate(ContainerType const&		container,
																						   Predicate				predicate)		-> Vector<typename std::remove_pointer_t<typename ContainerType::value_type> const*>;

			/**
			*	@brief Retrieve an entity with the given name.
			* 
			*	@param container	Unordered_set like container that contains entity (or subclass) and implements the "find" method.
			*	@param name			Name of the entity to look for.
			*/
			template <typename ContainerType>
			RFK_NODISCARD static auto								getEntityByName(ContainerType const&	container,
																					char const*				name)		noexcept	-> typename std::remove_pointer_t<typename ContainerType::value_type> const*;

			/**
			*	@brief Get an element of a given name if it matches a predicate in an unordered_set like container.
			* 
			*	@param container	Unordered_set like container that contain entity (or subclass) and implements the "find" method.
			*	@param name			Name of the entity to look for.
			*	@param predicate	Predicate that defines if an entity matches or not. Prototype must be bool(EntityType const&).
			* 
			*	@return A pointer to the first matching entity if any was found, else nullptr.
			*/
			template <typename ContainerType, typename Predicate>
			RFK_NODISCARD static auto								getEntityByNameAndPredicate(ContainerType const&	container,
																								char const*				name,
																								Predicate				predicate)	-> typename std::remove_pointer_t<typename ContainerType::value_type> const*;

			/**
			*	@brief Get all elements that match the given name predicate.
			* 
			*	@param container	Unordered_multiset like container containing entities and implementing the "equal_range" method.
			*	@param name			Name of the entity to look for.
			*	@param predicate	Predicate that defines if an entity matches or not. Prototype must be bool(EntityType const&).
			* 
			*	@return A vector containing all elements that match the given name predicate.
			*/
			template <typename ContainerType, typename Predicate>
			RFK_NODISCARD static auto								getEntitiesByNameAndPredicate(ContainerType const&	container,
																								  char const*			name,
																								  Predicate				predicate)	-> Vector<typename std::remove_pointer_t<typename ContainerType::value_type> const*>;

			/**
			*	@brief Iterate over all entities named with the given name.
			* 
			*	@param container	Unordered_multiset like container containing entities and implementing the "equal_range" method.
			*	@param name			Name of the entities to iterate on.
			*	@param visitor		Visitor to call on each entity.
			* 
			*	@return The last visitor result before exiting the loop.
			*/
			template <typename ContainerType, typename Visitor>
			static bool												foreachEntityNamed(ContainerType const& container,
																					   char const*			name,
																					   Visitor				visitor);

			/**
			*	@brief Find an entity by Id in a container containing Entity* or derivate.
			* 
			*	@param container	Container containing entity pointers.
			*	@param id			Id to look for.
			* 
			*	@return The entity with the provided id if any, else nullptr
			*/
			template <typename ContainerType>
			RFK_NODISCARD static typename ContainerType::value_type	getEntityPtrById(ContainerType const&	container,
																					 std::size_t			id)							noexcept;
	};

	#include "Refureku/TypeInfo/Entity/EntityUtility.inl"
}