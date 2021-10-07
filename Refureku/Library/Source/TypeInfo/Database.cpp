#include "Refureku/TypeInfo/Database.h"

#include <string>

#include "Refureku/TypeInfo/DatabaseImpl.h"
#include "Refureku/TypeInfo/Entity/EntityUtility.h"
#include "Refureku/TypeInfo/Entity/EntityCast.h"
#include "Refureku/Exceptions/BadNamespaceFormat.h"

using namespace rfk;

Database::Database() noexcept:
	_pimpl(new DatabaseImpl())
{
}

Database::~Database() noexcept = default;

Database& Database::getInstance() noexcept
{
	static Database database;
	
	return database;
}

Entity const* Database::getEntityById(std::size_t id) const noexcept
{
	return EntityUtility::getEntityPtrById(_pimpl->getEntitiesById(), id);
}

Namespace const* Database::getNamespaceById(std::size_t id) const noexcept
{
	return entityCast<Namespace>(getEntityById(id));
}

Namespace const* Database::getNamespaceByName(char const* name) const
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

Namespace const* Database::getNamespaceByPredicate(Predicate<Namespace> predicate, void* userData) const
{
	return EntityUtility::getEntityByPredicate(_pimpl->getFileLevelNamespacesByName(), predicate, userData);
}

Vector<Namespace const*> Database::getNamespacesByPredicate(Predicate<Namespace>	predicate, void* userData) const
{
	return EntityUtility::getEntitiesByPredicate(_pimpl->getFileLevelNamespacesByName(), predicate, userData);
}

bool Database::foreachFileLevelNamespace(Visitor<Namespace> visitor, void* userData) const
{
	return EntityUtility::foreachEntity(_pimpl->getFileLevelNamespacesByName(), visitor, userData);
}

Archetype const* Database::getArchetypeById(std::size_t id) const noexcept
{
	return entityCast<Archetype>(getEntityById(id));
}

Archetype const* Database::getArchetypeByName(char const* name) const noexcept
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

Vector<Archetype const*> Database::getArchetypesByPredicate(Predicate<Archetype> predicate, void* userData) const
{
	Vector<Archetype const*> result = EntityUtility::getEntitiesByPredicate(_pimpl->getFileLevelEnumsByName(), predicate, userData);

	result.push_back(EntityUtility::getEntitiesByPredicate(_pimpl->getFileLevelStructsByName(), predicate, userData));
	result.push_back(EntityUtility::getEntitiesByPredicate(_pimpl->getFileLevelClassesByName(), predicate, userData));

	return result;
}

Struct const* Database::getStructById(std::size_t id) const noexcept
{
	return entityCast<Struct>(getEntityById(id));
}

Struct const* Database::getStructByName(char const* name) const noexcept
{
	return EntityUtility::getEntityByName(_pimpl->getFileLevelStructsByName(), name);
}

Vector<Struct const*> Database::getStructsByPredicate(Predicate<Struct> predicate, void* userData) const
{
	return EntityUtility::getEntitiesByPredicate(_pimpl->getFileLevelStructsByName(), predicate, userData);
}

bool Database::foreachFileLevelStruct(Visitor<Struct> visitor, void* userData) const
{
	return EntityUtility::foreachEntity(_pimpl->getFileLevelStructsByName(), visitor, userData);
}

Class const* Database::getClassById(std::size_t id) const noexcept
{
	return entityCast<Class>(getEntityById(id));
}

Class const* Database::getClassByName(char const* name) const noexcept
{
	return EntityUtility::getEntityByName(_pimpl->getFileLevelClassesByName(), name);
}

Vector<Class const*> Database::getClassesByPredicate(Predicate<Class> predicate, void* userData) const
{
	return EntityUtility::getEntitiesByPredicate(_pimpl->getFileLevelClassesByName(), predicate, userData);
}

bool Database::foreachFileLevelClass(Visitor<Class> visitor, void* userData) const
{
	return EntityUtility::foreachEntity(_pimpl->getFileLevelClassesByName(), visitor, userData);
}

Enum const* Database::getEnumById(std::size_t id) const noexcept
{
	return entityCast<Enum>(getEntityById(id));
}

Enum const* Database::getEnumByName(char const* name) const noexcept
{
	return EntityUtility::getEntityByName(_pimpl->getFileLevelEnumsByName(), name);
}

Vector<Enum const*> Database::getEnumsByPredicate(Predicate<Enum> predicate, void* userData) const
{
	return EntityUtility::getEntitiesByPredicate(_pimpl->getFileLevelEnumsByName(), predicate, userData);
}

bool Database::foreachFileLevelEnum(Visitor<Enum> visitor, void* userData) const
{
	return EntityUtility::foreachEntity(_pimpl->getFileLevelEnumsByName(), visitor, userData);
}

FundamentalArchetype const* Database::getFundamentalArchetypeById(std::size_t id) const noexcept
{
	return entityCast<FundamentalArchetype>(getEntityById(id));
}

FundamentalArchetype const* Database::getFundamentalArchetypeByName(char const* name) const noexcept
{
	return EntityUtility::getEntityByName(_pimpl->getFundamentalArchetypesByName(), name);
}

Variable const* Database::getVariableById(std::size_t id) const noexcept
{
	return entityCast<Variable>(getEntityById(id));
}

Variable const* Database::getVariableByName(char const* name, EVarFlags flags) const noexcept
{
	return EntityUtility::getEntityByNameAndPredicate(_pimpl->getFileLevelVariablesByName(),
													  name,
													  [flags](Variable const& var) { return (var.getFlags() & flags) == flags; });
}

Vector<Variable const*> Database::getVariablesByPredicate(Predicate<Variable> predicate, void* userData) const
{
	return EntityUtility::getEntitiesByPredicate(_pimpl->getFileLevelVariablesByName(), predicate, userData);
}

bool Database::foreachFileLevelVariable(Visitor<Variable> visitor, void* userData) const
{
	return EntityUtility::foreachEntity(_pimpl->getFileLevelVariablesByName(), visitor, userData);
}

Function const* Database::getFunctionById(std::size_t id) const noexcept
{
	return entityCast<Function>(getEntityById(id));
}

Function const* Database::getFunctionByName(char const* name, EFunctionFlags flags) const noexcept
{
	return EntityUtility::getEntityByNameAndPredicate(_pimpl->getFileLevelFunctionsByName(),
													  name,
													  [flags](Function const& func) { return (func.getFlags() & flags) == flags; });
}

Vector<Function const*> Database::getFunctionsByPredicate(Predicate<Function> predicate, void* userData) const
{
	return EntityUtility::getEntitiesByPredicate(_pimpl->getFileLevelFunctionsByName(), predicate, userData);
}

bool Database::foreachFileLevelFunction(Visitor<Function> visitor, void* userData) const
{
	return EntityUtility::foreachEntity(_pimpl->getFileLevelFunctionsByName(), visitor, userData);
}

Method const* Database::getMethodById(std::size_t id) const noexcept
{
	return entityCast<Method>(getEntityById(id));
}

StaticMethod const* Database::getStaticMethodById(std::size_t id) const noexcept
{
	return entityCast<StaticMethod>(getEntityById(id));
}

Field const* Database::getFieldById(std::size_t id) const noexcept
{
	return entityCast<Field>(getEntityById(id));
}

StaticField const* Database::getStaticFieldById(std::size_t id) const noexcept
{
	return entityCast<StaticField>(getEntityById(id));
}

EnumValue const* Database::getEnumValueById(std::size_t id) const noexcept
{
	return entityCast<EnumValue>(getEntityById(id));
}

Database const& rfk::getDatabase() noexcept
{
	return Database::getInstance();
}