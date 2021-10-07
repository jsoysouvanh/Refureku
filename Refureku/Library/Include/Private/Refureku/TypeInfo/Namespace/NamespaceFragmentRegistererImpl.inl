/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

inline internal::NamespaceFragmentRegistererImpl::NamespaceFragmentRegistererImpl(char const* name, std::size_t id, NamespaceFragment const& namespaceFragment, bool isFileLevelNamespace) noexcept:
	_registeredFragment{namespaceFragment},
	_namespaceInstance(nullptr)
{
	_namespaceInstance = DatabaseAPI::getInstance()._pimpl->getOrCreateNamespace(name, id, isFileLevelNamespace);

	mergeFragmentToNamespace();
}

inline internal::NamespaceFragmentRegistererImpl::~NamespaceFragmentRegistererImpl()
{
	//Unregister namespace fragment
	removeFragmentFromNamespace();

	//Check if this fragment was the last one from the namespace
	DatabaseAPI::getInstance()._pimpl->checkNamespaceRefCount(_namespaceInstance);
}

inline void internal::NamespaceFragmentRegistererImpl::mergeFragmentToNamespace() noexcept
{
	//Make sure we can actually merge this fragment to the namespace
	assert(_namespaceInstance->getId() == _registeredFragment.getId());

	//Merge properties
	mergeFragmentPropertiesToNamespaceProperties();

	_registeredFragment.foreachNestedEntity([](rfk::Entity const& entity, void* userData)
											{
												reinterpret_cast<NamespaceFragmentRegistererImpl*>(userData)->addEntityToNamespace(entity);

												return true;
											}, this);
}

inline void internal::NamespaceFragmentRegistererImpl::mergeFragmentPropertiesToNamespaceProperties() noexcept
{
	_registeredFragment.foreachProperty([](Property const& property, void* userData)
										{
											reinterpret_cast<NamespaceFragmentRegistererImpl*>(userData)->addPropertyToNamespace(property);

											return true;
										}, this);
}

inline void internal::NamespaceFragmentRegistererImpl::addPropertyToNamespace(Property const& property) const noexcept
{
	if (_namespaceInstance->getProperty(property.getArchetype(), false) == nullptr)
	{
		_namespaceInstance->addProperty(&property);
	}
}

inline void	internal::NamespaceFragmentRegistererImpl::addEntityToNamespace(Entity const& entity) const noexcept
{
	//Setup outer entity
	const_cast<Entity&>(entity).setOuterEntity(_namespaceInstance.get());	//Don't tell anyone I actually wrote const_cast...

	switch (entity.getKind())
	{
		case EEntityKind::Namespace:
			_namespaceInstance->addNamespace(static_cast<Namespace const&>(entity));

			//Register the nested namespace but don't register sub entities
			DatabaseAPI::getInstance()._pimpl->registerEntityId(entity, false);
			break;

		case EEntityKind::Struct:
			[[fallthrough]];
		case EEntityKind::Class:
			[[fallthrough]];
		case EEntityKind::Enum:
			_namespaceInstance->addArchetype(static_cast<ArchetypeAPI const&>(entity));

			//Register the archetype and its sub entities to the database.
			DatabaseAPI::getInstance()._pimpl->registerEntityId(entity, true);
			break;

		case EEntityKind::Variable:
			_namespaceInstance->addVariable(static_cast<VariableAPI const&>(entity));

			//Register the variable to the database, a variable doesn't have sub entities so can write false right away
			DatabaseAPI::getInstance()._pimpl->registerEntityId(entity, false);
			break;

		case EEntityKind::Function:
			_namespaceInstance->addFunction(static_cast<FunctionAPI const&>(entity));

			//Register the function to the database, a function doesn't have sub entities so can write false right away
			DatabaseAPI::getInstance()._pimpl->registerEntityId(entity, false);
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

inline void internal::NamespaceFragmentRegistererImpl::removeFragmentFromNamespace() noexcept
{
	//TODO: Should find a solution to remove registered properties?...

	_registeredFragment.foreachNestedEntity([](rfk::Entity const& entity, void* userData)
											{
												reinterpret_cast<NamespaceFragmentRegistererImpl*>(userData)->removeEntityFromNamespace(entity);
												
												return true;
											}, this);
}

inline void internal::NamespaceFragmentRegistererImpl::removeEntityFromNamespace(Entity const& entity) const noexcept
{
	switch (entity.getKind())
	{
		case EEntityKind::Namespace:
			_namespaceInstance->removeNamespace(static_cast<Namespace const&>(entity));

			//Namespaces unregister automatically from the database, don't need to do it here
			break;

		case EEntityKind::Struct:
			[[fallthrough]];
		case EEntityKind::Class:
			[[fallthrough]];
		case EEntityKind::Enum:
			_namespaceInstance->removeArchetype(static_cast<ArchetypeAPI const&>(entity));

			//Unregister archetypes and their sub entities from the database
			DatabaseAPI::getInstance()._pimpl->unregisterEntity(entity, true);
			break;

		case EEntityKind::Variable:
			_namespaceInstance->removeVariable(static_cast<VariableAPI const&>(entity));

			//Unregister the variable from the database, a variable doesn't have sub entities so can write false right away
			DatabaseAPI::getInstance()._pimpl->unregisterEntity(entity, false);
			break;

		case EEntityKind::Function:
			_namespaceInstance->removeFunction(static_cast<FunctionAPI const&>(entity));

			//Unregister the function from the database, a function doesn't have sub entities so can write false right away
			DatabaseAPI::getInstance()._pimpl->unregisterEntity(entity, false);
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

inline Namespace const* internal::NamespaceFragmentRegistererImpl::getNamespaceInstance() const noexcept
{
	return _namespaceInstance.get();
}