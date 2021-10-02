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
	class FundamentalArchetypeAPI;
	class StructAPI;
	class EnumAPI;
	class EnumValueAPI;
	class NamespaceAPI;
	class FieldBaseAPI;
	class FieldAPI;
	class StaticFieldAPI;
	class MethodBaseAPI;
	class MethodAPI;
	class StaticMethodAPI;
	class VariableAPI;
	class FunctionAPI;

	namespace internal
	{
		template <typename T>
		using isValidEntityType = std::enable_if_t<std::is_base_of_v<EntityAPI, T>>;
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
	REFUREKU_API StructAPI const*				entityCast<StructAPI, void>(EntityAPI const* entity)				noexcept;

	template <>
	REFUREKU_API FieldBaseAPI const*			entityCast<FieldBaseAPI, void>(EntityAPI const* entity)				noexcept;

	template <>
	REFUREKU_API FieldAPI const*				entityCast<FieldAPI, void>(EntityAPI const* entity)					noexcept;

	template <>
	REFUREKU_API StaticFieldAPI const*			entityCast<StaticFieldAPI, void>(EntityAPI const* entity)			noexcept;

	template <>
	REFUREKU_API MethodBaseAPI const*			entityCast<MethodBaseAPI, void>(EntityAPI const* entity)			noexcept;

	template <>
	REFUREKU_API MethodAPI const*				entityCast<MethodAPI, void>(EntityAPI const* entity)				noexcept;

	template <>
	REFUREKU_API StaticMethodAPI const*			entityCast<StaticMethodAPI, void>(EntityAPI const* entity)			noexcept;

	template <>
	REFUREKU_API EnumAPI const*					entityCast<EnumAPI, void>(EntityAPI const* entity)					noexcept;

	template <>
	REFUREKU_API EnumValueAPI const*			entityCast<EnumValueAPI, void>(EntityAPI const* entity)				noexcept;

	template <>
	REFUREKU_API NamespaceAPI const*			entityCast<NamespaceAPI, void>(EntityAPI const* entity)				noexcept;

	template <>
	REFUREKU_API VariableAPI const*				entityCast<VariableAPI, void>(EntityAPI const* entity)				noexcept;

	template <>
	REFUREKU_API FunctionAPI const*				entityCast<FunctionAPI, void>(EntityAPI const* entity)				noexcept;
}