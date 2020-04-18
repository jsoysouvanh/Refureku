#include "TypeInfo/Database.h"

#include <iostream>

#include "Misc/DisableWarningMacros.h"

using namespace rfk;

//Init database containers BEFORE any other code so that reflected classes can register at startup
#if defined(__GNUC__) || defined(__clang__)

Database::EntitiesById		Database::_entitiesById		__attribute__ ((init_priority (101)));
Database::ArchetypesByName	Database::_archetypesByName	__attribute__ ((init_priority (101)));

#elif defined(_MSC_VER)

__RFK_DISABLE_WARNING_PUSH
__RFK_DISABLE_WARNING_INIT_SEG

#pragma init_seg(lib)

__RFK_DISABLE_WARNING_POP

Database::EntitiesById		Database::_entitiesById;
Database::ArchetypesByName	Database::_archetypesByName;

#else

Database::EntitiesById		Database::_entitiesById;
Database::ArchetypesByName	Database::_archetypesByName;

#endif

void Database::registerArchetype(Archetype const& archetype) noexcept
{
	registerSubEntities(archetype);

	_entitiesById.emplace(&archetype);
	_archetypesByName.emplace(&archetype);
}

void Database::registerSubEntities(Archetype const& archetype) noexcept
{
	switch (archetype.category)
	{
		case Archetype::ECategory::Struct:
			[[fallthrough]];
		case Archetype::ECategory::Class:
			registerStructSubEntities(static_cast<Struct const&>(archetype));
			break;

		case Archetype::ECategory::Enum:
			registerEnumSubEntities(static_cast<Enum const&>(archetype));
			break;

		case Archetype::ECategory::Fundamental:
			//Nothing special to do here since a fundamental archetype doesn't own sub entities
			break;

		case Archetype::ECategory::Count:
			[[fallthrough]];
		case Archetype::ECategory::Undefined:
			assert(false);	//Should never register a bad category
			break;
	}
}

void Database::registerStructSubEntities(Struct const& s) noexcept
{
	//Add fields
	for (Entity const& field : s.fields)
	{
		_entitiesById.emplace(&field);
	}

	for (Entity const& staticField : s.staticFields)
	{
		_entitiesById.emplace(&staticField);
	}

	//Add methods
	for (Entity const& method : s.methods)
	{
		_entitiesById.emplace(&method);
	}

	for (Entity const& staticMethod : s.staticMethods)
	{
		_entitiesById.emplace(&staticMethod);
	}
}

void Database::registerEnumSubEntities(Enum const& e) noexcept
{
	//Enum values
	for (Entity const& enumValue : e.values)
	{
		_entitiesById.emplace(&enumValue);
	}
}

Archetype const* Database::getArchetype(std::string typeName) noexcept
{
	Archetype searching(std::move(typeName));

	Database::ArchetypesByName::const_iterator it = _archetypesByName.find(&searching);

	return (it != _archetypesByName.cend()) ? *it : nullptr;
}

Struct const* Database::getStruct(std::string structName) noexcept
{
	Archetype const* archetype = getArchetype(std::move(structName));

	return (archetype != nullptr && archetype->category == Archetype::ECategory::Struct) ? static_cast<Struct const*>(archetype) : nullptr;
}

Class const* Database::getClass(std::string className) noexcept
{
	Archetype const* archetype = getArchetype(std::move(className));

	return (archetype != nullptr && archetype->category == Archetype::ECategory::Class) ? static_cast<Class const*>(archetype) : nullptr;
}

Enum const* Database::getEnum(std::string enumName) noexcept
{
	Archetype const* archetype = getArchetype(std::move(enumName));

	return (archetype != nullptr && archetype->category == Archetype::ECategory::Enum) ? static_cast<Enum const*>(archetype) : nullptr;
}

Entity const* Database::getEntity(uint64 id) noexcept
{
	Entity searching("", id);

	Database::EntitiesById::const_iterator it = _entitiesById.find(&searching);

	return (it != _entitiesById.cend()) ? *it : nullptr;
}

Database::EntitiesById const& Database::getEntitiesById() noexcept
{
	return _entitiesById;
}

Database::ArchetypesByName const& Database::getArchetypesByName() noexcept
{
	return _archetypesByName;
}