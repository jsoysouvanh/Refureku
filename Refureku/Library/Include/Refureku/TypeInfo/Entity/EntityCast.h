/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <type_traits>

#include "Refureku/Config.h"
#include "Refureku/TypeInfo/Entity/Entity.h"
#include "Refureku/TypeInfo/Variables/Variable.h"
#include "Refureku/TypeInfo/Variables/Field.h"
#include "Refureku/TypeInfo/Variables/StaticField.h"
#include "Refureku/TypeInfo/Functions/Function.h"
#include "Refureku/TypeInfo/Functions/Method.h"
#include "Refureku/TypeInfo/Functions/StaticMethod.h"
#include "Refureku/TypeInfo/Archetypes/Class.h"
#include "Refureku/TypeInfo/Archetypes/Enum.h"
#include "Refureku/TypeInfo/Archetypes/EnumValue.h"
#include "Refureku/TypeInfo/Archetypes/FundamentalArchetype.h"
#include "Refureku/TypeInfo/Namespaces/Namespace.h"

namespace rfk
{
	namespace internal
	{
		template <typename T>
		using isValidEntityType = std::enable_if_t<std::is_base_of_v<Entity, T>>;

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
		T const* entityCast(Entity const* entity) noexcept;
	}

	/**
	*	@brief Try to cast this entity to the specified concrete type if possible.
	*
	*	@tparam T Concrete entity type to cast to.
	*	
	*	@return The casted entity if the provided type matched the concrete entity type, else nullptr.
	*/
	template <typename T, typename = internal::isValidEntityType<T>>
	T const*	entityCast(Entity const* entity)	noexcept;

	/**
	*	rfk::entityCast<> specialization for all Entity types.
	*/
	template <>
	REFUREKU_API Archetype const*				entityCast<Archetype, void>(Entity const* entity)				noexcept;

	template <>
	REFUREKU_API FundamentalArchetype const*	entityCast<FundamentalArchetype, void>(Entity const* entity)	noexcept;

	/**
	*	This entity cast specialization doesn't work to check if an entity is a class (it will return a non-nullptr pointer when it is a struct as well).
	*	Make sure to check if the result's kind is EEntityKind::Class.
	*/
	template <>
	REFUREKU_API Struct const*					entityCast<Struct, void>(Entity const* entity)					noexcept;

	template <>
	REFUREKU_API FieldBase const*				entityCast<FieldBase, void>(Entity const* entity)				noexcept;

	template <>
	REFUREKU_API Field const*					entityCast<Field, void>(Entity const* entity)					noexcept;

	template <>
	REFUREKU_API StaticField const*				entityCast<StaticField, void>(Entity const* entity)				noexcept;

	template <>
	REFUREKU_API MethodBase const*				entityCast<MethodBase, void>(Entity const* entity)				noexcept;

	template <>
	REFUREKU_API Method const*					entityCast<Method, void>(Entity const* entity)					noexcept;

	template <>
	REFUREKU_API StaticMethod const*			entityCast<StaticMethod, void>(Entity const* entity)			noexcept;

	template <>
	REFUREKU_API Enum const*					entityCast<Enum, void>(Entity const* entity)					noexcept;

	template <>
	REFUREKU_API EnumValue const*				entityCast<EnumValue, void>(Entity const* entity)				noexcept;

	template <>
	REFUREKU_API Namespace const*				entityCast<Namespace, void>(Entity const* entity)				noexcept;

	template <>
	REFUREKU_API Variable const*				entityCast<Variable, void>(Entity const* entity)				noexcept;

	template <>
	REFUREKU_API Function const*				entityCast<Function, void>(Entity const* entity)				noexcept;

	#include "Refureku/TypeInfo/Entity/EntityCast.inl"
}