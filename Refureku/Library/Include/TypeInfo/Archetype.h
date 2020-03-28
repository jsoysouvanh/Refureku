#pragma once

#include <vector>
#include <algorithm>
#include <memory>

#include "TypeInfo/Entity.h"
#include "TypeInfo/Field.h"
#include "TypeInfo/Method.h"
#include "TypeInfo/StaticMethod.h"
#include "TypeInfo/EAccessSpecifier.h"
#include "TypeInfo/GeneratedTraits.h"

namespace refureku
{
	class Archetype : public Entity
	{
		public:
			enum class ECategory : uint8
			{
				Class	= 0,
				Struct,
				Enum,
				Fundamental,
				Undefined,

				Count
			};

			/** Category of this type */
			ECategory	category	= ECategory::Undefined;

			/** Size in bytes an instance of this archetype takes in memory, bsaically what typeof(Type) returns */
			uint64		memorySize	= 0;

			Archetype(std::string&& newName, uint64 newId, ECategory newCategory, uint64 newMemorySize)	noexcept;
			Archetype(Archetype const&)																	= delete;
			Archetype(Archetype&&)																		= default;
			~Archetype()																				= default;

			Archetype& operator=(Archetype const&)	= delete;
			Archetype& operator=(Archetype&&)		= default;
	};

	#include "TypeInfo/Archetype.inl"
}