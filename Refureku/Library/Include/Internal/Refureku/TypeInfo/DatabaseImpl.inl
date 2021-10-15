/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

void Database::DatabaseImpl::registerFileLevelEntity(Entity const& entity, bool shouldRegisterSubEntities) noexcept
{
	assert(entity.getOuterEntity() == nullptr);

	//Register by id
	registerEntityId(entity, shouldRegisterSubEntities);

	//Register by name
	switch (entity.getKind())
	{
		case EEntityKind::Namespace:
			_fileLevelNamespacesByName.emplace(reinterpret_cast<Namespace const*>(&entity));
			break;

		case EEntityKind::Struct:
			_fileLevelStructsByName.emplace(reinterpret_cast<Struct const*>(&entity));
			break;

		case EEntityKind::Class:
			_fileLevelClassesByName.emplace(reinterpret_cast<Class const*>(&entity));
			break;

		case EEntityKind::Enum:
			_fileLevelEnumsByName.emplace(reinterpret_cast<Enum const*>(&entity));
			break;

		case EEntityKind::Variable:
			_fileLevelVariablesByName.emplace(reinterpret_cast<Variable const*>(&entity));
			break;

		case EEntityKind::Function:
			_fileLevelFunctionsByName.emplace(reinterpret_cast<Function const*>(&entity));
			break;

		case EEntityKind::FundamentalArchetype:
			_fundamentalArchetypes.emplace(reinterpret_cast<FundamentalArchetype const*>(&entity));
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
			//Should never reach this point
			assert(false);
			break;
	}
}

void Database::DatabaseImpl::unregisterEntity(Entity const& entity, bool shouldUnregisterSubEntities) noexcept
{
	if (shouldUnregisterSubEntities)
	{
		switch (entity.getKind())
		{
			case EEntityKind::Namespace:
				assert(false); //This situation should never happen
				break;

			case EEntityKind::Struct:
				[[fallthrough]];
			case EEntityKind::Class:
				unregisterSubEntities(static_cast<Struct const&>(entity));
				break;

			case EEntityKind::Enum:
				unregisterSubEntities(static_cast<Enum const&>(entity));
				break;

			case EEntityKind::Variable:
				[[fallthrough]];
			case EEntityKind::Field:
				[[fallthrough]];
			case EEntityKind::Function:
				[[fallthrough]];
			case EEntityKind::Method:
				[[fallthrough]];
			case EEntityKind::EnumValue:
				[[fallthrough]];
			case EEntityKind::FundamentalArchetype:
				//No sub entity to unregister
				break;

			case EEntityKind::Undefined:
				[[fallthrough]];
			default:
				assert(false);	//Should never register a bad kind
				break;
		}
	}

	//Remove this entity from the list of registered entity ids
	_entitiesById.erase(&entity);

	if (entity.getOuterEntity() == nullptr)
	{
		switch (entity.getKind())
		{
			case EEntityKind::Namespace:
				_fileLevelNamespacesByName.erase(reinterpret_cast<Namespace const*>(&entity));
				break;

			case EEntityKind::Struct:
				_fileLevelStructsByName.erase(reinterpret_cast<Struct const*>(&entity));
				break;

			case EEntityKind::Class:
				_fileLevelClassesByName.erase(reinterpret_cast<Class const*>(&entity));
				break;

			case EEntityKind::Enum:
				_fileLevelEnumsByName.erase(reinterpret_cast<Enum const*>(&entity));
				break;

			case EEntityKind::Variable:
				_fileLevelVariablesByName.erase(reinterpret_cast<Variable const*>(&entity));
				break;

			case EEntityKind::Function:
				_fileLevelFunctionsByName.erase(reinterpret_cast<Function const*>(&entity));
				break;

			case EEntityKind::FundamentalArchetype:
				_fundamentalArchetypes.erase(reinterpret_cast<FundamentalArchetype const*>(&entity));
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
				//Those entities can't be at file level.
				assert(false);
				break;
		}
	}
}

void Database::DatabaseImpl::registerEntityId(Entity const& entity, bool shouldRegisterSubEntities) noexcept
{
	auto result = _entitiesById.emplace(&entity);

	//std::cout << "Register: (" << entity.getId() << ", " << entity.getName() << ")" << std::endl;

	//Emit a warning if 2 entities with the same ID are registered.
	if (!result.second)
	{
		Entity const* foundEntity = *_entitiesById.find(&entity);

		std::cout << "[Refureku] WARNING: Double registration detected: (" << entity.getId() << ", " << entity.getName() <<
			") collides with entity: (" << foundEntity->getId() << ", " << foundEntity->getName() << ")" << std::endl;
	}

	if (shouldRegisterSubEntities)
	{
		switch (entity.getKind())
		{
			case EEntityKind::Struct:
				[[fallthrough]];
			case EEntityKind::Class:
				registerSubEntities(static_cast<Struct const&>(entity));
				break;

			case EEntityKind::Enum:
				registerSubEntities(static_cast<Enum const&>(entity));
				break;

			case EEntityKind::Namespace:
				[[fallthrough]];	//Namespace nested entities are manually registered by NamespaceFragmentRegisterers
			case EEntityKind::FundamentalArchetype:
				[[fallthrough]];
			case EEntityKind::Variable:
				[[fallthrough]];
			case EEntityKind::Field:
				[[fallthrough]];
			case EEntityKind::Function:
				[[fallthrough]];
			case EEntityKind::Method:
				[[fallthrough]];
			case EEntityKind::EnumValue:
				//No sub entity to register
				break;

			case EEntityKind::Undefined:
				[[fallthrough]];
			default:
				assert(false);	//Should never register a bad kind
				break;
		}
	}
}

inline void Database::DatabaseImpl::registerSubEntities(Struct const& s) noexcept
{
	//Add nested archetypes
	s.foreachNestedArchetype([](Archetype const& archetype, void* userData)
							 {
								 reinterpret_cast<DatabaseImpl*>(userData)->registerEntityId(archetype, true);

								 return true;
							 }, this);

	//Add fields
	s.foreachField([](Field const& field, void* userData)
				   {
					   reinterpret_cast<DatabaseImpl*>(userData)->registerEntityId(field, false);

					   return true;
				   }, this, true);

	s.foreachStaticField([](StaticField const& staticField, void* userData)
						 {
							 reinterpret_cast<DatabaseImpl*>(userData)->registerEntityId(staticField, false);

							 return true;
						 }, this, true);

	//Add methods
	s.foreachMethod([](Method const& method, void* userData)
					{
						reinterpret_cast<DatabaseImpl*>(userData)->registerEntityId(method, false);

						return true;
					}, this);

	s.foreachStaticMethod([](StaticMethod const& staticMethod, void* userData)
						  {
							  reinterpret_cast<DatabaseImpl*>(userData)->registerEntityId(staticMethod, false);

							  return true;
						  }, this);
}

inline void Database::DatabaseImpl::unregisterSubEntities(Struct const& s) noexcept
{
	//Remove nested archetypes
	s.foreachNestedArchetype([](Archetype const& archetype, void* userData)
							 {
								 reinterpret_cast<DatabaseImpl*>(userData)->unregisterEntity(archetype, true);

								 return true;
							 }, this);

	//Remove fields
	s.foreachField([](Field const& field, void* userData)
				   {
					   reinterpret_cast<DatabaseImpl*>(userData)->unregisterEntity(field, false);

					   return true;
				   }, this, true);

	s.foreachStaticField([](StaticField const& staticField, void* userData)
						 {
							 reinterpret_cast<DatabaseImpl*>(userData)->unregisterEntity(staticField, false);

							 return true;
						 }, this, true);

	//Remove methods
	s.foreachMethod([](Method const& method, void* userData)
					{
						reinterpret_cast<DatabaseImpl*>(userData)->unregisterEntity(method, false);

						return true;
					}, this);

	s.foreachStaticMethod([](StaticMethod const& staticMethod, void* userData)
						  {
							  reinterpret_cast<DatabaseImpl*>(userData)->unregisterEntity(staticMethod, false);

							  return true;
						  }, this);
}

inline void Database::DatabaseImpl::registerSubEntities(Enum const& e) noexcept
{
	//Enum values
	e.foreachEnumValue([](EnumValue const& enumValue, void* userData)
					   {
						   reinterpret_cast<DatabaseImpl*>(userData)->registerEntityId(enumValue, false);

						   return true;
					   }, this);
}

inline void Database::DatabaseImpl::unregisterSubEntities(Enum const& e) noexcept
{
	//Enum values
	e.foreachEnumValue([](EnumValue const& enumValue, void* userData)
					   {
						   reinterpret_cast<DatabaseImpl*>(userData)->unregisterEntity(enumValue, false);

						   return true;
					   }, this);
}

inline void Database::DatabaseImpl::checkNamespaceRefCount(std::shared_ptr<Namespace> const& npPtr) noexcept
{
	assert(npPtr.use_count() >= 2);

	// 2: first is this method parameter, the second is the ptr stored in _generatedNamespaces
	if (npPtr.use_count() == 2)
	{
		//This shared pointer is used by database only so we can delete it
		unregisterEntity(*npPtr, false);

		_generatedNamespaces.erase(npPtr->getId());
	}
}

inline std::shared_ptr<Namespace> Database::DatabaseImpl::getOrCreateNamespace(char const* name, std::size_t id, bool isFileLevelNamespace) noexcept
{
	auto it = _generatedNamespaces.find(id);

	if (it != _generatedNamespaces.cend())
	{
		return it->second;
	}
	else
	{
		//Generate a namespace
		auto generatedNamespaceIt = _generatedNamespaces.emplace(id, std::make_shared<Namespace>(name, id));

		assert(generatedNamespaceIt.second);

		//Register the namespace to file level namespaces
		if (isFileLevelNamespace)
		{
			registerFileLevelEntity(*generatedNamespaceIt.first->second, false);
		}

		return generatedNamespaceIt.first->second;
	}
}

inline Database::DatabaseImpl::EntitiesById const& Database::DatabaseImpl::getEntitiesById() const noexcept
{
	return _entitiesById;
}

inline Database::DatabaseImpl::NamespacesByName const& Database::DatabaseImpl::getFileLevelNamespacesByName() const noexcept
{
	return _fileLevelNamespacesByName;
}

inline Database::DatabaseImpl::FundamentalArchetypesByName const& Database::DatabaseImpl::getFundamentalArchetypesByName() const noexcept
{
	return _fundamentalArchetypes;
}

inline Database::DatabaseImpl::StructsByName const& Database::DatabaseImpl::getFileLevelStructsByName() const noexcept
{
	return _fileLevelStructsByName;
}

inline Database::DatabaseImpl::ClassesByName const& Database::DatabaseImpl::getFileLevelClassesByName() const	noexcept
{
	return _fileLevelClassesByName;
}

inline Database::DatabaseImpl::EnumsByName const& Database::DatabaseImpl::getFileLevelEnumsByName() const noexcept
{
	return _fileLevelEnumsByName;
}

inline Database::DatabaseImpl::VariablesByName const& Database::DatabaseImpl::getFileLevelVariablesByName() const noexcept
{
	return _fileLevelVariablesByName;
}

inline Database::DatabaseImpl::FunctionsByName const& Database::DatabaseImpl::getFileLevelFunctionsByName() const noexcept
{
	return _fileLevelFunctionsByName;
}

inline Database::DatabaseImpl::GenNamespaces const& Database::DatabaseImpl::getGeneratedNamespaces() const noexcept
{
	return _generatedNamespaces;
}