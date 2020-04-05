#pragma once

#include <string>
#include <unordered_set>
#include <type_traits>

#include "Misc/FundamentalTypes.h"
#include "TypeInfo/Archetypes/Class.h"
#include "TypeInfo/Archetypes/Enum.h"

namespace rfk
{
	class Database
	{
		friend class ArchetypeRegisterer;

		private:
			using ArchetypesById	= std::unordered_set<Archetype const*, Entity::PtrIdHasher, Entity::PtrEqualId>;
			using ArchetypesByName	= std::unordered_set<Archetype const*, Entity::PtrNameHasher, Entity::PtrEqualName>;

			static	ArchetypesById		_archetypesById;
			static	ArchetypesByName	_archetypesByName;

			static void	registerArchetype(Archetype const& archetype)	noexcept;

		public:
			Database()								= delete;
			Database(Database const&)				= delete;
			Database(Database&&)					= delete;
			~Database()								= delete;

			static Archetype const*				getArchetype(std::string typeName)	noexcept;
			static Archetype const*				getArchetype(uint64 id)				noexcept;

			static Struct const*				getStruct(std::string structName)	noexcept;
			static Struct const*				getStruct(uint64 id)				noexcept;

			static Class const*					getClass(std::string className)		noexcept;
			static Class const*					getClass(uint64 id)					noexcept;

			static Enum const*					getEnum(std::string enumName)		noexcept;
			static Enum const*					getEnum(uint64 id)					noexcept;

			static ArchetypesById const&		getArchetypesById()					noexcept;
			static ArchetypesByName	const&		getArchetypesByName()				noexcept;

			Database& operator=(Database const&)	= delete;
			Database& operator=(Database&&)			= delete;
	};

	#include "TypeInfo/Database.inl"
}