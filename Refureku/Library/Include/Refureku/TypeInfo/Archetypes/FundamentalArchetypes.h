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
#include "Refureku/TypeInfo/Archetypes/Archetype.h"

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

			static Archetype const& getVoidArchetype() noexcept
			{
				static Archetype archetype("void", stringHasher("void"), Entity::EKind::FundamentalArchetype, 0u);

				return archetype;
			}

			static Archetype const& getNullptrArchetype() noexcept
			{
				static Archetype	archetype("nullptr_t", stringHasher("nullptr_t"), Entity::EKind::FundamentalArchetype, sizeof(std::nullptr_t));

				return archetype;
			}

			static Archetype const& getBoolArchetype() noexcept
			{
				static bool			initialized = false;
				static Archetype	archetype("bool", stringHasher("bool"), Entity::EKind::FundamentalArchetype, sizeof(bool));

				if (!initialized)
				{
					initialized = true;
				}

				return archetype;
			}

			static Archetype const& getCharArchetype() noexcept
			{
				static bool			initialized = false;
				static Archetype	archetype("char", stringHasher("char"), Entity::EKind::FundamentalArchetype, sizeof(char));

				if (!initialized)
				{
					initialized = true;
				}

				return archetype;
			}

			static Archetype const& getSignedCharArchetype() noexcept
			{
				static bool			initialized = false;
				static Archetype	archetype("signed char", stringHasher("signed char"), Entity::EKind::FundamentalArchetype, sizeof(signed char));

				if (!initialized)
				{
					initialized = true;
				}

				return archetype;
			}

			static Archetype const& getUnsignedCharArchetype() noexcept
			{
				static bool			initialized = false;
				static Archetype	archetype("unsigned char", stringHasher("unsigned char"), Entity::EKind::FundamentalArchetype, sizeof(unsigned char));

				if (!initialized)
				{
					initialized = true;
				}

				return archetype;
			}

			static Archetype const& getWideCharArchetype() noexcept
			{
				static bool			initialized = false;
				static Archetype	archetype("wide char", stringHasher("wide char"), Entity::EKind::FundamentalArchetype, sizeof(wchar_t));

				if (!initialized)
				{
					initialized = true;
				}

				return archetype;
			}

			static Archetype const& getChar16Archetype() noexcept
			{
				static bool			initialized = false;
				static Archetype	archetype("char16", stringHasher("char16"), Entity::EKind::FundamentalArchetype, sizeof(char16_t));

				if (!initialized)
				{
					initialized = true;
				}

				return archetype;
			}

			static Archetype const& getChar32Archetype() noexcept
			{
				static bool			initialized = false;
				static Archetype	archetype("char32", stringHasher("char32"), Entity::EKind::FundamentalArchetype, sizeof(char32_t));

				if (!initialized)
				{
					initialized = true;
				}

				return archetype;
			}

			static Archetype const& getShortArchetype() noexcept
			{
				static bool			initialized = false;
				static Archetype	archetype("short", stringHasher("short"), Entity::EKind::FundamentalArchetype, sizeof(short));

				if (!initialized)
				{
					initialized = true;
				}

				return archetype;
			}

			static Archetype const& getUnsignedShortArchetype() noexcept
			{
				static bool			initialized = false;
				static Archetype	archetype("unsigned short", stringHasher("unsigned short"), Entity::EKind::FundamentalArchetype, sizeof(unsigned short));

				if (!initialized)
				{
					initialized = true;
				}

				return archetype;
			}

			static Archetype const& getIntArchetype() noexcept
			{
				static bool			initialized = false;
				static Archetype	archetype("int", stringHasher("int"), Entity::EKind::FundamentalArchetype, sizeof(int));

				if (!initialized)
				{
					initialized = true;
				}

				return archetype;
			}

			static Archetype const& getUnsignedIntArchetype() noexcept
			{
				static bool			initialized = false;
				static Archetype	archetype("unsigned int", stringHasher("unsigned int"), Entity::EKind::FundamentalArchetype, sizeof(unsigned int));

				if (!initialized)
				{
					initialized = true;
				}

				return archetype;
			}

			static Archetype const& getLongArchetype() noexcept
			{
				static bool			initialized = false;
				static Archetype	archetype("long", stringHasher("long"), Entity::EKind::FundamentalArchetype, sizeof(long));

				if (!initialized)
				{
					initialized = true;
				}

				return archetype;
			}

			static Archetype const& getUnsignedLongArchetype() noexcept
			{
				static bool			initialized = false;
				static Archetype	archetype("unsigned long", stringHasher("unsigned long"), Entity::EKind::FundamentalArchetype, sizeof(unsigned long));

				if (!initialized)
				{
					initialized = true;
				}

				return archetype;
			}

			static Archetype const& getLongLongArchetype() noexcept
			{
				static bool			initialized = false;
				static Archetype	archetype("long long", stringHasher("long long"), Entity::EKind::FundamentalArchetype, sizeof(long long));

				if (!initialized)
				{
					initialized = true;
				}

				return archetype;
			}

			static Archetype const& getUnsignedLongLongArchetype() noexcept
			{
				static bool			initialized = false;
				static Archetype	archetype("unsigned long long", stringHasher("unsigned long long"), Entity::EKind::FundamentalArchetype, sizeof(unsigned long long));

				if (!initialized)
				{
					initialized = true;
				}

				return archetype;
			}

			static Archetype const& getFloatArchetype() noexcept
			{
				static bool			initialized = false;
				static Archetype	archetype("float", stringHasher("float"), Entity::EKind::FundamentalArchetype, sizeof(float));

				if (!initialized)
				{
					initialized = true;
				}

				return archetype;
			}

			static Archetype const& getDoubleArchetype() noexcept
			{
				static bool			initialized = false;
				static Archetype	archetype("double", stringHasher("double"), Entity::EKind::FundamentalArchetype, sizeof(double));

				if (!initialized)
				{
					initialized = true;
				}

				return archetype;
			}

			static Archetype const& getLongDoubleArchetype() noexcept
			{
				static bool			initialized = false;
				static Archetype	archetype("long double", stringHasher("long double"), Entity::EKind::FundamentalArchetype, sizeof(long double));

				if (!initialized)
				{
					initialized = true;
				}

				return archetype;
			}
	};
}