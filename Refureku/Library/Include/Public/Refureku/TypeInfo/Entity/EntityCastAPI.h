/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <type_traits>	//std::enable_if_t

#include "Refureku/TypeInfo/Entity/Entity.h"

namespace rfk
{
	//Forward declarations
	class ArchetypeAPI;
	class NamespaceAPI;

	namespace internal
	{
		template <typename T>
		using isValidEntityType = std::enable_if_t<std::is_base_of_v<EntityAPI, T>>;

		/**
		*	@brief Helper function to cast simple entity types.
		*
		*	@tparam T Concrete type to cast to.
		*
		*	@param entity The entity to cast.
		*	
		*	@return The casted entity if the entity concrete type was correct, else nullptr.
		*/
		template <typename T, EEntityKind CheckKind, typename = isValidEntityType<T>>
		T const* entityCast(EntityAPI const* entity) noexcept;
	}

	/**
	*	@brief Try to cast this entity to the specified concrete type if possible.
	*
	*	@tparam T Concrete entity type to cast to.
	*	
	*	@return The casted entity if the provided type matched the concrete entity type, else nullptr.
	*/
	template <typename T, typename = internal::isValidEntityType<T>>
	T const*									entityCast(EntityAPI const* entity)									noexcept;

	/**
	*	rfk::entityCast<> specialization for all Entity types.
	*/
	template <>
	REFUREKU_API ArchetypeAPI const*			entityCast<ArchetypeAPI, void>(EntityAPI const* entity)				noexcept;

	//template <>
	//REFUREKU_API FundamentalArchetypeAPI const*	entityCast<FundamentalArchetypeAPI, void>(EntityAPI const* entity)	noexcept;	//TODO

	template <>
	REFUREKU_API NamespaceAPI const*			entityCast<NamespaceAPI, void>(EntityAPI const* entity)				noexcept;

	#include "Refureku/TypeInfo/Entity/EntityCastAPI.inl"
}