#include "Refureku/TypeInfo/Namespaces/NamespaceFragmentRegisterer.h"

#include <cassert>
#include <algorithm>

#include "Refureku/TypeInfo/Namespaces/Namespace.h"
#include "Refureku/TypeInfo/Namespaces/NamespaceFragment.h"
#include "Refureku/TypeInfo/Database.h"

using namespace rfk;

NamespaceFragmentRegisterer::NamespaceFragmentRegisterer(char const* name, uint64 id, NamespaceFragment const* namespaceFragment, bool isFileLevelNamespace) noexcept:
	_fragment{namespaceFragment}
{
	//Try to get the namespace this fragment belongs to
	Entity const* foundNamespace = Database::getEntity(id);

	if (foundNamespace == nullptr)
	{
		//This namespace hasn't been registered yet, so create it
		_namespaceInstance = Database::generateNamespace(name, id);

		if (isFileLevelNamespace)
		{
			//Don't register a namespace sub entities as they will be registered manually during fragment merging
			Database::registerFileLevelEntity(*_namespaceInstance, false);
		}
	}
	else
	{
		//Retrieve the namespace pointer shared between all fragments
		_namespaceInstance = *std::find_if(Database::_generatedNamespaces.cbegin(),
										   Database::_generatedNamespaces.cend(),
										   [foundNamespace](std::shared_ptr<Namespace> const& n) { return n.get() == foundNamespace; });
	}

	mergeFragmentToNamespace(namespaceFragment);
}

NamespaceFragmentRegisterer::~NamespaceFragmentRegisterer() noexcept
{
	//Unregister namespace fragment
	removeFragmentFromNamespace(_fragment);

	//Check if this fragment was the last one from the namespace
	Database::checkNamespaceRefCount(_namespaceInstance);
}

void NamespaceFragmentRegisterer::mergeFragmentToNamespace(NamespaceFragment const* fragment) noexcept
{
	//Make sure we can actually merge this fragment to the namespace
	assert(_namespaceInstance->id == fragment->id);

	_mergedNamespaceFragment = fragment;

	//Merge properties
	mergeFragmentPropertiesToNamespaceProperties(fragment);

	for (Entity const* entity : fragment->nestedEntities)
	{
		//Setup outer entity
		const_cast<Entity*>(entity)->outerEntity = _namespaceInstance.get();	//Don't tell anyone I actually wrote const_cast...

		switch (entity->kind)
		{
			case Entity::EKind::Namespace:
				_namespaceInstance->namespaces.emplace(reinterpret_cast<Namespace const*>(entity));

				//Register the nested namespace but don't register sub entities
				Database::registerEntity(*entity, false);
				break;

			case Entity::EKind::Struct:
				[[fallthrough]];
			case Entity::EKind::Class:
				[[fallthrough]];
			case Entity::EKind::Enum:
				_namespaceInstance->archetypes.emplace(reinterpret_cast<Archetype const*>(entity));
				
				//Register the archetype and its sub entities to the database.
				Database::registerEntity(*entity, true);
				break;

			case Entity::EKind::Variable:
				_namespaceInstance->variables.emplace(reinterpret_cast<Variable const*>(entity));

				//Register the variable to the database, a variable doesn't have sub entities so can write false right away
				Database::registerEntity(*entity, false);
				break;

			case Entity::EKind::Function:
				_namespaceInstance->functions.emplace(reinterpret_cast<Function const*>(entity));

				//Register the function to the database, a function doesn't have sub entities so can write false right away
				Database::registerEntity(*entity, false);
				break;

			case Entity::EKind::EnumValue:
				[[fallthrough]];
			case Entity::EKind::Field:
				[[fallthrough]];
			case Entity::EKind::Method:
				[[fallthrough]];
			case Entity::EKind::Undefined:
				[[fallthrough]];
			default:
				assert(false);	//None of these kind of entities should ever be a namespace nested entity
				break;
		}
	}
}

void NamespaceFragmentRegisterer::mergeFragmentPropertiesToNamespaceProperties(NamespaceFragment const* fragment) noexcept
{
	//Append simple properties
	for (SimpleProperty const& simpleProperty : fragment->properties.simpleProperties)
	{
		//Add the simple prop only if it's not there yet
		if (_namespaceInstance->properties.getSimpleProperty(simpleProperty.mainProperty) == nullptr)
		{
			_namespaceInstance->properties.simpleProperties.push_back(simpleProperty);
		}
	}

	//Append complex properties
	for (ComplexProperty const& complexProperty : fragment->properties.complexProperties)
	{
		//Add the complex prop only if it's not there yet
		if (_namespaceInstance->properties.getComplexProperty(complexProperty.mainProperty) == nullptr)
		{
			_namespaceInstance->properties.complexProperties.push_back(complexProperty);
		}
	}
}

void NamespaceFragmentRegisterer::removeFragmentFromNamespace(NamespaceFragment const* /* fragment */) noexcept
{
	//Each namespace self unregister, so we only need to unregister
	//nested non-namespace entities
	for (Entity const* entity : _fragment->nestedEntities)
	{
		switch (entity->kind)
		{
			case Entity::EKind::Namespace:
				_namespaceInstance->namespaces.erase(reinterpret_cast<Namespace const*>(entity));

				//Namespaces unregister automatically from the database, don't need to do it here
				break;

			case Entity::EKind::Struct:
				[[fallthrough]];
			case Entity::EKind::Class:
				[[fallthrough]];
			case Entity::EKind::Enum:
				_namespaceInstance->archetypes.erase(reinterpret_cast<Archetype const*>(entity));

				//Unregister archetypes and their sub entities from the database
				Database::unregisterEntity(*entity, true);
				break;

			case Entity::EKind::Variable:
				_namespaceInstance->variables.erase(reinterpret_cast<Variable const*>(entity));

				//Unregister the variable from the database, a variable doesn't have sub entities so can write false right away
				Database::unregisterEntity(*entity, false);
				break;

			case Entity::EKind::Function:
				_namespaceInstance->functions.erase(reinterpret_cast<Function const*>(entity));

				//Unregister the function from the database, a function doesn't have sub entities so can write false right away
				Database::unregisterEntity(*entity, false);
				break;

			case Entity::EKind::EnumValue:
				[[fallthrough]];
			case Entity::EKind::Field:
				[[fallthrough]];
			case Entity::EKind::Method:
				[[fallthrough]];
			case Entity::EKind::Undefined:
				[[fallthrough]];
			default:
				assert(false);	//None of these kind of entities should ever be a namespace nested entity
				break;
		}
	}
}

Namespace const* NamespaceFragmentRegisterer::getNamespaceInstance() const noexcept
{
	return _namespaceInstance.get();
}