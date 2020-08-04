#include "Refureku/TypeInfo/Namespaces/NamespaceFragmentRegisterer.h"

#include <cassert>

#include "Refureku/TypeInfo/Namespaces/Namespace.h"
#include "Refureku/TypeInfo/Namespaces/NamespaceFragment.h"
#include "Refureku/TypeInfo/Database.h"

using namespace rfk;

NamespaceFragmentRegisterer::NamespaceFragmentRegisterer(char const* name, uint64 id, NamespaceFragment const* namespaceFragment, bool isFileLevelNamespace) noexcept
{
	//Try to get the namespace this fragment belongs to
	Entity const* foundNamespace = Database::getEntity(id);

	if (foundNamespace == nullptr)
	{
		//This namespace hasn't been registered yet, so create it
		_namespaceInstance = new Namespace(name, id);	//TODO: The database should be the one generating the pointer, (using shared_ptr)
		_isNamespaceOwner	= true;

		if (isFileLevelNamespace)
		{
			//Don't register a namespace sub entities as they will be registered manually during fragment merging
			Database::registerFileLevelEntity(*_namespaceInstance, false);
		}
	}
	else
	{
		//Sorry we need to get rid of that const to fill you...
		_namespaceInstance = const_cast<Namespace*>(reinterpret_cast<Namespace const*>(foundNamespace));
	}

	mergeFragmentToNamespace(namespaceFragment);
}

NamespaceFragmentRegisterer::~NamespaceFragmentRegisterer() noexcept
{
	if (_isNamespaceOwner)
	{
		delete _namespaceInstance;
	}
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
		const_cast<Entity*>(entity)->outerEntity = _namespaceInstance;	//Don't tell anyone I actually wrote const_cast...

		switch (entity->kind)
		{
			case Entity::EKind::Namespace:
				_namespaceInstance->nestedNamespaces.emplace(reinterpret_cast<Namespace const*>(entity));

				//Register the nested namespace but don't register sub entities
				Database::registerEntity(*entity, false);

				break;

			case Entity::EKind::Archetype:
				_namespaceInstance->nestedArchetypes.emplace(reinterpret_cast<Archetype const*>(entity));
				
				//Register the archetype and its sub entities to the database.
				Database::registerEntity(*entity, true);

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
	//TODO
}

Namespace const* NamespaceFragmentRegisterer::getNamespaceInstance() const noexcept
{
	return _namespaceInstance;
}