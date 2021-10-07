#include "Refureku/TypeInfo/DatabaseAPI.h"

#include <string>

#include "Refureku/TypeInfo/DatabaseImpl.h"
#include "Refureku/TypeInfo/Entity/EntityUtility.h"
#include "Refureku/TypeInfo/Entity/EntityCast.h"
#include "Refureku/Exceptions/BadNamespaceFormat.h"

using namespace rfk;

DatabaseAPI::DatabaseAPI() noexcept:
	_pimpl(new DatabaseImpl())
{
}

DatabaseAPI::~DatabaseAPI() noexcept = default;

DatabaseAPI& DatabaseAPI::getInstance() noexcept
{
	static DatabaseAPI database;
	
	return database;
}

Entity const* DatabaseAPI::getEntityById(std::size_t id) const noexcept
{
	return EntityUtility::getEntityPtrById(_pimpl->getEntitiesById(), id);
}

Namespace const* DatabaseAPI::getNamespaceById(std::size_t id) const noexcept
{
	return entityCast<Namespace>(getEntityById(id));
}

Namespace const* DatabaseAPI::getNamespaceByName(char const* name) const
{
	std::string namespaceName(name);

	std::size_t index = namespaceName.find_first_of(':');

	//Make sure namespaceName has a valid namespace syntax
	if (index != std::string::npos && (index == namespaceName.size() - 1 || namespaceName[index + 1] != ':'))
	{
		throw BadNamespaceFormat("The provided namespace name is ill formed.");
	}

	Namespace const* result = EntityUtility::getEntityByName(_pimpl->getFileLevelNamespacesByName(), namespaceName.substr(0u, index).data());

	//Couldn't find first namespace part, abort search
	if (result == nullptr)
	{
		return nullptr;
	}

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

		result = result->getNamespaceByName(namespaceName.substr(0u, index).data());
	}

	return result;
}

bool DatabaseAPI::foreachFileLevelNamespace(Visitor<Namespace> visitor, void* userData) const
{
	return EntityUtility::foreachEntity(_pimpl->getFileLevelNamespacesByName(), visitor, userData);
}

Archetype const* DatabaseAPI::getArchetypeById(std::size_t id) const noexcept
{
	return entityCast<Archetype>(getEntityById(id));
}

Archetype const* DatabaseAPI::getArchetypeByName(char const* name) const noexcept
{
	Archetype const* result = getClassByName(name);

	if (result == nullptr)
	{
		result = getStructByName(name);

		if (result == nullptr)
		{
			result = getEnumByName(name);

			if (result == nullptr)
			{
				result = getFundamentalArchetypeByName(name);
			}
		}
	}

	return result;
}

Struct const* DatabaseAPI::getStructById(std::size_t id) const noexcept
{
	return entityCast<Struct>(getEntityById(id));
}

Struct const* DatabaseAPI::getStructByName(char const* name) const noexcept
{
	return EntityUtility::getEntityByName(_pimpl->getFileLevelStructsByName(), name);
}

bool DatabaseAPI::foreachFileLevelStruct(Visitor<Struct> visitor, void* userData) const
{
	return EntityUtility::foreachEntity(_pimpl->getFileLevelStructsByName(), visitor, userData);
}

Class const* DatabaseAPI::getClassById(std::size_t id) const noexcept
{
	return entityCast<Class>(getEntityById(id));
}

Class const* DatabaseAPI::getClassByName(char const* name) const noexcept
{
	return EntityUtility::getEntityByName(_pimpl->getFileLevelClassesByName(), name);
}

bool DatabaseAPI::foreachFileLevelClass(Visitor<Class> visitor, void* userData) const
{
	return EntityUtility::foreachEntity(_pimpl->getFileLevelClassesByName(), visitor, userData);
}

Enum const* DatabaseAPI::getEnumById(std::size_t id) const noexcept
{
	return entityCast<Enum>(getEntityById(id));
}

Enum const* DatabaseAPI::getEnumByName(char const* name) const noexcept
{
	return EntityUtility::getEntityByName(_pimpl->getFileLevelEnumsByName(), name);
}

bool DatabaseAPI::foreachFileLevelEnum(Visitor<Enum> visitor, void* userData) const
{
	return EntityUtility::foreachEntity(_pimpl->getFileLevelEnumsByName(), visitor, userData);
}

FundamentalArchetype const* DatabaseAPI::getFundamentalArchetypeById(std::size_t id) const noexcept
{
	return entityCast<FundamentalArchetype>(getEntityById(id));
}

FundamentalArchetype const* DatabaseAPI::getFundamentalArchetypeByName(char const* name) const noexcept
{
	return EntityUtility::getEntityByName(_pimpl->getFundamentalArchetypesByName(), name);
}

Variable const* DatabaseAPI::getVariableById(std::size_t id) const noexcept
{
	return entityCast<Variable>(getEntityById(id));
}

Variable const* DatabaseAPI::getVariableByName(char const* name, EVarFlags flags) const noexcept
{
	return EntityUtility::getEntityByNameAndPredicate(_pimpl->getFileLevelVariablesByName(),
													  name,
													  [flags](Variable const& var) { return (var.getFlags() & flags) == flags; });
}

bool DatabaseAPI::foreachFileLevelVariable(Visitor<Variable> visitor, void* userData) const
{
	return EntityUtility::foreachEntity(_pimpl->getFileLevelVariablesByName(), visitor, userData);
}

Function const* DatabaseAPI::getFunctionById(std::size_t id) const noexcept
{
	return entityCast<Function>(getEntityById(id));
}

Function const* DatabaseAPI::getFunctionByName(char const* name, EFunctionFlags flags) const noexcept
{
	return EntityUtility::getEntityByNameAndPredicate(_pimpl->getFileLevelFunctionsByName(),
													  name,
													  [flags](Function const& func) { return (func.getFlags() & flags) == flags; });
}

bool DatabaseAPI::foreachFileLevelFunction(Visitor<Function> visitor, void* userData) const
{
	return EntityUtility::foreachEntity(_pimpl->getFileLevelFunctionsByName(), visitor, userData);
}

Method const* DatabaseAPI::getMethodById(std::size_t id) const noexcept
{
	return entityCast<Method>(getEntityById(id));
}

StaticMethod const* DatabaseAPI::getStaticMethodById(std::size_t id) const noexcept
{
	return entityCast<StaticMethod>(getEntityById(id));
}

Field const* DatabaseAPI::getFieldById(std::size_t id) const noexcept
{
	return entityCast<Field>(getEntityById(id));
}

StaticField const* DatabaseAPI::getStaticFieldById(std::size_t id) const noexcept
{
	return entityCast<StaticField>(getEntityById(id));
}

EnumValue const* DatabaseAPI::getEnumValueById(std::size_t id) const noexcept
{
	return entityCast<EnumValue>(getEntityById(id));
}

DatabaseAPI const& rfk::getDatabaseAPI() noexcept
{
	return DatabaseAPI::getInstance();
}