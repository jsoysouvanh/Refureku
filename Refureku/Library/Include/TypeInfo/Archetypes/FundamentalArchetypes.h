#pragma once

#include <functional>
#include <string>
#include <cstddef>

#include "Misc/FundamentalTypes.h"
#include "TypeInfo/Archetypes/Archetype.h"

namespace rfk
{
	class FundamentalArchetypes
	{
		private:
			static inline std::hash<std::string>	_stringHasher;
			
			inline static void* instantiateBool() noexcept
			{
				return new bool();
			}

			inline static void* instantiateChar() noexcept
			{
				return new char();
			}

			inline static void* instantiateSignedChar() noexcept
			{
				return new signed char();
			}

			inline static void* instantiateUnsignedChar() noexcept
			{
				return new unsigned char();
			}

			inline static void* instantiateWideChar() noexcept
			{
				return new wchar_t();
			}

			inline static void* instantiateChar16() noexcept
			{
				return new char16_t();
			}

			inline static void* instantiateChar32() noexcept
			{
				return new char32_t();
			}

			inline static void* instantiateShort() noexcept
			{
				return new short();
			}

			inline static void* instantiateUnsignedShort() noexcept
			{
				return new unsigned short();
			}

			inline static void* instantiateInt() noexcept
			{
				return new int();
			}

			inline static void* instantiateUnsignedInt() noexcept
			{
				return new unsigned int();
			}

			inline static void* instantiateLong() noexcept
			{
				return new long();
			}

			inline static void* instantiateUnsignedLong() noexcept
			{
				return new unsigned long();
			}

			inline static void* instantiateLongLong() noexcept
			{
				return new long long();
			}

			inline static void* instantiateUnsignedLongLong() noexcept
			{
				return new unsigned long long();
			}

			inline static void* instantiateFloat() noexcept
			{
				return new float();
			}

			inline static void* instantiateDouble() noexcept
			{
				return new double();
			}

			inline static void* instantiateLongDouble() noexcept
			{
				return new double();
			}

		public:
			FundamentalArchetypes()								= delete;
			FundamentalArchetypes(FundamentalArchetypes const&) = delete;
			FundamentalArchetypes(FundamentalArchetypes&&)		= delete;
			~FundamentalArchetypes()							= delete;

			static Archetype const& getVoidArchetype() noexcept
			{
				static Archetype archetype("void", _stringHasher("void"), Archetype::ECategory::Fundamental, 0u);

				return archetype;
			}

			static Archetype const& getNullptrArchetype() noexcept
			{
				static Archetype	archetype("nullptr_t", _stringHasher("nullptr_t"), Archetype::ECategory::Fundamental, sizeof(std::nullptr_t));

				return archetype;
			}

			static Archetype const& getBoolArchetype() noexcept
			{
				static bool			initialized = false;
				static Archetype	archetype("bool", _stringHasher("bool"), Archetype::ECategory::Fundamental, sizeof(bool));

				if (!initialized)
				{
					initialized = true;

					archetype.__RFKsetDefaultInstantiationMethod(&FundamentalArchetypes::instantiateBool);
				}

				return archetype;
			}

			static Archetype const& getCharArchetype() noexcept
			{
				static bool			initialized = false;
				static Archetype	archetype("char", _stringHasher("char"), Archetype::ECategory::Fundamental, sizeof(char));

				if (!initialized)
				{
					initialized = true;

					archetype.__RFKsetDefaultInstantiationMethod(&FundamentalArchetypes::instantiateChar);
				}

				return archetype;
			}

			static Archetype const& getSignedCharArchetype() noexcept
			{
				static bool			initialized = false;
				static Archetype	archetype("signed char", _stringHasher("signed char"), Archetype::ECategory::Fundamental, sizeof(signed char));

				if (!initialized)
				{
					initialized = true;

					archetype.__RFKsetDefaultInstantiationMethod(&FundamentalArchetypes::instantiateSignedChar);
				}

				return archetype;
			}

			static Archetype const& getUnsignedCharArchetype() noexcept
			{
				static bool			initialized = false;
				static Archetype	archetype("unsigned char", _stringHasher("unsigned char"), Archetype::ECategory::Fundamental, sizeof(unsigned char));

				if (!initialized)
				{
					initialized = true;

					archetype.__RFKsetDefaultInstantiationMethod(&FundamentalArchetypes::instantiateUnsignedChar);
				}

				return archetype;
			}

			static Archetype const& getWideCharArchetype() noexcept
			{
				static bool			initialized = false;
				static Archetype	archetype("wide char", _stringHasher("wide char"), Archetype::ECategory::Fundamental, sizeof(wchar_t));

				if (!initialized)
				{
					initialized = true;

					archetype.__RFKsetDefaultInstantiationMethod(&FundamentalArchetypes::instantiateWideChar);
				}

				return archetype;
			}

			static Archetype const& getChar16Archetype() noexcept
			{
				static bool			initialized = false;
				static Archetype	archetype("char16", _stringHasher("char16"), Archetype::ECategory::Fundamental, sizeof(char16_t));

				if (!initialized)
				{
					initialized = true;

					archetype.__RFKsetDefaultInstantiationMethod(&FundamentalArchetypes::instantiateChar16);
				}

				return archetype;
			}

			static Archetype const& getChar32Archetype() noexcept
			{
				static bool			initialized = false;
				static Archetype	archetype("char32", _stringHasher("char32"), Archetype::ECategory::Fundamental, sizeof(char32_t));

				if (!initialized)
				{
					initialized = true;

					archetype.__RFKsetDefaultInstantiationMethod(&FundamentalArchetypes::instantiateChar32);
				}

				return archetype;
			}

			static Archetype const& getShortArchetype() noexcept
			{
				static bool			initialized = false;
				static Archetype	archetype("short", _stringHasher("short"), Archetype::ECategory::Fundamental, sizeof(short));

				if (!initialized)
				{
					initialized = true;

					archetype.__RFKsetDefaultInstantiationMethod(&FundamentalArchetypes::instantiateShort);
				}

				return archetype;
			}

			static Archetype const& getUnsignedShortArchetype() noexcept
			{
				static bool			initialized = false;
				static Archetype	archetype("unsigned short", _stringHasher("unsigned short"), Archetype::ECategory::Fundamental, sizeof(unsigned short));

				if (!initialized)
				{
					initialized = true;

					archetype.__RFKsetDefaultInstantiationMethod(&FundamentalArchetypes::instantiateUnsignedShort);
				}

				return archetype;
			}

			static Archetype const& getIntArchetype() noexcept
			{
				static bool			initialized = false;
				static Archetype	archetype("int", _stringHasher("int"), Archetype::ECategory::Fundamental, sizeof(int));

				if (!initialized)
				{
					initialized = true;

					archetype.__RFKsetDefaultInstantiationMethod(&FundamentalArchetypes::instantiateInt);
				}

				return archetype;
			}

			static Archetype const& getUnsignedIntArchetype() noexcept
			{
				static bool			initialized = false;
				static Archetype	archetype("unsigned int", _stringHasher("unsigned int"), Archetype::ECategory::Fundamental, sizeof(unsigned int));

				if (!initialized)
				{
					initialized = true;

					archetype.__RFKsetDefaultInstantiationMethod(&FundamentalArchetypes::instantiateUnsignedInt);
				}

				return archetype;
			}

			static Archetype const& getLongArchetype() noexcept
			{
				static bool			initialized = false;
				static Archetype	archetype("long", _stringHasher("long"), Archetype::ECategory::Fundamental, sizeof(long));

				if (!initialized)
				{
					initialized = true;

					archetype.__RFKsetDefaultInstantiationMethod(&FundamentalArchetypes::instantiateLong);
				}

				return archetype;
			}

			static Archetype const& getUnsignedLongArchetype() noexcept
			{
				static bool			initialized = false;
				static Archetype	archetype("unsigned long", _stringHasher("unsigned long"), Archetype::ECategory::Fundamental, sizeof(unsigned long));

				if (!initialized)
				{
					initialized = true;

					archetype.__RFKsetDefaultInstantiationMethod(&FundamentalArchetypes::instantiateUnsignedLong);
				}

				return archetype;
			}

			static Archetype const& getLongLongArchetype() noexcept
			{
				static bool			initialized = false;
				static Archetype	archetype("long long", _stringHasher("long long"), Archetype::ECategory::Fundamental, sizeof(long long));

				if (!initialized)
				{
					initialized = true;

					archetype.__RFKsetDefaultInstantiationMethod(&FundamentalArchetypes::instantiateLongLong);
				}

				return archetype;
			}

			static Archetype const& getUnsignedLongLongArchetype() noexcept
			{
				static bool			initialized = false;
				static Archetype	archetype("unsigned long long", _stringHasher("unsigned long long"), Archetype::ECategory::Fundamental, sizeof(unsigned long long));

				if (!initialized)
				{
					initialized = true;

					archetype.__RFKsetDefaultInstantiationMethod(&FundamentalArchetypes::instantiateUnsignedLongLong);
				}

				return archetype;
			}

			static Archetype const& getFloatArchetype() noexcept
			{
				static bool			initialized = false;
				static Archetype	archetype("float", _stringHasher("float"), Archetype::ECategory::Fundamental, sizeof(float));

				if (!initialized)
				{
					initialized = true;

					archetype.__RFKsetDefaultInstantiationMethod(&FundamentalArchetypes::instantiateFloat);
				}

				return archetype;
			}

			static Archetype const& getDoubleArchetype() noexcept
			{
				static bool			initialized = false;
				static Archetype	archetype("double", _stringHasher("double"), Archetype::ECategory::Fundamental, sizeof(double));

				if (!initialized)
				{
					initialized = true;

					archetype.__RFKsetDefaultInstantiationMethod(&FundamentalArchetypes::instantiateDouble);
				}

				return archetype;
			}

			static Archetype const& getLongDoubleArchetype() noexcept
			{
				static bool			initialized = false;
				static Archetype	archetype("long double", _stringHasher("long double"), Archetype::ECategory::Fundamental, sizeof(long double));

				if (!initialized)
				{
					initialized = true;

					archetype.__RFKsetDefaultInstantiationMethod(&FundamentalArchetypes::instantiateLongDouble);
				}

				return archetype;
			}
	};
}