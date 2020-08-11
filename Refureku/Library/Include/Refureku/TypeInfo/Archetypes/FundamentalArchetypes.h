/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <functional>
#include <string>
#include <cstddef>

#include "Refureku/Misc/FundamentalTypes.h"
#include "Refureku/TypeInfo/Archetypes/FundamentalArchetype.h"

namespace rfk
{
	class FundamentalArchetypes
	{
		private:
			static inline std::hash<std::string>	stringHasher;

		public:
			FundamentalArchetypes()								= delete;
			FundamentalArchetypes(FundamentalArchetypes const&) = delete;
			FundamentalArchetypes(FundamentalArchetypes&&)		= delete;
			~FundamentalArchetypes()							= delete;

			static FundamentalArchetype const& getVoidArchetype() noexcept
			{
				static FundamentalArchetype archetype("void", stringHasher("void"), 0u);

				return archetype;
			}

			static FundamentalArchetype const& getNullptrArchetype() noexcept
			{
				static FundamentalArchetype	archetype("nullptr_t", stringHasher("nullptr_t"), sizeof(std::nullptr_t));

				return archetype;
			}

			static FundamentalArchetype const& getBoolArchetype() noexcept
			{
				static FundamentalArchetype	archetype("bool", stringHasher("bool"), sizeof(bool));

				return archetype;
			}

			static FundamentalArchetype const& getCharArchetype() noexcept
			{
				static FundamentalArchetype	archetype("char", stringHasher("char"), sizeof(char));

				return archetype;
			}

			static FundamentalArchetype const& getSignedCharArchetype() noexcept
			{
				static FundamentalArchetype	archetype("signed char", stringHasher("signed char"), sizeof(signed char));

				return archetype;
			}

			static FundamentalArchetype const& getUnsignedCharArchetype() noexcept
			{
				static FundamentalArchetype	archetype("unsigned char", stringHasher("unsigned char"), sizeof(unsigned char));

				return archetype;
			}

			static FundamentalArchetype const& getWideCharArchetype() noexcept
			{
				static FundamentalArchetype	archetype("wide char", stringHasher("wide char"), sizeof(wchar_t));

				return archetype;
			}

			static FundamentalArchetype const& getChar16Archetype() noexcept
			{
				static FundamentalArchetype	archetype("char16", stringHasher("char16"), sizeof(char16_t));

				return archetype;
			}

			static FundamentalArchetype const& getChar32Archetype() noexcept
			{
				static FundamentalArchetype	archetype("char32", stringHasher("char32"), sizeof(char32_t));

				return archetype;
			}

			static FundamentalArchetype const& getShortArchetype() noexcept
			{
				static FundamentalArchetype	archetype("short", stringHasher("short"), sizeof(short));

				return archetype;
			}

			static FundamentalArchetype const& getUnsignedShortArchetype() noexcept
			{
				static FundamentalArchetype	archetype("unsigned short", stringHasher("unsigned short"), sizeof(unsigned short));

				return archetype;
			}

			static FundamentalArchetype const& getIntArchetype() noexcept
			{
				static FundamentalArchetype	archetype("int", stringHasher("int"), sizeof(int));

				return archetype;
			}

			static FundamentalArchetype const& getUnsignedIntArchetype() noexcept
			{
				static FundamentalArchetype	archetype("unsigned int", stringHasher("unsigned int"), sizeof(unsigned int));

				return archetype;
			}

			static FundamentalArchetype const& getLongArchetype() noexcept
			{
				static FundamentalArchetype	archetype("long", stringHasher("long"), sizeof(long));

				return archetype;
			}

			static FundamentalArchetype const& getUnsignedLongArchetype() noexcept
			{
				static FundamentalArchetype	archetype("unsigned long", stringHasher("unsigned long"), sizeof(unsigned long));

				return archetype;
			}

			static FundamentalArchetype const& getLongLongArchetype() noexcept
			{
				static FundamentalArchetype	archetype("long long", stringHasher("long long"), sizeof(long long));

				return archetype;
			}

			static FundamentalArchetype const& getUnsignedLongLongArchetype() noexcept
			{
				static FundamentalArchetype	archetype("unsigned long long", stringHasher("unsigned long long"), sizeof(unsigned long long));

				return archetype;
			}

			static FundamentalArchetype const& getFloatArchetype() noexcept
			{
				static FundamentalArchetype	archetype("float", stringHasher("float"), sizeof(float));

				return archetype;
			}

			static FundamentalArchetype const& getDoubleArchetype() noexcept
			{
				static FundamentalArchetype	archetype("double", stringHasher("double"), sizeof(double));

				return archetype;
			}

			static FundamentalArchetype const& getLongDoubleArchetype() noexcept
			{
				static FundamentalArchetype	archetype("long double", stringHasher("long double"), sizeof(long double));

				return archetype;
			}
	};
}