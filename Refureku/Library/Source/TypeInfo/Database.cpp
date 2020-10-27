#include "Refureku/TypeInfo/Database.h"

#include <iostream>

#include "Refureku/Exceptions/BadNamespaceFormat.h"
#include "Refureku/Misc/DisableWarningMacros.h"

using namespace rfk;

//Init database containers BEFORE any other code so that reflected classes can register at startup
#if defined(__GNUC__) || defined(__clang__)

Database::EntitiesById					Database::_entitiesById					__attribute__((init_priority(101)));
Database::NamespacesByName				Database::_fileLevelNamespacesByName	__attribute__((init_priority(101)));
Database::FundamentalArchetypesByName	Database::_fundamentalArchetypes		__attribute__((init_priority(101)));
Database::StructsByName					Database::_fileLevelStructsByName		__attribute__((init_priority(101)));
Database::ClassesByName					Database::_fileLevelClassesByName		__attribute__((init_priority(101)));
Database::EnumsByName					Database::_fileLevelEnumsByName			__attribute__((init_priority(101)));
Database::VariablesByName				Database::_fileLevelVariablesByName		__attribute__((init_priority(101)));
Database::FunctionsByName				Database::_fileLevelFunctionsByName		__attribute__((init_priority(101)));
Database::GenNamespaces					Database::_generatedNamespaces			__attribute__((init_priority(101)));

#elif defined(_MSC_VER)

__RFK_DISABLE_WARNING_PUSH
__RFK_DISABLE_WARNING_INIT_SEG

#pragma init_seg(lib)

__RFK_DISABLE_WARNING_POP

Database::EntitiesById					Database::_entitiesById;
Database::NamespacesByName				Database::_fileLevelNamespacesByName;
Database::FundamentalArchetypesByName	Database::_fundamentalArchetypes;
Database::StructsByName					Database::_fileLevelStructsByName;
Database::ClassesByName					Database::_fileLevelClassesByName;
Database::EnumsByName					Database::_fileLevelEnumsByName;
Database::VariablesByName				Database::_fileLevelVariablesByName;
Database::FunctionsByName				Database::_fileLevelFunctionsByName;
Database::GenNamespaces					Database::_generatedNamespaces;

#else

Database::EntitiesById					Database::_entitiesById;
Database::NamespacesByName				Database::_fileLevelNamespacesByName;
Database::FundamentalArchetypesByName	Database::_fundamentalArchetypes;
Database::StructsByName					Database::_fileLevelStructsByName;
Database::ClassesByName					Database::_fileLevelClassesByName;
Database::EnumsByName					Database::_fileLevelEnumsByName;
Database::VariablesByName				Database::_fileLevelVariablesByName;
Database::FunctionsByName				Database::_fileLevelFunctionsByName;
Database::GenNamespaces					Database::_generatedNamespaces;

#endif

void Database::registerFileLevelEntity(Entity const& entity, bool shouldRegisterSubEntities) noexcept
{
	//Register by id
	registerEntity(entity, shouldRegisterSubEntities);

	//Register by name
	switch (entity.kind)
	{
		case Entity::EKind::Namespace:
			_fileLevelNamespacesByName.emplace(reinterpret_cast<Namespace const*>(&entity));
			break;

		case Entity::EKind::Struct:
			_fileLevelStructsByName.emplace(reinterpret_cast<Struct const*>(&entity));
			break;

		case Entity::EKind::Class:
			_fileLevelClassesByName.emplace(reinterpret_cast<Class const*>(&entity));
			break;

		case Entity::EKind::Enum:
			_fileLevelEnumsByName.emplace(reinterpret_cast<Enum const*>(&entity));
			break;

		case Entity::EKind::Variable:
			_fileLevelVariablesByName.emplace(reinterpret_cast<Variable const*>(&entity));
			break;

		case Entity::EKind::Function:
			_fileLevelFunctionsByName.emplace(reinterpret_cast<Function const*>(&entity));
			break;

		case Entity::EKind::FundamentalArchetype:
			_fundamentalArchetypes.emplace(reinterpret_cast<FundamentalArchetype const*>(&entity));
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
		switch (entity.kind)
		{
			case Entity::EKind::Namespace:
				registerSubEntities(static_cast<Namespace const&>(entity));
				break;

			case Entity::EKind::Struct:
				[[fallthrough]];
			case Entity::EKind::Class:
				registerSubEntities(static_cast<Struct const&>(entity));
				break;

			case Entity::EKind::Enum:
				registerSubEntities(static_cast<Enum const&>(entity));
				break;

			case Entity::EKind::FundamentalArchetype:
				[[fallthrough]];
			case Entity::EKind::Variable:
				[[fallthrough]];
			case Entity::EKind::Field:
				[[fallthrough]];
			case Entity::EKind::Function:
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

void Database::unregisterEntity(Entity const& entity, bool shouldUnregisterSubEntities) noexcept
{
	if (shouldUnregisterSubEntities)
	{
		switch (entity.kind)
		{
			case Entity::EKind::Namespace:
				assert(false); //This situation should never happen
				break;

			case Entity::EKind::Struct:
				[[fallthrough]];
			case Entity::EKind::Class:
				unregisterSubEntities(static_cast<Struct const&>(entity));
				break;

			case Entity::EKind::Enum:
				unregisterSubEntities(static_cast<Enum const&>(entity));
				break;

			case Entity::EKind::Variable:
				[[fallthrough]];
			case Entity::EKind::Field:
				[[fallthrough]];
			case Entity::EKind::Function:
				[[fallthrough]];
			case Entity::EKind::Method:
				[[fallthrough]];
			case Entity::EKind::EnumValue:
				[[fallthrough]];
			case Entity::EKind::FundamentalArchetype:
				//No sub entity to unregister
				break;

			case Entity::EKind::Undefined:
				[[fallthrough]];
			default:
				assert(false);	//Should never register a bad kind
				break;
		}
	}

	//Remove this entity from the list of registered entity ids
	_entitiesById.erase(&entity);

	if (entity.outerEntity == nullptr)
	{
		switch (entity.kind)
		{
			case Entity::EKind::Namespace:
				_fileLevelNamespacesByName.erase(reinterpret_cast<Namespace const*>(&entity));
				break;

			case Entity::EKind::Struct:
				_fileLevelStructsByName.erase(reinterpret_cast<Struct const*>(&entity));
				break;

			case Entity::EKind::Class:
				_fileLevelClassesByName.erase(reinterpret_cast<Class const*>(&entity));
				break;

			case Entity::EKind::Enum:
				_fileLevelEnumsByName.erase(reinterpret_cast<Enum const*>(&entity));
				break;

			case Entity::EKind::Variable:
				_fileLevelVariablesByName.erase(reinterpret_cast<Variable const*>(&entity));
				break;

			case Entity::EKind::Function:
				_fileLevelFunctionsByName.erase(reinterpret_cast<Function const*>(&entity));
				break;

			case Entity::EKind::FundamentalArchetype:
				_fundamentalArchetypes.erase(reinterpret_cast<FundamentalArchetype const*>(&entity));
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
	for (Entity const& enumValue : e.values)
	{
		registerEntity(enumValue, false);
	}
}

void Database::unregisterSubEntities(Enum const& e) noexcept
{
	//Enum values
	for (Entity const& enumValue : e.values)
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

std::shared_ptr<Namespace> Database::generateNamespace(char const* name, uint64 id) noexcept
{
	return _generatedNamespaces.emplace_back(std::make_shared<Namespace>(name, id));
}

Entity const* Database::getEntity(uint64 id) noexcept
{
	Entity searching("", id);

	Database::EntitiesById::const_iterator it = _entitiesById.find(&searching);

	return (it != _entitiesById.cend()) ? *it : nullptr;
}

Namespace const* Database::getNamespace(std::string namespaceName)
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

Archetype const* Database::getArchetype(std::string archetypeName) noexcept
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

Struct const* Database::getStruct(std::string structName) noexcept
{
	Entity searchedStruct(std::move(structName), 0u);

	Database::StructsByName::const_iterator it = _fileLevelStructsByName.find(reinterpret_cast<Struct const*>(&searchedStruct));

	return (it != _fileLevelStructsByName.cend()) ? *it : nullptr;
}

Class const* Database::getClass(std::string className) noexcept
{
	Entity searchedClass(std::move(className), 0u);

	Database::ClassesByName::const_iterator it = _fileLevelClassesByName.find(reinterpret_cast<Class const*>(&searchedClass));

	return (it != _fileLevelClassesByName.cend()) ? *it : nullptr;
}

Enum const* Database::getEnum(std::string enumName) noexcept
{
	Entity searchedEnum(std::move(enumName), 0u);

	Database::EnumsByName::const_iterator it = _fileLevelEnumsByName.find(reinterpret_cast<Enum const*>(&searchedEnum));

	return (it != _fileLevelEnumsByName.cend()) ? *it : nullptr;
}

FundamentalArchetype const* Database::getFundamentalArchetype(std::string archetypeName) noexcept
{
	Entity searchedFundamentalArchetype(std::move(archetypeName), 0u);

	Database::FundamentalArchetypesByName::const_iterator it = _fundamentalArchetypes.find(reinterpret_cast<FundamentalArchetype const*>(&searchedFundamentalArchetype));

	return (it != _fundamentalArchetypes.cend()) ? *it : nullptr;
}

Variable const* Database::getVariable(std::string variableName, EVarFlags flags) noexcept
{
	Entity searchedVariable(std::move(variableName), 0u);

	Database::VariablesByName::const_iterator it = _fileLevelVariablesByName.find(reinterpret_cast<Variable const*>(&searchedVariable));

	return (it != _fileLevelVariablesByName.cend() && ((*it)->flags & flags) == flags) ? *it : nullptr;
}

Function const* Database::getFunction(std::string functionName, EFunctionFlags flags) noexcept
{
	Entity searchedFunction(std::move(functionName), 0u);

	Database::FunctionsByName::const_iterator it = _fileLevelFunctionsByName.find(reinterpret_cast<Function const*>(&searchedFunction));

	return (it != _fileLevelFunctionsByName.cend() && ((*it)->flags & flags) == flags) ? *it : nullptr;
}

void Database::clear() noexcept
{
	_entitiesById.clear();
	_fileLevelNamespacesByName.clear();
	_fileLevelStructsByName.clear();
	_fileLevelClassesByName.clear();
	_fileLevelEnumsByName.clear();
	_fileLevelVariablesByName.clear();
	_fileLevelFunctionsByName.clear();

	//Don't clear _fundamentalArchetypes because it will never re-register
}

Database::EntitiesById const& Database::getEntitiesById() noexcept
{
	return _entitiesById;
}

Database::NamespacesByName const& Database::getFileLevelNamespaces() noexcept
{
	return _fileLevelNamespacesByName;
}

Database::FundamentalArchetypesByName const& Database::getFundamentalArchetypes() noexcept
{
	return _fundamentalArchetypes;
}

Database::StructsByName const& Database::getFileLevelStructs() noexcept
{
	return _fileLevelStructsByName;
}

Database::ClassesByName const& Database::getFileLevelClasses() noexcept
{
	return _fileLevelClassesByName;
}

Database::EnumsByName const& Database::getFileLevelEnums() noexcept
{
	return _fileLevelEnumsByName;
}

Database::VariablesByName const& Database::getFileLevelVariables() noexcept
{
	return _fileLevelVariablesByName;
}

Database::FunctionsByName const& Database::getFileLevelFunctions() noexcept
{
	return _fileLevelFunctionsByName;
}