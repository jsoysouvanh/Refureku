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
	T const*									entityCast(EntityAPI const* entity)								noexcept;

	/**
	*	rfk::entityCast<> specialization for all Entity types.
	*/
	template <>
	REFUREKU_API ArchetypeAPI const*			entityCast<ArchetypeAPI>(EntityAPI const* entity)				noexcept;

	template <>
	REFUREKU_API FundamentalArchetypeAPI const*	entityCast<FundamentalArchetypeAPI>(EntityAPI const* entity)	noexcept;

	template <>
	REFUREKU_API StructAPI const*				entityCast<StructAPI>(EntityAPI const* entity)					noexcept;

	template <>
	REFUREKU_API FieldBaseAPI const*			entityCast<FieldBaseAPI>(EntityAPI const* entity)				noexcept;

	template <>
	REFUREKU_API FieldAPI const*				entityCast<FieldAPI>(EntityAPI const* entity)					noexcept;

	template <>
	REFUREKU_API StaticFieldAPI const*			entityCast<StaticFieldAPI>(EntityAPI const* entity)				noexcept;

	template <>
	REFUREKU_API MethodBaseAPI const*			entityCast<MethodBaseAPI>(EntityAPI const* entity)				noexcept;

	template <>
	REFUREKU_API MethodAPI const*				entityCast<MethodAPI>(EntityAPI const* entity)					noexcept;

	template <>
	REFUREKU_API StaticMethodAPI const*			entityCast<StaticMethodAPI>(EntityAPI const* entity)			noexcept;

	template <>
	REFUREKU_API EnumAPI const*					entityCast<EnumAPI>(EntityAPI const* entity)					noexcept;

	template <>
	REFUREKU_API EnumValueAPI const*			entityCast<EnumValueAPI>(EntityAPI const* entity)				noexcept;

	template <>
	REFUREKU_API NamespaceAPI const*			entityCast<NamespaceAPI>(EntityAPI const* entity)				noexcept;

	template <>
	REFUREKU_API VariableAPI const*				entityCast<VariableAPI>(EntityAPI const* entity)				noexcept;

	template <>
	REFUREKU_API FunctionAPI const*				entityCast<FunctionAPI>(EntityAPI const* entity)				noexcept;
}