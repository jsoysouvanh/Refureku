#include "Refureku/TypeInfo/Namespaces/NamespaceFragmentRegisterer.h"

#include <cassert>
#include <algorithm>

#include "Refureku/TypeInfo/Namespaces/Namespace.h"
#include "Refureku/TypeInfo/Namespaces/NamespaceFragment.h"
#include "Refureku/TypeInfo/Database.h"

using namespace rfk;

NamespaceFragmentRegisterer::NamespaceFragmentRegisterer(char const* name, uint64 id, NamespaceFragment const& namespaceFragment, bool isFileLevelNamespace) noexcept:
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

void NamespaceFragmentRegisterer::mergeFragmentToNamespace(NamespaceFragment const& fragment) noexcept
{
	//Make sure we can actually merge this fragment to the namespace
	assert(_namespaceInstance->id == fragment.id);

	//Merge properties
	mergeFragmentPropertiesToNamespaceProperties(fragment);

	for (Entity const* entity : fragment.nestedEntities)
	{
		//Setup outer entity
		const_cast<Entity*>(entity)->outerEntity = _namespaceInstance.get();	//Don't tell anyone I actually wrote const_cast...

		switch (entity->kind)
		{
			case EEntityKind::Namespace:
				_namespaceInstance->namespaces.emplace(reinterpret_cast<Namespace const*>(entity));

				//Register the nested namespace but don't register sub entities
				Database::registerEntity(*entity, false);
				break;

			case EEntityKind::Struct:
				[[fallthrough]];
			case EEntityKind::Class:
				[[fallthrough]];
			case EEntityKind::Enum:
				_namespaceInstance->archetypes.emplace(reinterpret_cast<Archetype const*>(entity));
				
				//Register the archetype and its sub entities to the database.
				Database::registerEntity(*entity, true);
				break;

			case EEntityKind::Variable:
				_namespaceInstance->variables.emplace(reinterpret_cast<Variable const*>(entity));

				//Register the variable to the database, a variable doesn't have sub entities so can write false right away
				Database::registerEntity(*entity, false);
				break;

			case EEntityKind::Function:
				_namespaceInstance->functions.emplace(reinterpret_cast<Function const*>(entity));

				//Register the function to the database, a function doesn't have sub entities so can write false right away
				Database::registerEntity(*entity, false);
				break;

			case EEntityKind::EnumValue:
				[[fallthrough]];
			case EEntityKind::Field:
				[[fallthrough]];
			case EEntityKind::Method:
				[[fallthrough]];
			case EEntityKind::Undefined:
				[[fallthrough]];
			default:
				assert(false);	//None of these kind of entities should ever be a namespace nested entity
				break;
		}
	}
}

void NamespaceFragmentRegisterer::mergeFragmentPropertiesToNamespaceProperties(NamespaceFragment const& fragment) noexcept
{
	//Append properties
	for (Property const* fragmentProperty : fragment.properties)
	{
		//Don't add the prop if the same prop is already added
		if (!_namespaceInstance->getProperty([fragmentProperty](Property const* namespaceProperty)
			{
				return &namespaceProperty->getArchetype() == &fragmentProperty->getArchetype();
			}))
		{
			_namespaceInstance->properties.emplace_back(fragmentProperty);
		}
	}
}

void NamespaceFragmentRegisterer::removeFragmentFromNamespace(NamespaceFragment const& /* fragment */) noexcept
{
	//Each namespace self unregister, so we only need to unregister
	//nested non-namespace entities
	for (Entity const* entity : _fragment.nestedEntities)
	{
		switch (entity->kind)
		{
			case EEntityKind::Namespace:
				_namespaceInstance->namespaces.erase(reinterpret_cast<Namespace const*>(entity));

				//Namespaces unregister automatically from the database, don't need to do it here
				break;

			case EEntityKind::Struct:
				[[fallthrough]];
			case EEntityKind::Class:
				[[fallthrough]];
			case EEntityKind::Enum:
				_namespaceInstance->archetypes.erase(reinterpret_cast<Archetype const*>(entity));

				//Unregister archetypes and their sub entities from the database
				Database::unregisterEntity(*entity, true);
				break;

			case EEntityKind::Variable:
				_namespaceInstance->variables.erase(reinterpret_cast<Variable const*>(entity));

				//Unregister the variable from the database, a variable doesn't have sub entities so can write false right away
				Database::unregisterEntity(*entity, false);
				break;

			case EEntityKind::Function:
				_namespaceInstance->functions.erase(reinterpret_cast<Function const*>(entity));

				//Unregister the function from the database, a function doesn't have sub entities so can write false right away
				Database::unregisterEntity(*entity, false);
				break;

			case EEntityKind::EnumValue:
				[[fallthrough]];
			case EEntityKind::Field:
				[[fallthrough]];
			case EEntityKind::Method:
				[[fallthrough]];
			case EEntityKind::Undefined:
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