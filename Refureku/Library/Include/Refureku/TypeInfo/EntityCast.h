/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <type_traits>

#include "Refureku/TypeInfo/Entity.h"
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
	T const*					entityCast(Entity const* entity)								noexcept;

	/**
	*	rfk::entityCast<> specialization for all Entity types.
	*/
	template <>
	Archetype const*			entityCast<Archetype, void>(Entity const* entity)				noexcept;

	template <>
	FundamentalArchetype const* entityCast<FundamentalArchetype, void>(Entity const* entity)	noexcept;

	template <>
	Struct const*				entityCast<Struct, void>(Entity const* entity)					noexcept;

	template <>
	Class const*				entityCast<Class, void>(Entity const* entity)					noexcept;

	template <>
	FieldBase const*			entityCast<FieldBase, void>(Entity const* entity)				noexcept;

	template <>
	Field const*				entityCast<Field, void>(Entity const* entity)					noexcept;

	template <>
	StaticField const*			entityCast<StaticField, void>(Entity const* entity)				noexcept;

	template <>
	MethodBase const*			entityCast<MethodBase, void>(Entity const* entity)				noexcept;

	template <>
	Method const*				entityCast<Method, void>(Entity const* entity)					noexcept;

	template <>
	StaticMethod const*			entityCast<StaticMethod, void>(Entity const* entity)			noexcept;

	template <>
	Enum const*					entityCast<Enum, void>(Entity const* entity)					noexcept;

	template <>
	EnumValue const*			entityCast<EnumValue, void>(Entity const* entity)				noexcept;

	template <>
	Namespace const*			entityCast<Namespace, void>(Entity const* entity)				noexcept;

	template <>
	Variable const*				entityCast<Variable, void>(Entity const* entity)				noexcept;

	template <>
	Function const*				entityCast<Function, void>(Entity const* entity)				noexcept;

	#include "Refureku/TypeInfo/EntityCast.inl"
}