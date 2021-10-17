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
	class Archetype;
	class FundamentalArchetype;
	class Struct;
	class ClassTemplate;
	class ClassTemplateInstantiation;
	class Enum;
	class EnumValue;
	class Namespace;
	class FieldBase;
	class Field;
	class StaticField;
	class MethodBase;
	class Method;
	class StaticMethod;
	class Variable;
	class Function;

	/**
	*	@brief Try to cast this entity to the specified concrete type if possible.
	*
	*	@tparam T Concrete entity type to cast to.
	*	
	*	@return The casted entity if the provided type matched the concrete entity type, else nullptr.
	*/
	template <typename T>
	RFK_NODISCARD T const*											entityCast(Entity const* entity)								noexcept;

	/**
	*	rfk::entityCast<> specialization for all Entity types.
	*/
	template <>
	RFK_NODISCARD REFUREKU_API Archetype const*						entityCast<Archetype>(Entity const* entity)						noexcept;

	template <>
	RFK_NODISCARD REFUREKU_API FundamentalArchetype const*			entityCast<FundamentalArchetype>(Entity const* entity)			noexcept;

	/**
	*	This entity cast specialization doesn't differentiate structs and classes since they have the same static type.
	*	Make sure to check if the result's kind is EEntityKind::Struct or EEntityKind::Class.
	*/
	template <>
	RFK_NODISCARD REFUREKU_API Struct const*						entityCast<Struct>(Entity const* entity)						noexcept;

	/**
	*	This entity cast specialization doesn't differentiate structs and classes since they have the same static type.
	*	Make sure to check if the result's kind is EEntityKind::Struct or EEntityKind::Class.
	*/
	template <>
	RFK_NODISCARD REFUREKU_API ClassTemplate const*					entityCast<ClassTemplate>(Entity const* entity)					noexcept;

	/**
	*	This entity cast specialization doesn't differentiate structs and classes since they have the same static type.
	*	Make sure to check if the result's kind is EEntityKind::Struct or EEntityKind::Class.
	*/
	template <>
	RFK_NODISCARD REFUREKU_API ClassTemplateInstantiation const*	entityCast<ClassTemplateInstantiation>(Entity const* entity)	noexcept;

	template <>
	RFK_NODISCARD REFUREKU_API FieldBase const*						entityCast<FieldBase>(Entity const* entity)						noexcept;

	template <>	
	RFK_NODISCARD REFUREKU_API Field const*							entityCast<Field>(Entity const* entity)							noexcept;

	template <>
	RFK_NODISCARD REFUREKU_API StaticField const*					entityCast<StaticField>(Entity const* entity)					noexcept;

	template <>
	RFK_NODISCARD REFUREKU_API MethodBase const*					entityCast<MethodBase>(Entity const* entity)					noexcept;

	template <>
	RFK_NODISCARD REFUREKU_API Method const*						entityCast<Method>(Entity const* entity)						noexcept;

	template <>
	RFK_NODISCARD REFUREKU_API StaticMethod const*					entityCast<StaticMethod>(Entity const* entity)					noexcept;

	template <>
	RFK_NODISCARD REFUREKU_API Enum const*							entityCast<Enum>(Entity const* entity)							noexcept;

	template <>
	RFK_NODISCARD REFUREKU_API EnumValue const*						entityCast<EnumValue>(Entity const* entity)						noexcept;

	template <>
	RFK_NODISCARD REFUREKU_API Namespace const*						entityCast<Namespace>(Entity const* entity)						noexcept;

	template <>
	RFK_NODISCARD REFUREKU_API Variable const*						entityCast<Variable>(Entity const* entity)						noexcept;

	template <>
	RFK_NODISCARD REFUREKU_API Function const*						entityCast<Function>(Entity const* entity)						noexcept;
}