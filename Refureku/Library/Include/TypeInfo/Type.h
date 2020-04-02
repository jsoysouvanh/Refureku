#pragma once

#include <iostream>
#include <vector>

#include "TypeInfo/Archetypes/Archetype.h"
#include "TypeInfo/TypePart.h"


namespace rfk
{
	class Type
	{
		public:
			/** Archetype of this type */
			Archetype const*		archetype = nullptr;

			/** Parts of this type */
			std::vector<TypePart>	parts;

			Type()				= default;
			Type(Type const&)	= default;
			Type(Type&&)		= default;
			~Type()				= default;

			//TODO: methods

			Type& operator=(Type const&)	= default;
			Type& operator=(Type&&)			= default;

			bool operator==(Type const& type)	const noexcept;
	};

	std::ostream& operator<<(std::ostream& stream, Type const& type) noexcept;
}