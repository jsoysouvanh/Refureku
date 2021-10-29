/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Entity/Entity.h"

namespace rfk
{
	//Forward declarations
	class Archetype;
	class FundamentalArchetype;
	class Struct;
	using Class = Struct;
	class ClassTemplate;
	using StructTemplate = ClassTemplate;
	class ClassTemplateInstantiation;
	using StructTemplateInstantiation = ClassTemplateInstantiation;
	class Enum;
	class EnumValue;
	class Namespace;
	class Field;
	class StaticField;
	class Method;
	class StaticMethod;
	class Variable;
	class Function;

	/**
	*	@brief Try to cast a rfk::Entity to rfk::Archetype.
	* 
	*	@param entity The entity to cast.
	* 
	*	@return A non-nullptr pointer to rfk::Archetype if entity is an archetype, else nullptr.
	*/
	RFK_NODISCARD REFUREKU_API
		Archetype const*					archetypeCast(Entity const* entity)						noexcept;

	/**
	*	@brief Try to cast a rfk::Entity to rfk::FundamentalType.
	* 
	*	@param entity The entity to cast.
	* 
	*	@return A non-nullptr pointer to rfk::FundamentalType if entity is a fundamental archetype, else nullptr.
	*/
	RFK_NODISCARD REFUREKU_API
		FundamentalArchetype const*			fundamentalArchetypeCast(Entity const* entity)			noexcept;

	/**
	*	@brief Try to cast a rfk::Entity to rfk::Struct.
	* 
	*	@param entity The entity to cast.
	* 
	*	@return A non-nullptr pointer to rfk::Struct if entity is a struct, else nullptr.
	*/
	RFK_NODISCARD REFUREKU_API
		Struct const*						structCast(Entity const* entity)						noexcept;

	/**
	*	@brief Try to cast a rfk::Entity to rfk::StructTemplate.
	* 
	*	@param entity The entity to cast.
	* 
	*	@return A non-nullptr pointer to rfk::StructTemplate if entity is a struct template, else nullptr.
	*/
	RFK_NODISCARD REFUREKU_API
		StructTemplate const*				structTemplateCast(Entity const* entity)				noexcept;

	/**
	*	@brief Try to cast a rfk::Entity to rfk::StructTemplateInstantiation.
	* 
	*	@param entity The entity to cast.
	* 
	*	@return A non-nullptr pointer to rfk::StructTemplateInstantiation if entity is a struct template instantiation, else nullptr.
	*/
	RFK_NODISCARD REFUREKU_API
		StructTemplateInstantiation const*	structTemplateInstantiationCast(Entity const* entity)	noexcept;

	/**
	*	@brief Try to cast a rfk::Entity to rfk::Class.
	* 
	*	@param entity The entity to cast.
	* 
	*	@return A non-nullptr pointer to rfk::Class if entity is a class, else nullptr.
	*/
	RFK_NODISCARD REFUREKU_API
		Class const*						classCast(Entity const* entity)							noexcept;

	/**
	*	@brief Try to cast a rfk::Entity to rfk::ClassTemplate.
	* 
	*	@param entity The entity to cast.
	* 
	*	@return A non-nullptr pointer to rfk::ClassTemplate if entity is a class template, else nullptr.
	*/
	RFK_NODISCARD REFUREKU_API
		ClassTemplate const*				classTemplateCast(Entity const* entity)					noexcept;

	/**
	*	@brief Try to cast a rfk::Entity to rfk::ClassTemplateInstantiation.
	* 
	*	@param entity The entity to cast.
	* 
	*	@return A non-nullptr pointer to rfk::ClassTemplateInstantiation if entity is a class template instantiation, else nullptr.
	*/
	RFK_NODISCARD REFUREKU_API
		ClassTemplateInstantiation const*	classTemplateInstantiationCast(Entity const* entity)	noexcept;

	/**
	*	@brief Try to cast a rfk::Entity to rfk::Field.
	* 
	*	@param entity The entity to cast.
	* 
	*	@return A non-nullptr pointer to rfk::Field if entity is a field, else nullptr.
	*/
	RFK_NODISCARD REFUREKU_API
		Field const*						fieldCast(Entity const* entity)							noexcept;

	/**
	*	@brief Try to cast a rfk::Entity to rfk::StaticField.
	* 
	*	@param entity The entity to cast.
	* 
	*	@return A non-nullptr pointer to rfk::StaticField if entity is a static field, else nullptr.
	*/
	RFK_NODISCARD REFUREKU_API
		StaticField const*					staticFieldCast(Entity const* entity)					noexcept;

	/**
	*	@brief Try to cast a rfk::Entity to rfk::Method.
	* 
	*	@param entity The entity to cast.
	* 
	*	@return A non-nullptr pointer to rfk::Method if entity is a method, else nullptr.
	*/
	RFK_NODISCARD REFUREKU_API
		Method const*						methodCast(Entity const* entity)						noexcept;

	/**
	*	@brief Try to cast a rfk::Entity to rfk::StaticMethod.
	* 
	*	@param entity The entity to cast.
	* 
	*	@return A non-nullptr pointer to rfk::StaticMethod if entity is a static method, else nullptr.
	*/
	RFK_NODISCARD REFUREKU_API
		StaticMethod const*					staticMethodCast(Entity const* entity)					noexcept;

	/**
	*	@brief Try to cast a rfk::Entity to rfk::Enum.
	* 
	*	@param entity The entity to cast.
	* 
	*	@return A non-nullptr pointer to rfk::Enum if entity is an enum or enum class, else nullptr.
	*/
	RFK_NODISCARD REFUREKU_API
		Enum const*							enumCast(Entity const* entity)							noexcept;

	/**
	*	@brief Try to cast a rfk::Entity to rfk::EnumValue.
	* 
	*	@param entity The entity to cast.
	* 
	*	@return A non-nullptr pointer to rfk::EnumValue if entity is an enum value, else nullptr.
	*/
	RFK_NODISCARD REFUREKU_API
		EnumValue const*					enumValueCast(Entity const* entity)						noexcept;

	/**
	*	@brief Try to cast a rfk::Entity to rfk::Namespace.
	* 
	*	@param entity The entity to cast.
	* 
	*	@return A non-nullptr pointer to rfk::Namespace if entity is a namespace, else nullptr.
	*/
	RFK_NODISCARD REFUREKU_API
		Namespace const*					namespaceCast(Entity const* entity)						noexcept;

	/**
	*	@brief Try to cast a rfk::Entity to rfk::Variable.
	* 
	*	@param entity The entity to cast.
	* 
	*	@return A non-nullptr pointer to rfk::Variable if entity is a variable, else nullptr.
	*/
	RFK_NODISCARD REFUREKU_API
		Variable const*						variableCast(Entity const* entity)						noexcept;

	/**
	*	@brief Try to cast a rfk::Entity to rfk::Function.
	* 
	*	@param entity The entity to cast.
	* 
	*	@return A non-nullptr pointer to rfk::Function if entity is a function, else nullptr.
	*/
	RFK_NODISCARD REFUREKU_API
		Function const*						functionCast(Entity const* entity)						noexcept;
}