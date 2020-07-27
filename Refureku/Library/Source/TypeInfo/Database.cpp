#include "TypeInfo/Database.h"

#include <iostream>

#include "Exceptions/BadNamespaceFormat.h"
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
	registerEntity(entity, shouldRegisterSubEntities);

	//Register by name
	_fileLevelEntitiesByName.emplace(&entity);
}

void Database::registerEntity(Entity const& entity, bool shouldRegisterSubEntities) noexcept
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
		registerEntity(*nn, true);
	}

	//Add nested archetypes
	for (Archetype const* na : n.nestedArchetypes)
	{
		registerEntity(*na, true);
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
		registerEntity(*nestedArchetype, true);
	}

	//Add fields
	for (Entity const& field : s.fields)
	{
		registerEntity(field, false);
	}

	for (Entity const& staticField : s.staticFields)
	{
		registerEntity(staticField, false);
	}

	//Add methods
	for (Entity const& method : s.methods)
	{
		registerEntity(method, false);
	}

	for (Entity const& staticMethod : s.staticMethods)
	{
		registerEntity(staticMethod, false);
	}
}

void Database::registerSubEntities(Enum const& e) noexcept
{
	//Enum values
	for (Entity const& enumValue : e.values)
	{
		registerEntity(enumValue, false);
	}
}

Entity const* Database::getEntity(uint64 id) noexcept
{
	Entity searching("", id);

	Database::EntitiesById::const_iterator it = _entitiesById.find(&searching);

	return (it != _entitiesById.cend()) ? *it : nullptr;
}

Entity const* Database::getEntity(std::string entityName) noexcept
{
	Entity searching(std::move(entityName), 0u);

	Database::EntitiesByName::const_iterator it = _fileLevelEntitiesByName.find(&searching);

	return (it != _fileLevelEntitiesByName.cend()) ? *it : nullptr;
}

Namespace const* Database::getNamespace(std::string namespaceName)
{
	size_t			index	= namespaceName.find_first_of(':');

	//Make sure namespaceName has a valid namespace syntax
	if (index != std::string::npos && (index == namespaceName.size() - 1 || namespaceName[index + 1] != ':'))
	{
		throw BadNamespaceFormat("The provided namespace name is ill formed.");
	}

	Entity const*	entity	= getEntity(namespaceName.substr(0u, index));

	//Couldn't find first namespace part, abort search
	if (entity == nullptr || entity->kind != Entity::EKind::Namespace)
	{
		return nullptr;
	}

	Namespace const* result = reinterpret_cast<Namespace const*>(entity);

	while (index != std::string::npos && result != nullptr)
	{
		if (namespaceName.size() <= index + 2u ||	//The provided namespace name either ends with : or :[some char]
			namespaceName[index + 1] != ':')		//or the namespace separation was : instead of ::
		{
			throw BadNamespaceFormat("The provided namespace name is ill formed.");
		}

		//Remove namespace separation :: 
		namespaceName	= namespaceName.substr(index + 2u);
		index			= namespaceName.find_first_of(':');

		result = result->getNestedNamespace(namespaceName.substr(0u, index));
	}

	return result;
}

//Namespace const* Database::getNamespace(std::string namespaceName, bool allowNestedNamespaces) noexcept
//{
//	//Entity const* entity = getEntity(std::move(namespaceName));
//
//	//if (allowNestedNamespaces &&
//	//	(entity == nullptr || entity->kind != Entity::EKind::Namespace))
//	//{
//	//	//Look in nested namespaces
//	//	for (Entity const* entity : _fileLevelEntitiesByName)	//Might consider making a vector containing only file level namespaces to avoid iteration over all file entities (potentially a lot of classes)
//	//	{
//	//		if (entity->kind == Entity::EKind::Namespace)
//	//		{
//
//	//		}
//	//	}
//	//}
//	//else
//	//{
//	//	return (entity != nullptr && entity->kind == Entity::EKind::Namespace) ?
//	//			reinterpret_cast<Namespace const*>(entity) :
//	//			nullptr;
//	//}
//
//	return nullptr;
//}

Struct const* Database::getStruct(std::string structName) noexcept
{
	Entity const* entity = getEntity(std::move(structName));

	return (entity != nullptr && entity->kind == Entity::EKind::Archetype && reinterpret_cast<Archetype const*>(entity)->category == Archetype::ECategory::Struct) ?
			reinterpret_cast<Struct const*>(entity) :
			nullptr;
}

Class const* Database::getClass(std::string className) noexcept
{
	Entity const* entity = getEntity(std::move(className));

	return (entity != nullptr && entity->kind == Entity::EKind::Archetype && reinterpret_cast<Archetype const*>(entity)->category == Archetype::ECategory::Class) ?
			reinterpret_cast<Class const*>(entity) :
			nullptr;
}

Enum const* Database::getEnum(std::string enumName) noexcept
{
	Entity const* entity = getEntity(std::move(enumName));

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