#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <memory>

#include "Misc/FundamentalTypes.h"
#include "TypeInfo/Field.h"
#include "TypeInfo/Method.h"
#include "TypeInfo/StaticMethod.h"
#include "TypeInfo/EAccessSpecifier.h"
#include "TypeInfo/GeneratedTraits.h"

namespace refureku
{
	class Archetype
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

			/**
			*	Type name
			*/
			std::string	name;

			/**
			*	Unique id qualifying this type
			*/
			uint64		id			= 0u;

			/**
			*	Category of this type
			*/
			ECategory	category	= ECategory::Undefined;

			Archetype(std::string&& newName, uint64 newId, ECategory newCategory)	noexcept;
			Archetype(Archetype const&)												= delete;
			Archetype(Archetype&&)													= default;
			~Archetype()															= default;

			Archetype& operator=(Archetype const&)	= delete;
			Archetype& operator=(Archetype&&)		= default;
	};

	#include "TypeInfo/Archetype.inl"
}