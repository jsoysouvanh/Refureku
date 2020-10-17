/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <cstddef>
#include <string>
#include <functional>	//std::hash

#include "Refureku/TypeInfo/Archetypes/Archetype.h"

namespace rfk
{
	class FundamentalArchetype final : public Archetype
	{
		public:
			FundamentalArchetype()								= delete;
			FundamentalArchetype(std::string&&	name,
								 uint64			id,
								 uint64			memorySize)		noexcept;
			FundamentalArchetype(FundamentalArchetype const&)	= delete;
			FundamentalArchetype(FundamentalArchetype&&)		= delete;
			~FundamentalArchetype()								= default;
	};

	/**
	*	rfk::getArchetype specialization for all fundamental types.
	*/
	template <>
	rfk::Archetype const* getArchetype<void>()					noexcept;
	
	template <>
	rfk::Archetype const* getArchetype<nullptr_t>()				noexcept;
	
	template <>
	rfk::Archetype const* getArchetype<bool>()					noexcept;
	
	template <>
	rfk::Archetype const* getArchetype<char>()					noexcept;
	
	template <>
	rfk::Archetype const* getArchetype<signed char>()			noexcept;
	
	template <>
	rfk::Archetype const* getArchetype<unsigned char>()			noexcept;
	
	template <>
	rfk::Archetype const* getArchetype<wchar_t>()				noexcept;
	
	template <>
	rfk::Archetype const* getArchetype<char16_t>()				noexcept;
	
	template <>
	rfk::Archetype const* getArchetype<char32_t>()				noexcept;
	
	template <>
	rfk::Archetype const* getArchetype<short>()					noexcept;
	
	template <>
	rfk::Archetype const* getArchetype<unsigned short>()		noexcept;
	
	template <>
	rfk::Archetype const* getArchetype<int>()					noexcept;
	
	template <>
	rfk::Archetype const* getArchetype<unsigned int>()			noexcept;
	
	template <>
	rfk::Archetype const* getArchetype<long>()					noexcept;
	
	template <>
	rfk::Archetype const* getArchetype<unsigned long>()			noexcept;
	
	template <>
	rfk::Archetype const* getArchetype<long long>()				noexcept;
	
	template <>
	rfk::Archetype const* getArchetype<unsigned long long>()	noexcept;
	
	template <>
	rfk::Archetype const* getArchetype<float>()					noexcept;
	
	template <>
	rfk::Archetype const* getArchetype<double>()				noexcept;
	
	template <>
	rfk::Archetype const* getArchetype<long double>()			noexcept;
}