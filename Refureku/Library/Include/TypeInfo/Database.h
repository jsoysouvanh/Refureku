#pragma once

#include <string>
#include <unordered_set>

#include "Misc/FundamentalTypes.h"
#include "TypeInfo/Class.h"

namespace rfk
{
	class Database
	{
		friend class ArchetypeRegisterer;
		friend class EnumRegisterer;

		private:
			using ArchetypesById	= std::unordered_set<Archetype const*, Entity::PtrIdHasher, Entity::PtrEqualId>;
			using ArchetypesByName	= std::unordered_set<Archetype const*, Entity::PtrNameHasher, Entity::PtrEqualName>;

			static	ArchetypesById		_archetypesById;
			static	ArchetypesByName	_archetypesByName;

			static void				registerArchetype(Archetype const& archetype)	noexcept;
			//TODO: static void		registerEnum(...)	noexcept;

		public:
			Database()								= delete;
			Database(Database const&)				= delete;
			Database(Database&&)					= delete;
			~Database()								= delete;

			static Archetype const*	getArchetype(std::string typeName)				noexcept;
			static Archetype const*	getArchetype(uint64 id)							noexcept;
			//TODO: static Enum const* getEnum(std::string const& enumName)	noexcept;
			//TODO: static Enum const* getEnum(uint64 id)	noexcept;

			static ArchetypesById const&	getArchetypesById()		noexcept;
			static ArchetypesByName	const&	getArchetypesByName()	noexcept;
			//TODO: static EnumsById const&	getEnumsById()			noexcept;
			//TODO: static EnumsByName const& getEnumsByName()		noexcept;

			Database& operator=(Database const&)	= delete;
			Database& operator=(Database&&)			= delete;
	};
}