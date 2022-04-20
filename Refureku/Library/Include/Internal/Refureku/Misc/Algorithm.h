/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include <type_traits>

#include "Refureku/TypeInfo/Entity/EntityImpl.h"
#include "Refureku/Containers/Vector.h"
#include "Refureku/Misc/Visitor.h"
#include "Refureku/Misc/Predicate.h"

namespace rfk
{
	class Algorithm
	{
		public:
			Algorithm()		= delete;
			~Algorithm()	= delete;

			/**
			*	@brief Execute the given visitor on all items of the container.
			*
			*	@param container Container containing all the items the visitor should run on.
			*	@param visitor	 Visitor function to call. Return false to abort the foreach loop.
			*	@param userData	 Optional user data forwarded to the visitor.
			* 
			*	@return	The last visitor result before exiting the loop.
			*			If the visitor is nullptr, return false.
			* 
			*	@exception Any exception potentially thrown from the provided visitor.
			*/
			template <typename ItemType, typename ContainerType>
			static bool												foreach(ContainerType const&	container,
																			Visitor<ItemType>		visitor,
																			void*					userData);

			template <typename ContainerType, typename Visitor>
			static bool												foreach(ContainerType const&	container,
																			Visitor					visitor);

			/**
			*	@brief Get an item in a container from a predicate.
			*	
			*	@param container Container containing items (can by ptr or value).
			*	@param predicate Predicate defining valid item.
			* 
			*	@return A pointer to the first item matching the given predicate if any, else nullptr.
			* 
			*	@exception Any exception potentially thrown from the provided predicate.
			*/
			template <typename ContainerType, typename Predicate>
			RFK_NODISCARD static auto								getItemByPredicate(ContainerType const&	container,
																					   Predicate			predicate)			-> typename std::remove_pointer_t<typename ContainerType::value_type> const*;
			
			template <typename ItemType, typename ContainerType>
			RFK_NODISCARD static ItemType const*					getItemByPredicate(ContainerType const&	container,
																					   Predicate<ItemType>	predicate,
																					   void*				userData);


			/**
			*	@brief Get a list of all items satisfying the given predicate.
			* 
			*	@param container Container containing items (can be ptr or value).
			*	@param predicate Predicate defining valid items.
			* 
			*	@return A list of all items satisfying the given predicate.
			* 
			*	@exception Any exception potentially thrown from the provided predicate.
			*/
			template <typename ContainerType, typename Predicate>
			RFK_NODISCARD static auto								getItemsByPredicate(ContainerType const&	container,
																						Predicate				predicate)		-> Vector<typename std::remove_pointer_t<typename ContainerType::value_type> const*>;

			template <typename ItemType, typename ContainerType>
			RFK_NODISCARD static Vector<ItemType const*>			getItemsByPredicate(ContainerType const&	container,
																						Predicate<ItemType>		predicate,
																						void*					userData);

			/**
			*	@brief Get a sorted (ascending) list of all items satisfying the given predicate.
			* 
			*	@param container Container containing items (can be ptr or value).
			*	@param predicate Predicate defining valid items.
			*	@param compare	 Method used to compare elements. It must have the following signature: bool (*)(Item const& a, Item const& b);
			*					 The compare method must return true when a < b (ordered before b in the result).
			* 
			*	@return A sorted list of all items satisfying the given predicate.
			* 
			*	@exception Any exception potentially thrown from the provided predicate.
			*/
			template <typename ContainerType, typename Predicate, typename Compare>
			RFK_NODISCARD static auto								getSortedItemsByPredicate(ContainerType const&	container,
																							  Predicate				predicate,
																							  Compare				compare)	-> Vector<typename std::remove_pointer_t<typename ContainerType::value_type> const*>;

			/**
			*	@brief Retrieve an entity with the given name.
			* 
			*	@param container	Unordered_set like container that contains entity (or subclass) and implements the "find" method.
			*	@param name			Name of the entity to look for.
			* 
			*	@return The entity that has the given name from the container if any, else nullptr.
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

			/**
			*	@brief Return the index of the first element that is greater than the provided element in the container.
			* 
			*	@param container	Container containing the elements. It must be accessible by index (operator[index]) and implement the size() method.
			*	@param element		Element to compare with.
			*	@param compare		Method used to compare elements. It must have the following signature: bool (*)(Item const& a, Item const& b);
			*						The compare method must return true when a < b (ordered before b in the result).
			* 
			*	@return The index of the first element greater than the provided element, or container.size() if no element is greater than the provided element.
			* 
			*	@exception Any exception potentially thrown by the Compare 
			*/
			template <typename ContainerType, typename Compare,
					  typename ElementType = typename ContainerType::const_reference,
					  typename = std::enable_if_t<std::is_invocable_r_v<bool, Compare, typename ContainerType::const_reference, typename ContainerType::const_reference>>>
			RFK_NODISCARD static std::size_t						getFirstGreaterElementIndex(ContainerType const&	container,
																								ElementType				element,
																								Compare					compare)		noexcept(noexcept(compare));
	};

	#include "Refureku/Misc/Algorithm.inl"
}