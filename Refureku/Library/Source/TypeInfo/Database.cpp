#include "Refureku/TypeInfo/Database.h"

#include <iostream>

#include "Refureku/TypeInfo/Entity/EntityCast.h"
#include "Refureku/Exceptions/BadNamespaceFormat.h"
#include "Refureku/Misc/DisableWarningMacros.h"

using namespace rfk;

Database& Database::getInternal() noexcept
{
	static Database database;
	return database;
}

void Database::registerFileLevelEntity(Entity const& entity, bool shouldRegisterSubEntities) noexcept
{
	//Register by id
	registerEntity(entity, shouldRegisterSubEntities);

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

void Database::registerEntity(Entity const& entity, bool shouldRegisterSubEntities) noexcept
{
	_entitiesById.emplace(&entity);

	if (shouldRegisterSubEntities)
	{
		switch (entity.getKind())
		{
			case EEntityKind::Namespace:
				registerSubEntities(static_cast<Namespace const&>(entity));
				break;

			case EEntityKind::Struct:
				[[fallthrough]];
			case EEntityKind::Class:
				registerSubEntities(static_cast<Struct const&>(entity));
				break;

			case EEntityKind::Enum:
				registerSubEntities(static_cast<Enum const&>(entity));
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

			case EEntityKind::Undefined:
				[[fallthrough]];
			default:
				assert(false);	//Should never register a bad kind
				break;
		}
	}
}

void Database::unregisterEntity(Entity const& entity, bool shouldUnregisterSubEntities) noexcept
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

void Database::registerSubEntities(Namespace const& n) noexcept
{
	//Add nested namespaces
	for (Namespace const* nn : n.namespaces)
	{
		registerEntity(*nn, true);
	}

	//Add nested archetypes
	for (Archetype const* na : n.archetypes)
	{
		registerEntity(*na, true);
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

void Database::unregisterSubEntities(Struct const& s) noexcept
{
	//Remove nested archetypes
	for (Archetype const* nestedArchetype : s.nestedArchetypes)
	{
		unregisterEntity(*nestedArchetype, true);
	}

	//Add fields
	for (Entity const& field : s.fields)
	{
		unregisterEntity(field, false);
	}

	for (Entity const& staticField : s.staticFields)
	{
		unregisterEntity(staticField, false);
	}

	//Add methods
	for (Entity const& method : s.methods)
	{
		unregisterEntity(method, false);
	}

	for (Entity const& staticMethod : s.staticMethods)
	{
		unregisterEntity(staticMethod, false);
	}
}

void Database::registerSubEntities(Enum const& e) noexcept
{
	//Enum values
	for (Entity const& enumValue : e.getEnumValues())
	{
		registerEntity(enumValue, false);
	}
}

void Database::unregisterSubEntities(Enum const& e) noexcept
{
	//Enum values
	for (Entity const& enumValue : e.getEnumValues())
	{
		unregisterEntity(enumValue, false);
	}
}

void Database::checkNamespaceRefCount(std::shared_ptr<Namespace> const& npPtr) noexcept
{
	assert(npPtr.use_count() >= 2);

	// 2: first is this method parameter, the second is the ptr stored in _generatedNamespaces
	if (npPtr.use_count() == 2)
	{
		//This shared pointer is used by database only so we can delete it
		unregisterEntity(*npPtr, false);
		
		_generatedNamespaces.erase(std::find_if(_generatedNamespaces.cbegin(),
												_generatedNamespaces.cend(),
												[npPtr](std::shared_ptr<Namespace> const& n) { return npPtr == n; }));
	}
}

std::shared_ptr<Namespace> Database::generateNamespace(char const* name, std::size_t id) noexcept
{
	return _generatedNamespaces.emplace_back(std::make_shared<Namespace>(name, id));
}

Entity const* Database::getEntity(std::size_t id) const noexcept
{
	Entity searching("", id);

	Database::EntitiesById::const_iterator it = _entitiesById.find(&searching);

	return (it != _entitiesById.cend()) ? *it : nullptr;
}

Namespace const* Database::getNamespace(std::size_t id) const noexcept
{
	return entityCast<Namespace>(getEntity(id));
}

Namespace const* Database::getNamespace(std::string namespaceName) const
{
	size_t index = namespaceName.find_first_of(':');

	//Make sure namespaceName has a valid namespace syntax
	if (index != std::string::npos && (index == namespaceName.size() - 1 || namespaceName[index + 1] != ':'))
	{
		throw BadNamespaceFormat("The provided namespace name is ill formed.");
	}

	Entity searchedNamespace(namespaceName.substr(0u, index), 0u);

	Database::NamespacesByName::const_iterator it = _fileLevelNamespacesByName.find(reinterpret_cast<Namespace const*>(&searchedNamespace));

	//Couldn't find first namespace part, abort search
	if (it == _fileLevelNamespacesByName.cend())
	{
		return nullptr;
	}

	Namespace const* result = *it;

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

		result = result->getNamespace(namespaceName.substr(0u, index));
	}

	return result;
}

Archetype const* Database::getArchetype(std::size_t id) const noexcept
{
	return entityCast<Archetype>(getEntity(id));
}

Archetype const* Database::getArchetype(std::string archetypeName) const noexcept
{
	Archetype const* result = getClass(archetypeName);
	
	if (result == nullptr)
	{
		result = getStruct(archetypeName);

		if (result == nullptr)
		{
			result = getEnum(archetypeName);

			if (result == nullptr)
			{
				result = getFundamentalArchetype(std::move(archetypeName));
			}
		}
	}

	return result;
}

Struct const* Database::getStruct(std::size_t id) const noexcept
{
	return entityCast<Struct>(getEntity(id));
}

Struct const* Database::getStruct(std::string structName) const noexcept
{
	Entity searchedStruct(std::move(structName), 0u);

	Database::StructsByName::const_iterator it = _fileLevelStructsByName.find(reinterpret_cast<Struct const*>(&searchedStruct));

	return (it != _fileLevelStructsByName.cend()) ? *it : nullptr;
}

Class const* Database::getClass(std::size_t id) const noexcept
{
	return entityCast<Class>(getEntity(id));
}

Class const* Database::getClass(std::string className) const noexcept
{
	Entity searchedClass(std::move(className), 0u);

	Database::ClassesByName::const_iterator it = _fileLevelClassesByName.find(reinterpret_cast<Class const*>(&searchedClass));

	return (it != _fileLevelClassesByName.cend()) ? *it : nullptr;
}

Enum const* Database::getEnum(std::size_t id) const noexcept
{
	return entityCast<Enum>(getEntity(id));
}

Enum const* Database::getEnum(std::string enumName) const noexcept
{
	Entity searchedEnum(std::move(enumName), 0u);

	Database::EnumsByName::const_iterator it = _fileLevelEnumsByName.find(reinterpret_cast<Enum const*>(&searchedEnum));

	return (it != _fileLevelEnumsByName.cend()) ? *it : nullptr;
}

FundamentalArchetype const* Database::getFundamentalArchetype(std::size_t id) const noexcept
{
	return entityCast<FundamentalArchetype>(getEntity(id));
}

FundamentalArchetype const* Database::getFundamentalArchetype(std::string archetypeName) const noexcept
{
	Entity searchedFundamentalArchetype(std::move(archetypeName), 0u);

	Database::FundamentalArchetypesByName::const_iterator it = _fundamentalArchetypes.find(reinterpret_cast<FundamentalArchetype const*>(&searchedFundamentalArchetype));

	return (it != _fundamentalArchetypes.cend()) ? *it : nullptr;
}

Variable const* Database::getVariable(std::size_t id) const noexcept
{
	return entityCast<Variable>(getEntity(id));
}

Variable const* Database::getVariable(std::string variableName, EVarFlags flags) const noexcept
{
	Entity searchedVariable(std::move(variableName), 0u);

	Database::VariablesByName::const_iterator it = _fileLevelVariablesByName.find(reinterpret_cast<Variable const*>(&searchedVariable));

	return (it != _fileLevelVariablesByName.cend() && ((*it)->flags & flags) == flags) ? *it : nullptr;
}

Function const* Database::getFunction(std::size_t id) const noexcept
{
	return entityCast<Function>(getEntity(id));
}

Function const* Database::getFunction(std::string functionName, EFunctionFlags flags) const noexcept
{
	Entity searchedFunction(std::move(functionName), 0u);

	Database::FunctionsByName::const_iterator it = _fileLevelFunctionsByName.find(reinterpret_cast<Function const*>(&searchedFunction));

	return (it != _fileLevelFunctionsByName.cend() && ((*it)->flags & flags) == flags) ? *it : nullptr;
}

Method const* Database::getMethod(std::size_t id) const noexcept
{
	return entityCast<Method>(getEntity(id));
}

StaticMethod const* Database::getStaticMethod(std::size_t id) const noexcept
{
	return entityCast<StaticMethod>(getEntity(id));
}

Field const* Database::getField(std::size_t id) const noexcept
{
	return entityCast<Field>(getEntity(id));
}

StaticField const* Database::getStaticField(std::size_t id) const noexcept
{
	return entityCast<StaticField>(getEntity(id));
}

EnumValue const* Database::getEnumValue(std::size_t id) const noexcept
{
	return entityCast<EnumValue>(getEntity(id));
}

Database::EntitiesById const& Database::getEntitiesById() const noexcept
{
	return _entitiesById;
}

Database::NamespacesByName const& Database::getFileLevelNamespaces() const noexcept
{
	return _fileLevelNamespacesByName;
}

Database::FundamentalArchetypesByName const& Database::getFundamentalArchetypes() const noexcept
{
	return _fundamentalArchetypes;
}

Database::StructsByName const& Database::getFileLevelStructs() const noexcept
{
	return _fileLevelStructsByName;
}

Database::ClassesByName const& Database::getFileLevelClasses() const noexcept
{
	return _fileLevelClassesByName;
}

Database::EnumsByName const& Database::getFileLevelEnums() const noexcept
{
	return _fileLevelEnumsByName;
}

Database::VariablesByName const& Database::getFileLevelVariables() const noexcept
{
	return _fileLevelVariablesByName;
}

Database::FunctionsByName const& Database::getFileLevelFunctions() const noexcept
{
	return _fileLevelFunctionsByName;
}

Database const& rfk::getDatabase() noexcept
{
	return Database::getInternal();
}