#include "TypeInfo/Database.h"

#include <iostream>

#include "Misc/DisableWarningMacros.h"

using namespace rfk;

//Init database containers BEFORE any other code so that reflected classes can register at startup
#if defined(__GNUC__) || defined(__clang__)

Database::EntitiesById		Database::_entitiesById				__attribute__((init_priority(101)));
Database::EntitiesByName	Database::_fileLevelEntitiesByName	__attribute__((init_priority(101)));

#elif defined(_MSC_VER)

__RFK_DISABLE_WARNING_PUSH
__RFK_DISABLE_WARNING_INIT_SEG

#pragma init_seg(lib)

__RFK_DISABLE_WARNING_POP

Database::EntitiesById		Database::_entitiesById;
Database::EntitiesByName	Database::_fileLevelEntitiesByName;

#else

Database::EntitiesById		Database::_entitiesById;
Database::EntitiesByName	Database::_fileLevelEntitiesByName;

#endif

void Database::registerFileLevelEntity(Entity const& entity) noexcept
{
	registerSubEntities(entity);

	_fileLevelEntitiesByName.emplace(&entity);
}

void Database::registerSubEntities(Entity const& entity) noexcept
{
	switch (entity.kind)
	{
		case Entity::EKind::Namespace:
			registerSubEntities(static_cast<Namespace const&>(entity));
			break;

		case Entity::EKind::Archetype:
			registerSubEntities(static_cast<Archetype const&>(entity));
			break;

		case Entity::EKind::Field:
			[[fallthrough]];
		case Entity::EKind::Method:
			[[fallthrough]];
		case Entity::EKind::EnumValue:
			[[fallthrough]];
		case Entity::EKind::Undefined:
			assert(false);	//Should never register a bad kind
			break;
	}
}

void Database::registerSubEntities(Namespace const& n) noexcept
{
	_entitiesById.emplace(&n);

	//Add nested namespaces
	for (Namespace const* nn : n.nestedNamespaces)
	{
		registerSubEntities(*nn);
	}

	//Add nested archetypes
	for (Archetype const* na : n.nestedArchetypes)
	{
		registerSubEntities(*na);
	}
}

void Database::registerSubEntities(Archetype const& archetype) noexcept
{
	switch (archetype.category)
	{
		case Archetype::ECategory::Struct:
			[[fallthrough]];
		case Archetype::ECategory::Class:
			registerSubEntities(static_cast<Struct const&>(archetype));
			break;

		case Archetype::ECategory::Enum:
			registerSubEntities(static_cast<Enum const&>(archetype));
			break;

		case Archetype::ECategory::Fundamental:
			//Nothing special to do here since a fundamental archetype doesn't own any sub entities
			break;

		case Archetype::ECategory::Count:
			[[fallthrough]];
		case Archetype::ECategory::Undefined:
			assert(false);	//Should never register a bad category
			break;
	}
}

void Database::registerSubEntities(Struct const& s) noexcept
{
	_entitiesById.emplace(&s);

	//Add nested archetypes
	for (Archetype const* nestedArchetype : s.nestedArchetypes)
	{
		registerSubEntities(*nestedArchetype);
	}

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

void Database::registerSubEntities(Enum const& e) noexcept
{
	_entitiesById.emplace(&e);

	//Enum values
	for (Entity const& enumValue : e.values)
	{
		_entitiesById.emplace(&enumValue);
	}
}

Entity const* Database::getEntity(std::string const& entityName) noexcept
{
	Entity searching(std::string(entityName), 0u);

	Database::EntitiesByName::const_iterator it = _fileLevelEntitiesByName.find(&searching);

	return (it != _fileLevelEntitiesByName.cend()) ? *it : nullptr;
}

Namespace const* Database::getNamespace(std::string const& namespaceName) noexcept
{
	Entity const* entity = getEntity(std::string(namespaceName));

	return (entity != nullptr && entity->kind == Entity::EKind::Namespace) ?
			reinterpret_cast<Namespace const*>(entity) :
			nullptr;
}

Struct const* Database::getStruct(std::string const& structName) noexcept
{
	Entity const* entity = getEntity(std::string(structName));

	return (entity != nullptr && entity->kind == Entity::EKind::Archetype && reinterpret_cast<Archetype const*>(entity)->category == Archetype::ECategory::Struct) ?
			reinterpret_cast<Struct const*>(entity) :
			nullptr;
}

Class const* Database::getClass(std::string const& className) noexcept
{
	Entity const* entity = getEntity(std::string(className));

	return (entity != nullptr && entity->kind == Entity::EKind::Archetype && reinterpret_cast<Archetype const*>(entity)->category == Archetype::ECategory::Class) ?
			reinterpret_cast<Class const*>(entity) :
			nullptr;
}

Enum const* Database::getEnum(std::string const& enumName) noexcept
{
	Entity const* entity = getEntity(std::string(enumName));

	return (entity != nullptr && entity->kind == Entity::EKind::Archetype && reinterpret_cast<Archetype const*>(entity)->category == Archetype::ECategory::Enum) ?
			reinterpret_cast<Enum const*>(entity) :
			nullptr;
}

Entity const* Database::getEntity(uint64 id) noexcept
{
	Entity searching("", id);

	Database::EntitiesById::const_iterator it = _entitiesById.find(&searching);

	return (it != _entitiesById.cend()) ? *it : nullptr;
}

void Database::clear() noexcept
{
	_entitiesById.clear();
	_fileLevelEntitiesByName.clear();
}

Database::EntitiesById const& Database::getEntitiesById() noexcept
{
	return _entitiesById;
}

Database::EntitiesByName const& Database::getFileLevelEntities() noexcept
{
	return _fileLevelEntitiesByName;
}