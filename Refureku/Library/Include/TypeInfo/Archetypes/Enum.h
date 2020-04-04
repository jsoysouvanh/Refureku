#pragma once

#include <vector>

#include "TypeInfo/Archetypes/Archetype.h"
#include "TypeInfo/EnumValue.h"

namespace rfk
{
	class Enum : public Archetype
	{
		public:
			std::vector<EnumValue>	values;

			Enum()													= delete;
			Enum(std::string&& name, uint64 id, uint64 memorySize)	noexcept;
			Enum(Enum const&)										= delete;
			Enum(Enum&&)											= default;
			~Enum()													= default;

			//TODO?

			Enum& operator=(Enum const&)	= delete;
			Enum& operator=(Enum&&)			= default;
	};

	/** Base implementation of getEnum, specialized for each reflected enum */
	template <typename T, typename = std::enable_if_t<std::is_enum_v<T>>>
	rfk::Enum const* getEnum() noexcept
	{
		return nullptr;
	}
}