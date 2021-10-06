/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

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

	/**
	*	@brief Try to cast this entity to the specified concrete type if possible.
	*
	*	@tparam T Concrete entity type to cast to.
	*	
	*	@return The casted entity if the provided type matched the concrete entity type, else nullptr.
	*/
	template <typename T>
	T const*									entityCast(Entity const* entity)								noexcept;

	/**
	*	rfk::entityCast<> specialization for all Entity types.
	*/
	template <>
	REFUREKU_API ArchetypeAPI const*			entityCast<ArchetypeAPI>(Entity const* entity)				noexcept;

	template <>
	REFUREKU_API FundamentalArchetypeAPI const*	entityCast<FundamentalArchetypeAPI>(Entity const* entity)	noexcept;

	template <>
	REFUREKU_API StructAPI const*				entityCast<StructAPI>(Entity const* entity)					noexcept;

	template <>
	REFUREKU_API FieldBaseAPI const*			entityCast<FieldBaseAPI>(Entity const* entity)				noexcept;

	template <>
	REFUREKU_API FieldAPI const*				entityCast<FieldAPI>(Entity const* entity)					noexcept;

	template <>
	REFUREKU_API StaticFieldAPI const*			entityCast<StaticFieldAPI>(Entity const* entity)				noexcept;

	template <>
	REFUREKU_API MethodBaseAPI const*			entityCast<MethodBaseAPI>(Entity const* entity)				noexcept;

	template <>
	REFUREKU_API MethodAPI const*				entityCast<MethodAPI>(Entity const* entity)					noexcept;

	template <>
	REFUREKU_API StaticMethodAPI const*			entityCast<StaticMethodAPI>(Entity const* entity)			noexcept;

	template <>
	REFUREKU_API EnumAPI const*					entityCast<EnumAPI>(Entity const* entity)					noexcept;

	template <>
	REFUREKU_API EnumValueAPI const*			entityCast<EnumValueAPI>(Entity const* entity)				noexcept;

	template <>
	REFUREKU_API NamespaceAPI const*			entityCast<NamespaceAPI>(Entity const* entity)				noexcept;

	template <>
	REFUREKU_API VariableAPI const*				entityCast<VariableAPI>(Entity const* entity)				noexcept;

	template <>
	REFUREKU_API FunctionAPI const*				entityCast<FunctionAPI>(Entity const* entity)				noexcept;
}