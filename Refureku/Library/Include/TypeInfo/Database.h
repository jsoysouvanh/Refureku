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
			using EntitiesById		= std::unordered_set<Entity const*, Entity::PtrIdHasher, Entity::PtrEqualId>;
			using ArchetypesByName	= std::unordered_set<Archetype const*, Entity::PtrNameHasher, Entity::PtrEqualName>;

			static	EntitiesById		_entitiesById;
			static	ArchetypesByName	_archetypesByName;

			static void	registerArchetype(Archetype const& archetype)	noexcept;
			static void registerSubEntities(Archetype const& archetype)	noexcept;
			static void registerStructSubEntities(Struct const& s)		noexcept;
			static void registerEnumSubEntities(Enum const& e)			noexcept;

		public:
			Database()								= delete;
			Database(Database const&)				= delete;
			Database(Database&&)					= delete;
			~Database()								= delete;

			static Archetype const*				getArchetype(std::string typeName)	noexcept;
			static Struct const*				getStruct(std::string structName)	noexcept;
			static Class const*					getClass(std::string className)		noexcept;
			static Enum const*					getEnum(std::string enumName)		noexcept;

			static Entity const*				getEntity(uint64 id)				noexcept;

			static EntitiesById const&			getEntitiesById()					noexcept;
			static ArchetypesByName	const&		getArchetypesByName()				noexcept;

			Database& operator=(Database const&)	= delete;
			Database& operator=(Database&&)			= delete;
	};
}