/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Entity/EntityImpl.h"
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
			*/
			template <typename EntityType, typename ContainerType>
			static bool											foreachEntity(ContainerType const&	container,
																			  Visitor<EntityType>	visitor,
																			  void*					userData)						noexcept;

			template <typename EntityType, typename ContainerType>
			static bool											foreachEntityPtr(ContainerType const&	container,
																				 Visitor<EntityType>	visitor,
																				 void*					userData)					noexcept;

			/**
			*	@brief Get an element of a given name if it matches a predicate in an unordered_set like container.
			* 
			*	@param container	Unordered_set like container that contains non-ptr entities. Must define the value_type type and the find method.
			*	@param name			Name of the entity to look for.
			*	@param predicate	Predicate that defines if an entity matches or not. Prototype must be bool(ContainerType::const_reference).
			* 
			*	@return A pointer to the first matching entity if any was found, else nullptr.
			*/
			template <typename ContainerType, typename Predicate>
			static typename ContainerType::value_type const*	getEntityByNameAndPredicate(ContainerType const& container,
																							char const*			 name,
																							Predicate			 predicate)			noexcept;

			/**
			*	@brief Get an element of a given name if it matches a predicate in an unordered_set like container.
			* 
			*	@param container	Unordered_set like container that contain entity (or subclass) pointers.
			*						Must define the value_type type and the find method, and contain pointers to entities or subclass.
			*	@param name			Name of the entity to look for.
			*	@param predicate	Predicate that defines if an entity matches or not. Prototype must be bool(ContainerType::value_type).
			* 
			*	@return A pointer to the first matching entity if any was found, else nullptr.
			*/
			template <typename ContainerType, typename Predicate>
			static typename ContainerType::value_type			getEntityPtrByNameAndPredicate(ContainerType const& container,
																							   char const*			name,
																							   Predicate			predicate)		noexcept;

			/**
			*	@brief Iterate over all entities named with the given name.
			*/
			template <typename ContainerType, typename Visitor>
			static bool											foreachEntityNamed(ContainerType const& container,
																				   char const*			name,
																				   Visitor				visitor);

			template <typename ContainerType, typename Visitor>
			static bool											foreachEntityPtrNamed(ContainerType const&	container,
																					  char const*			name,
																					  Visitor				visitor);

			/**
			*	@brief Find an entity by Id in a container containing EntityAPI*.
			*/
			template <typename ContainerType>
			static typename ContainerType::value_type			getEntityPtrById(ContainerType const&	container,
																				 std::size_t			id)							noexcept;
	};

	#include "Refureku/TypeInfo/Entity/EntityUtility.inl"
}