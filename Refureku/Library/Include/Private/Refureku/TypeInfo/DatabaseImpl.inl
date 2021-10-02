/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

void DatabaseAPI::DatabaseImpl::registerFileLevelEntity(EntityAPI const& entity, bool shouldRegisterSubEntities) noexcept
{
	assert(entity.getOuterEntity() == nullptr);

	//Register by id
	registerEntityId(entity, shouldRegisterSubEntities);

	//Register by name
	switch (entity.getKind())
	{
		case EEntityKind::Namespace:
			_fileLevelNamespacesByName.emplace(reinterpret_cast<NamespaceAPI const*>(&entity));
			break;

		case EEntityKind::Struct:
			_fileLevelStructsByName.emplace(reinterpret_cast<StructAPI const*>(&entity));
			break;

		case EEntityKind::Class:
			_fileLevelClassesByName.emplace(reinterpret_cast<ClassAPI const*>(&entity));
			break;

		case EEntityKind::Enum:
			_fileLevelEnumsByName.emplace(reinterpret_cast<EnumAPI const*>(&entity));
			break;

		case EEntityKind::Variable:
			_fileLevelVariablesByName.emplace(reinterpret_cast<VariableAPI const*>(&entity));
			break;

		case EEntityKind::Function:
			_fileLevelFunctionsByName.emplace(reinterpret_cast<FunctionAPI const*>(&entity));
			break;

		case EEntityKind::FundamentalArchetype:
			//_fundamentalArchetypes.emplace(reinterpret_cast<FundamentalArchetype const*>(&entity));	//TODO
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

void DatabaseAPI::DatabaseImpl::unregisterEntity(EntityAPI const& entity, bool shouldUnregisterSubEntities) noexcept
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
				unregisterSubEntities(static_cast<StructAPI const&>(entity));
				break;

			case EEntityKind::Enum:
				unregisterSubEntities(static_cast<EnumAPI const&>(entity));
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
				_fileLevelNamespacesByName.erase(reinterpret_cast<NamespaceAPI const*>(&entity));
				break;

			case EEntityKind::Struct:
				_fileLevelStructsByName.erase(reinterpret_cast<StructAPI const*>(&entity));
				break;

			case EEntityKind::Class:
				_fileLevelClassesByName.erase(reinterpret_cast<ClassAPI const*>(&entity));
				break;

			case EEntityKind::Enum:
				_fileLevelEnumsByName.erase(reinterpret_cast<EnumAPI const*>(&entity));
				break;

			case EEntityKind::Variable:
				_fileLevelVariablesByName.erase(reinterpret_cast<VariableAPI const*>(&entity));
				break;

			case EEntityKind::Function:
				_fileLevelFunctionsByName.erase(reinterpret_cast<FunctionAPI const*>(&entity));
				break;

			case EEntityKind::FundamentalArchetype:
				//_fundamentalArchetypes.erase(reinterpret_cast<FundamentalArchetypeAPI const*>(&entity));	//TODO
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

void DatabaseAPI::DatabaseImpl::registerEntityId(EntityAPI const& entity, bool shouldRegisterSubEntities) noexcept
{
	_entitiesById.emplace(&entity);

	if (shouldRegisterSubEntities)
	{
		switch (entity.getKind())
		{
			case EEntityKind::Struct:
				[[fallthrough]];
			case EEntityKind::Class:
				registerSubEntities(static_cast<StructAPI const&>(entity));
				break;

			case EEntityKind::Enum:
				registerSubEntities(static_cast<EnumAPI const&>(entity));
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

inline void DatabaseAPI::DatabaseImpl::registerSubEntities(StructAPI const& s) noexcept
{
	//Add nested archetypes
	s.foreachNestedArchetype([](ArchetypeAPI const& archetype, void* userData)
							 {
								 reinterpret_cast<DatabaseImpl*>(userData)->registerEntityId(archetype, true);

								 return true;
							 }, this);

	//Add fields
	s.foreachField([](FieldAPI const& field, void* userData)
				   {
					   reinterpret_cast<DatabaseImpl*>(userData)->registerEntityId(field, false);

					   return true;
				   }, this);

	s.foreachStaticField([](StaticFieldAPI const& staticField, void* userData)
						 {
							 reinterpret_cast<DatabaseImpl*>(userData)->registerEntityId(staticField, false);

							 return true;
						 }, this);

	//Add methods
	s.foreachMethod([](MethodAPI const& method, void* userData)
					{
						reinterpret_cast<DatabaseImpl*>(userData)->registerEntityId(method, false);

						return true;
					}, this);

	s.foreachStaticMethod([](StaticMethodAPI const& staticMethod, void* userData)
						  {
							  reinterpret_cast<DatabaseImpl*>(userData)->registerEntityId(staticMethod, false);

							  return true;
						  }, this);
}

inline void DatabaseAPI::DatabaseImpl::unregisterSubEntities(StructAPI const& s) noexcept
{
	//Remove nested archetypes
	s.foreachNestedArchetype([](ArchetypeAPI const& archetype, void* userData)
							 {
								 reinterpret_cast<DatabaseImpl*>(userData)->unregisterEntity(archetype, true);

								 return true;
							 }, this);

	//Remove fields
	s.foreachField([](FieldAPI const& field, void* userData)
				   {
					   reinterpret_cast<DatabaseImpl*>(userData)->unregisterEntity(field, false);

					   return true;
				   }, this);

	s.foreachStaticField([](StaticFieldAPI const& staticField, void* userData)
						 {
							 reinterpret_cast<DatabaseImpl*>(userData)->unregisterEntity(staticField, false);

							 return true;
						 }, this);

	//Remove methods
	s.foreachMethod([](MethodAPI const& method, void* userData)
					{
						reinterpret_cast<DatabaseImpl*>(userData)->unregisterEntity(method, false);

						return true;
					}, this);

	s.foreachStaticMethod([](StaticMethodAPI const& staticMethod, void* userData)
						  {
							  reinterpret_cast<DatabaseImpl*>(userData)->unregisterEntity(staticMethod, false);

							  return true;
						  }, this);
}

inline void DatabaseAPI::DatabaseImpl::registerSubEntities(EnumAPI const& e) noexcept
{
	//Enum values
	e.foreachEnumValue([](EnumValueAPI const& enumValue, void* userData)
					   {
						   reinterpret_cast<DatabaseImpl*>(userData)->registerEntityId(enumValue, false);

						   return true;
					   }, this);
}

inline void DatabaseAPI::DatabaseImpl::unregisterSubEntities(EnumAPI const& e) noexcept
{
	//Enum values
	e.foreachEnumValue([](EnumValueAPI const& enumValue, void* userData)
					   {
						   reinterpret_cast<DatabaseImpl*>(userData)->unregisterEntity(enumValue, false);

						   return true;
					   }, this);
}

inline void DatabaseAPI::DatabaseImpl::checkNamespaceRefCount(std::shared_ptr<NamespaceAPI> const& npPtr) noexcept
{
	assert(npPtr.use_count() >= 2);

	// 2: first is this method parameter, the second is the ptr stored in _generatedNamespaces
	if (npPtr.use_count() == 2)
	{
		//This shared pointer is used by database only so we can delete it
		unregisterEntity(*npPtr, false);

		for (auto it = _generatedNamespaces.cbegin(); it != _generatedNamespaces.cend(); it++)
		{
			if (*it == npPtr)
			{
				_generatedNamespaces.erase(it);
				return;
			}
		}
	}
}

inline std::shared_ptr<NamespaceAPI> DatabaseAPI::DatabaseImpl::generateNamespace(char const* name, std::size_t id) noexcept
{
	return _generatedNamespaces.emplace_back(std::make_shared<NamespaceAPI>(name, id));
}

inline DatabaseAPI::DatabaseImpl::EntitiesById const& DatabaseAPI::DatabaseImpl::getEntitiesById() const noexcept
{
	return _entitiesById;
}

inline DatabaseAPI::DatabaseImpl::NamespacesByName const& DatabaseAPI::DatabaseImpl::getFileLevelNamespacesByName() const noexcept
{
	return _fileLevelNamespacesByName;
}

//inline DatabaseAPI::DatabaseImpl::FundamentalArchetypesByName const&	DatabaseAPI::DatabaseImpl::getFundamentalArchetypesByName() const noexcept
//{
//	return _fundamentalArchetypes;
//}

inline DatabaseAPI::DatabaseImpl::StructsByName const& DatabaseAPI::DatabaseImpl::getFileLevelStructsByName() const noexcept
{
	return _fileLevelStructsByName;
}

inline DatabaseAPI::DatabaseImpl::ClassesByName const& DatabaseAPI::DatabaseImpl::getFileLevelClassesByName() const	noexcept
{
	return _fileLevelClassesByName;
}

inline DatabaseAPI::DatabaseImpl::EnumsByName const& DatabaseAPI::DatabaseImpl::getFileLevelEnumsByName() const noexcept
{
	return _fileLevelEnumsByName;
}

inline DatabaseAPI::DatabaseImpl::VariablesByName const& DatabaseAPI::DatabaseImpl::getFileLevelVariablesByName() const noexcept
{
	return _fileLevelVariablesByName;
}

inline DatabaseAPI::DatabaseImpl::FunctionsByName const& DatabaseAPI::DatabaseImpl::getFileLevelFunctionsByName() const noexcept
{
	return _fileLevelFunctionsByName;
}

inline DatabaseAPI::DatabaseImpl::GenNamespaces const& DatabaseAPI::DatabaseImpl::getGeneratedNamespaces() const noexcept
{
	return _generatedNamespaces;
}