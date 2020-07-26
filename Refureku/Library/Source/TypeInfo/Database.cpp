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

void Database::registerFileLevelEntity(Entity const& entity, bool shouldRegisterSubEntities) noexcept
{
	//Register by id
	registerEntityById(entity, shouldRegisterSubEntities);

	//Register by name
	_fileLevelEntitiesByName.emplace(&entity);
}

void Database::registerEntityById(Entity const& entity, bool shouldRegisterSubEntities) noexcept
{
	_entitiesById.emplace(&entity);

	if (shouldRegisterSubEntities)
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
				//No sub entity to register
				break;

			case Entity::EKind::Undefined:
				[[fallthrough]];
			default:
				assert(false);	//Should never register a bad kind
				break;
		}
	}
}

void Database::registerSubEntities(Namespace const& n) noexcept
{
	//Add nested namespaces
	for (Namespace const* nn : n.nestedNamespaces)
	{
		registerEntityById(*nn, true);
	}

	//Add nested archetypes
	for (Archetype const* na : n.nestedArchetypes)
	{
		registerEntityById(*na, true);
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
			[[fallthrough]];
		default:
			assert(false);	//Should never register a bad category
			break;
	}
}

void Database::registerSubEntities(Struct const& s) noexcept
{
	//Add nested archetypes
	for (Archetype const* nestedArchetype : s.nestedArchetypes)
	{
		registerEntityById(*nestedArchetype, true);
	}

	//Add fields
	for (Entity const& field : s.fields)
	{
		registerEntityById(field, false);
	}

	for (Entity const& staticField : s.staticFields)
	{
		registerEntityById(staticField, false);
	}

	//Add methods
	for (Entity const& method : s.methods)
	{
		registerEntityById(method, false);
	}

	for (Entity const& staticMethod : s.staticMethods)
	{
		registerEntityById(staticMethod, false);
	}
}

void Database::registerSubEntities(Enum const& e) noexcept
{
	//Enum values
	for (Entity const& enumValue : e.values)
	{
		registerEntityById(enumValue, false);
	}
}

Entity const* Database::getEntity(uint64 id) noexcept
{
	Entity searching("", id);

	Database::EntitiesById::const_iterator it = _entitiesById.find(&searching);

	return (it != _entitiesById.cend()) ? *it : nullptr;
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