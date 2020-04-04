#include "TypeInfo/Database.h"

#include <iostream>

using namespace rfk;

//Init database containers BEFORE any other code so that reflected classes can register at startup
#if defined(_MSC_VER) || defined(__clang__)
	
#pragma init_seg(lib)

Database::ArchetypesById	Database::_archetypesById;
Database::ArchetypesByName	Database::_archetypesByName;

#elif defined(__GNUC__)

Database::ArchetypesById	Database::_archetypesById	__attribute__ ((init_priority (4242)));
Database::ArchetypesByName	Database::_archetypesByName	__attribute__ ((init_priority (4242)));

#endif

void Database::registerArchetype(Archetype const& archetype) noexcept
{
	std::cout << "Register Archetype: " << archetype.name << std::endl;

	_archetypesById.emplace(&archetype);
	_archetypesByName.emplace(&archetype);
}

Archetype const* Database::getArchetype(std::string typeName) noexcept
{
	Archetype searching(std::move(typeName));

	Database::ArchetypesByName::const_iterator it = _archetypesByName.find(&searching);

	return (it != _archetypesByName.cend()) ? *it : nullptr;
}

Archetype const* Database::getArchetype(uint64 id) noexcept
{
	Archetype searching("", id);

	Database::ArchetypesById::const_iterator it = _archetypesById.find(&searching);

	return (it != _archetypesById.cend()) ? *it : nullptr;
}

Struct const* Database::getStruct(std::string structName) noexcept
{
	Archetype const* archetype = getArchetype(std::move(structName));

	return (archetype != nullptr && archetype->category == Archetype::ECategory::Struct) ? static_cast<Struct const*>(archetype) : nullptr;
}

Struct const* Database::getStruct(uint64 id) noexcept
{
	Archetype const* archetype = getArchetype(id);

	return (archetype != nullptr && archetype->category == Archetype::ECategory::Struct) ? static_cast<Struct const*>(archetype) : nullptr;
}

Class const* Database::getClass(std::string className) noexcept
{
	Archetype const* archetype = getArchetype(std::move(className));

	return (archetype != nullptr && archetype->category == Archetype::ECategory::Class) ? static_cast<Class const*>(archetype) : nullptr;
}

Class const* Database::getClass(uint64 id) noexcept
{
	Archetype const* archetype = getArchetype(id);

	return (archetype != nullptr && archetype->category == Archetype::ECategory::Class) ? static_cast<Class const*>(archetype) : nullptr;
}

Enum const* Database::getEnum(std::string enumName) noexcept
{
	Archetype const* archetype = getArchetype(std::move(enumName));

	return (archetype != nullptr && archetype->category == Archetype::ECategory::Enum) ? static_cast<Enum const*>(archetype) : nullptr;
}

Enum const* Database::getEnum(uint64 id) noexcept
{
	Archetype const* archetype = getArchetype(id);

	return (archetype != nullptr && archetype->category == Archetype::ECategory::Enum) ? static_cast<Enum const*>(archetype) : nullptr;
}

Database::ArchetypesById const& Database::getArchetypesById() noexcept
{
	return _archetypesById;
}

Database::ArchetypesByName const& Database::getArchetypesByName() noexcept
{
	return _archetypesByName;
}