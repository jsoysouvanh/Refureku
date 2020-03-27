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
	class Type
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

			Type(std::string&& newName, uint64 newId, ECategory newCategory)	noexcept;
			Type(Type const&)													= default;
			Type(Type&&)														= default;
			~Type()																= default;

			Type& operator=(Type const&)	= default;
			Type& operator=(Type&&)			= default;
	};

	#include "TypeInfo/Type.inl"
}