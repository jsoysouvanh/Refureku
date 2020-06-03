#pragma once

#include <vector>

#include "TypeInfo/Entity.h"

namespace rfk
{
	class StaticMethod;	//Forward declaration

	class Archetype : public Entity
	{
		public:
			/**
			*	Category of an archetype.
			*	Actually represents the class of an archetype instance.
			*/
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

			/** Size in bytes an instance of this archetype takes in memory, basically what sizeof(Type) returns */
			uint64		memorySize	= 0;

			Archetype(std::string&& newName,
					  uint64		newId			= 0u,
					  ECategory		newCategory		= ECategory::Undefined,
					  uint64		newMemorySize	= 0u)					noexcept;
			Archetype(Archetype const&)										= delete;
			Archetype(Archetype&&)											= default;
			~Archetype()													= default;

			Archetype& operator=(Archetype const&)	= delete;
			Archetype& operator=(Archetype&&)		= default;
	};
}