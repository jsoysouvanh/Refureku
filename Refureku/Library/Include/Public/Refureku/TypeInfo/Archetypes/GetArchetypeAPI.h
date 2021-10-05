/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <type_traits>	//std::is_function_v, std::is_member_object_pointer_v, std::is_pointer_v...

#include "Refureku/Config.h"
#include "Refureku/TypeInfo/Archetypes/EnumAPI.h"	//rfk::getEnum
#include "Refureku/Utility/TypeTraitsMacros.h"

namespace rfk
{
	RFK_GENERATE_IS_CALLABLE_METHOD_TRAITS(staticGetArchetype)

	/**
	*	@brief	Get the archetype of any type if it exists.
	*			Note that this method will always return nullptr on protected/private nested archetypes.
	*			If a cv-qualified, pointer/reference, array type is passed, they are all ignored and the raw type archetype is returned.
	*			Example:	int* -> int,
	*						int[2] -> int,
	*						const volatile int -> int,
	*						int& -> int
	*
	*			This templated method can be specialized to handle unreflected types.
	*
	*	@return The archetype of the provided type if it exists, else nullptr.
	*/
	template <typename T>
	ArchetypeAPI const* getArchetypeAPI() noexcept;

	/**
	*	@brief	Get archetype for template classes. Cover only most common cases.
	* 
	*	@return The archetype of the provided type if it exists, else nullptr.
	*/
	template <template <typename...> typename T>
	ArchetypeAPI const* getArchetypeAPI()	noexcept;								//Variadic type template parameters

	template <template <auto...> typename T>
	ArchetypeAPI const* getArchetypeAPI()	noexcept;								//Variadic non-type template parameters

	template <template <template <typename...> typename...> typename T>
	ArchetypeAPI const* getArchetypeAPI()	noexcept;								//Variadic template template type parameters

	template <template <typename, auto> typename T>
	ArchetypeAPI const* getArchetypeAPI()	noexcept;

	/**
	*	rfk::getArchetype specialization for all fundamental types.
	*/
	template <>
	REFUREKU_API ArchetypeAPI const* getArchetypeAPI<void>()				noexcept;

	template <>
	REFUREKU_API ArchetypeAPI const* getArchetypeAPI<std::nullptr_t>()		noexcept;

	template <>
	REFUREKU_API ArchetypeAPI const* getArchetypeAPI<bool>()				noexcept;

	template <>
	REFUREKU_API ArchetypeAPI const* getArchetypeAPI<char>()				noexcept;

	template <>
	REFUREKU_API ArchetypeAPI const* getArchetypeAPI<signed char>()			noexcept;

	template <>
	REFUREKU_API ArchetypeAPI const* getArchetypeAPI<unsigned char>()		noexcept;

	template <>
	REFUREKU_API ArchetypeAPI const* getArchetypeAPI<wchar_t>()				noexcept;

	template <>
	REFUREKU_API ArchetypeAPI const* getArchetypeAPI<char16_t>()			noexcept;

	template <>
	REFUREKU_API ArchetypeAPI const* getArchetypeAPI<char32_t>()			noexcept;

	template <>
	REFUREKU_API ArchetypeAPI const* getArchetypeAPI<short>()				noexcept;

	template <>
	REFUREKU_API ArchetypeAPI const* getArchetypeAPI<unsigned short>()		noexcept;

	template <>
	REFUREKU_API ArchetypeAPI const* getArchetypeAPI<int>()					noexcept;

	template <>
	REFUREKU_API ArchetypeAPI const* getArchetypeAPI<unsigned int>()		noexcept;

	template <>
	REFUREKU_API ArchetypeAPI const* getArchetypeAPI<long>()				noexcept;

	template <>
	REFUREKU_API ArchetypeAPI const* getArchetypeAPI<unsigned long>()		noexcept;

	template <>
	REFUREKU_API ArchetypeAPI const* getArchetypeAPI<long long>()			noexcept;

	template <>
	REFUREKU_API ArchetypeAPI const* getArchetypeAPI<unsigned long long>()	noexcept;

	template <>
	REFUREKU_API ArchetypeAPI const* getArchetypeAPI<float>()				noexcept;

	template <>
	REFUREKU_API ArchetypeAPI const* getArchetypeAPI<double>()				noexcept;

	template <>
	REFUREKU_API ArchetypeAPI const* getArchetypeAPI<long double>()			noexcept;

	#include "Refureku/TypeInfo/Archetypes/GetArchetypeAPI.inl"
}