/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

inline void Database::DatabaseImpl::registerFileLevelEntityRecursive(Entity const& entity) noexcept
{
	assert(entity.getOuterEntity() == nullptr);

	//Register by name
	switch (entity.getKind())
	{
		case EEntityKind::NamespaceFragment:
			_fileLevelNamespacesByName.emplace(reinterpret_cast<Namespace const*>(&static_cast<NamespaceFragment const&>(entity).getMergedNamespace()));
			
			registerSubEntitesId(entity);
			return;	

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

		case EEntityKind::Namespace:
			//This situation should never happen since namespace registration is done through NamespaceFragment
			[[fallthrough]];
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

	//Register by id
	registerEntityIdRecursive(entity);
}

inline void Database::DatabaseImpl::unregisterEntityRecursive(Entity const& entity) noexcept
{
	switch (entity.getKind())
	{
		case EEntityKind::NamespaceFragment:
			unregisterNamespaceFragmentSubEntities(static_cast<NamespaceFragment const&>(entity));
				
			//Namespace fragment is not registered by id, and is not a file level registered entity neither
			//So we can exit the method call right away
			return;	

		case EEntityKind::Struct:
			[[fallthrough]];
		case EEntityKind::Class:
			unregisterStructSubEntities(static_cast<Struct const&>(entity));
			break;

		case EEntityKind::Enum:
			unregisterEnumSubEntities(static_cast<Enum const&>(entity));
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

		case EEntityKind::Namespace:
			//This situation should never happen since namespace unregistration is done through NamespaceFragment
			[[fallthrough]];
		case EEntityKind::Undefined:
			[[fallthrough]];
		default:
			assert(false);	//Should never register a bad kind
			break;
	}

	unregisterEntity(entity);
}

inline void Database::DatabaseImpl::unregisterEntity(Entity const& entity) noexcept
{
	//Remove this entity from the list of registered entity ids
	_entitiesById.erase(&entity);

	//Remove the entity from the suitable file level entities collection if applicable
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

inline void Database::DatabaseImpl::registerEntityId(Entity const& entity) noexcept
{
	//Should never register namespace fragments
	assert(entity.getKind() != EEntityKind::NamespaceFragment);

	auto result = _entitiesById.emplace(&entity);

	//std::cout << "Register: (" << entity.getId() << ", " << entity.getName() << ")" << std::endl;

	//Emit a warning if 2 entities with the same ID are registered.
	if (!result.second)
	{
		Entity const* foundEntity = *_entitiesById.find(&entity);

		std::cout << "[Refureku] WARNING: Double registration detected: (" << entity.getId() << ", " << entity.getName() <<
			") collides with entity: (" << foundEntity->getId() << ", " << foundEntity->getName() << ")" << std::endl;
	}
}

inline void Database::DatabaseImpl::registerSubEntitesId(Entity const& entity) noexcept
{
	switch (entity.getKind())
	{
		case EEntityKind::NamespaceFragment:
			registerNamespaceFragmentSubEntities(static_cast<NamespaceFragment const&>(entity));
			break;

		case EEntityKind::Struct:
			[[fallthrough]];
		case EEntityKind::Class:
			registerStructSubEntities(static_cast<Struct const&>(entity));
			break;

		case EEntityKind::Enum:
			registerEnumSubEntities(static_cast<Enum const&>(entity));
			break;

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

		case EEntityKind::Namespace:
			[[fallthrough]];
		case EEntityKind::Undefined:
			[[fallthrough]];
		default:
			assert(false);	//Should never happen
			break;
	}
}

inline void Database::DatabaseImpl::registerEntityIdRecursive(Entity const& entity) noexcept
{
	registerEntityId(entity);
	registerSubEntitesId(entity);
}

inline void Database::DatabaseImpl::registerNamespaceFragmentSubEntities(NamespaceFragment const& frag) noexcept
{
	frag.foreachNestedEntity([](Entity const& nestedEntity, void* userData)
							 {
								 switch (nestedEntity.getKind())
								 {
									 case EEntityKind::NamespaceFragment:
										 reinterpret_cast<DatabaseImpl*>(userData)->registerSubEntitesId(nestedEntity);
										 break;

									 default:
										 reinterpret_cast<DatabaseImpl*>(userData)->registerEntityIdRecursive(nestedEntity);
										 break;
								 }
								 
								 return true;
							 }, this);
}

inline void Database::DatabaseImpl::unregisterNamespaceFragmentSubEntities(NamespaceFragment const& frag) noexcept
{
	frag.foreachNestedEntity([](Entity const& nestedEntity, void* userData)
							 {
								 reinterpret_cast<DatabaseImpl*>(userData)->unregisterEntityRecursive(nestedEntity);

								 return true;
							 }, this);
}

inline void Database::DatabaseImpl::registerStructSubEntities(Struct const& s) noexcept
{
	//Add nested archetypes
	s.foreachNestedArchetype([](Archetype const& archetype, void* userData)
							 {
								 reinterpret_cast<DatabaseImpl*>(userData)->registerEntityIdRecursive(archetype);

								 return true;
							 }, this);

	//Add fields
	s.foreachField([](Field const& field, void* userData)
				   {
					   reinterpret_cast<DatabaseImpl*>(userData)->registerEntityIdRecursive(field);

					   return true;
				   }, this, true);

	s.foreachStaticField([](StaticField const& staticField, void* userData)
						 {
							 reinterpret_cast<DatabaseImpl*>(userData)->registerEntityIdRecursive(staticField);

							 return true;
						 }, this, true);

	//Add methods
	s.foreachMethod([](Method const& method, void* userData)
					{
						reinterpret_cast<DatabaseImpl*>(userData)->registerEntityIdRecursive(method);

						return true;
					}, this);

	s.foreachStaticMethod([](StaticMethod const& staticMethod, void* userData)
						  {
							  reinterpret_cast<DatabaseImpl*>(userData)->registerEntityIdRecursive(staticMethod);

							  return true;
						  }, this);
}

inline void Database::DatabaseImpl::unregisterStructSubEntities(Struct const& s) noexcept
{
	//Remove nested archetypes
	s.foreachNestedArchetype([](Archetype const& archetype, void* userData)
							 {
								 reinterpret_cast<DatabaseImpl*>(userData)->unregisterEntityRecursive(archetype);

								 return true;
							 }, this);

	//Remove fields
	s.foreachField([](Field const& field, void* userData)
				   {
					   reinterpret_cast<DatabaseImpl*>(userData)->unregisterEntity(field);

					   return true;
				   }, this, true);

	s.foreachStaticField([](StaticField const& staticField, void* userData)
						 {
							 reinterpret_cast<DatabaseImpl*>(userData)->unregisterEntity(staticField);

							 return true;
						 }, this, true);

	//Remove methods
	s.foreachMethod([](Method const& method, void* userData)
					{
						reinterpret_cast<DatabaseImpl*>(userData)->unregisterEntity(method);

						return true;
					}, this);

	s.foreachStaticMethod([](StaticMethod const& staticMethod, void* userData)
						  {
							  reinterpret_cast<DatabaseImpl*>(userData)->unregisterEntity(staticMethod);

							  return true;
						  }, this);
}

inline void Database::DatabaseImpl::registerEnumSubEntities(Enum const& e) noexcept
{
	//Enum values
	e.foreachEnumValue([](EnumValue const& enumValue, void* userData)
					   {
						   reinterpret_cast<DatabaseImpl*>(userData)->registerEntityIdRecursive(enumValue);

						   return true;
					   }, this);
}

inline void Database::DatabaseImpl::unregisterEnumSubEntities(Enum const& e) noexcept
{
	//Enum values
	e.foreachEnumValue([](EnumValue const& enumValue, void* userData)
					   {
						   reinterpret_cast<DatabaseImpl*>(userData)->unregisterEntity(enumValue);

						   return true;
					   }, this);
}

inline void Database::DatabaseImpl::releaseNamespaceIfUnreferenced(std::shared_ptr<Namespace> const& npPtr) noexcept
{
	assert(npPtr.use_count() >= 2);

	// 2: first is this method parameter, the second is the ptr stored in _generatedNamespaces
	if (npPtr.use_count() == 2)
	{
		//This shared pointer is used by database only so we can delete it
		unregisterEntity(*npPtr);

		_generatedNamespaces.erase(npPtr->getId());
	}
}

inline std::shared_ptr<Namespace> Database::DatabaseImpl::getOrCreateNamespace(char const* name, std::size_t id) noexcept
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

		std::shared_ptr<Namespace> const& generatedNamespace = generatedNamespaceIt.first->second;

		//Register the namespace by ID
		registerEntityId(*generatedNamespace.get());

		return generatedNamespace;
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