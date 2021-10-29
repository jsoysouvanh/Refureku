#include "Refureku/TypeInfo/Database.h"

#include <string>

#include "Refureku/TypeInfo/DatabaseImpl.h"
#include "Refureku/Misc/Algorithm.h"
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
	return Algorithm::getEntityPtrById(_pimpl->getEntitiesById(), id);
}

Namespace const* Database::getNamespaceById(std::size_t id) const noexcept
{
	return namespaceCast(getEntityById(id));
}

Namespace const* Database::getNamespaceByName(char const* name) const
{
	std::string namespaceName(name);

	std::size_t index = namespaceName.find_first_of(':');

	//Make sure namespaceName has a valid namespace syntax
	if (index != std::string::npos && (index == 0 || index == namespaceName.size() - 1 || namespaceName[index + 1] != ':'))
	{
		throw BadNamespaceFormat("The provided namespace name is ill formed.");
	}

	Namespace const* result = Algorithm::getEntityByName(_pimpl->getFileLevelNamespacesByName(), namespaceName.substr(0u, index).data());

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

Namespace const* Database::getFileLevelNamespaceByPredicate(Predicate<Namespace> predicate, void* userData) const
{
	return Algorithm::getItemByPredicate(_pimpl->getFileLevelNamespacesByName(), predicate, userData);
}

Vector<Namespace const*> Database::getFileLevelNamespacesByPredicate(Predicate<Namespace>	predicate, void* userData) const
{
	return Algorithm::getItemsByPredicate(_pimpl->getFileLevelNamespacesByName(), predicate, userData);
}

bool Database::foreachFileLevelNamespace(Visitor<Namespace> visitor, void* userData) const
{
	return Algorithm::foreach(_pimpl->getFileLevelNamespacesByName(), visitor, userData);
}

std::size_t Database::getFileLevelNamespacesCount() const noexcept
{
	return _pimpl->getFileLevelNamespacesByName().size();
}

Archetype const* Database::getArchetypeById(std::size_t id) const noexcept
{
	return archetypeCast(getEntityById(id));
}

Archetype const* Database::getFileLevelArchetypeByName(char const* name) const noexcept
{
	Archetype const* result = getFileLevelClassByName(name);

	if (result == nullptr)
	{
		result = getFileLevelStructByName(name);

		if (result == nullptr)
		{
			result = getFileLevelEnumByName(name);

			if (result == nullptr)
			{
				result = getFundamentalArchetypeByName(name);
			}
		}
	}

	return result;
}

Vector<Archetype const*> Database::getFileLevelArchetypesByPredicate(Predicate<Archetype> predicate, void* userData) const
{
	Vector<Archetype const*> result = Algorithm::getItemsByPredicate(_pimpl->getFileLevelEnumsByName(), predicate, userData);

	result.push_back(Algorithm::getItemsByPredicate(_pimpl->getFileLevelStructsByName(), predicate, userData));
	result.push_back(Algorithm::getItemsByPredicate(_pimpl->getFileLevelClassesByName(), predicate, userData));

	return result;
}

Struct const* Database::getStructById(std::size_t id) const noexcept
{
	Struct const* result = structCast(getEntityById(id));

	return (result != nullptr && result->getKind() == EEntityKind::Struct) ? result : nullptr;
}

Struct const* Database::getFileLevelStructByName(char const* name) const noexcept
{
	return Algorithm::getEntityByName(_pimpl->getFileLevelStructsByName(), name);
}

Struct const* Database::getFileLevelStructByPredicate(Predicate<Struct>	predicate, void* userData) const
{
	return Algorithm::getItemByPredicate(_pimpl->getFileLevelStructsByName(), predicate, userData);
}

Vector<Struct const*> Database::getFileLevelStructsByPredicate(Predicate<Struct> predicate, void* userData) const
{
	return Algorithm::getItemsByPredicate(_pimpl->getFileLevelStructsByName(), predicate, userData);
}

bool Database::foreachFileLevelStruct(Visitor<Struct> visitor, void* userData) const
{
	return Algorithm::foreach(_pimpl->getFileLevelStructsByName(), visitor, userData);
}

std::size_t Database::getFileLevelStructsCount() const noexcept
{
	return _pimpl->getFileLevelStructsByName().size();
}

Class const* Database::getClassById(std::size_t id) const noexcept
{
	return classCast(getEntityById(id));
}

Class const* Database::getFileLevelClassByName(char const* name) const noexcept
{
	return Algorithm::getEntityByName(_pimpl->getFileLevelClassesByName(), name);
}

Struct const* Database::getFileLevelClassByPredicate(Predicate<Struct>	predicate, void* userData) const
{
	return Algorithm::getItemByPredicate(_pimpl->getFileLevelClassesByName(), predicate, userData);
}

Vector<Class const*> Database::getFileLevelClassesByPredicate(Predicate<Class> predicate, void* userData) const
{
	return Algorithm::getItemsByPredicate(_pimpl->getFileLevelClassesByName(), predicate, userData);
}

bool Database::foreachFileLevelClass(Visitor<Class> visitor, void* userData) const
{
	return Algorithm::foreach(_pimpl->getFileLevelClassesByName(), visitor, userData);
}

std::size_t Database::getFileLevelClassesCount() const noexcept
{
	return _pimpl->getFileLevelClassesByName().size();
}

Enum const* Database::getEnumById(std::size_t id) const noexcept
{
	return enumCast(getEntityById(id));
}

Enum const* Database::getFileLevelEnumByName(char const* name) const noexcept
{
	return Algorithm::getEntityByName(_pimpl->getFileLevelEnumsByName(), name);
}

Enum const* Database::getFileLevelEnumByPredicate(Predicate<Enum> predicate, void* userData) const
{
	return Algorithm::getItemByPredicate(_pimpl->getFileLevelEnumsByName(), predicate, userData);
}

Vector<Enum const*> Database::getFileLevelEnumsByPredicate(Predicate<Enum> predicate, void* userData) const
{
	return Algorithm::getItemsByPredicate(_pimpl->getFileLevelEnumsByName(), predicate, userData);
}

bool Database::foreachFileLevelEnum(Visitor<Enum> visitor, void* userData) const
{
	return Algorithm::foreach(_pimpl->getFileLevelEnumsByName(), visitor, userData);
}

std::size_t Database::getFileLevelEnumsCount() const noexcept
{
	return _pimpl->getFileLevelEnumsByName().size();
}

FundamentalArchetype const* Database::getFundamentalArchetypeById(std::size_t id) const noexcept
{
	return fundamentalArchetypeCast(getEntityById(id));
}

FundamentalArchetype const* Database::getFundamentalArchetypeByName(char const* name) const noexcept
{
	return Algorithm::getEntityByName(_pimpl->getFundamentalArchetypesByName(), name);
}

Variable const* Database::getVariableById(std::size_t id) const noexcept
{
	return variableCast(getEntityById(id));
}

Variable const* Database::getFileLevelVariableByName(char const* name, EVarFlags flags) const noexcept
{
	return Algorithm::getEntityByNameAndPredicate(_pimpl->getFileLevelVariablesByName(),
													  name,
													  [flags](Variable const& var) { return (var.getFlags() & flags) == flags; });
}

Variable const* Database::getFileLevelVariableByPredicate(Predicate<Variable> predicate, void* userData) const
{
	return Algorithm::getItemByPredicate(_pimpl->getFileLevelVariablesByName(), predicate, userData);
}

Vector<Variable const*> Database::getFileLevelVariablesByPredicate(Predicate<Variable> predicate, void* userData) const
{
	return Algorithm::getItemsByPredicate(_pimpl->getFileLevelVariablesByName(), predicate, userData);
}

bool Database::foreachFileLevelVariable(Visitor<Variable> visitor, void* userData) const
{
	return Algorithm::foreach(_pimpl->getFileLevelVariablesByName(), visitor, userData);
}

std::size_t Database::getFileLevelVariablesCount() const noexcept
{
	return _pimpl->getFileLevelVariablesByName().size();
}

Function const* Database::getFunctionById(std::size_t id) const noexcept
{
	return functionCast(getEntityById(id));
}

Function const* Database::getFileLevelFunctionByName(char const* name, EFunctionFlags flags) const noexcept
{
	return Algorithm::getEntityByNameAndPredicate(_pimpl->getFileLevelFunctionsByName(),
													  name,
													  [flags](Function const& func) { return (func.getFlags() & flags) == flags; });
}

Vector<Function const*> Database::getFileLevelFunctionsByName(char const* name, EFunctionFlags flags) const noexcept
{
	return Algorithm::getEntitiesByNameAndPredicate(_pimpl->getFileLevelFunctionsByName(),
														name,
														[flags](Function const& func) { return (func.getFlags() & flags) == flags; });
}

Function const* Database::getFileLevelFunctionByPredicate(Predicate<Function> predicate, void* userData) const
{
	return Algorithm::getItemByPredicate(_pimpl->getFileLevelFunctionsByName(), predicate, userData);
}

Vector<Function const*> Database::getFileLevelFunctionsByPredicate(Predicate<Function> predicate, void* userData) const
{
	return Algorithm::getItemsByPredicate(_pimpl->getFileLevelFunctionsByName(), predicate, userData);
}

bool Database::foreachFileLevelFunction(Visitor<Function> visitor, void* userData) const
{
	return Algorithm::foreach(_pimpl->getFileLevelFunctionsByName(), visitor, userData);
}

std::size_t Database::getFileLevelFunctionsCount() const noexcept
{
	return _pimpl->getFileLevelFunctionsByName().size();
}

Method const* Database::getMethodById(std::size_t id) const noexcept
{
	return methodCast(getEntityById(id));
}

StaticMethod const* Database::getStaticMethodById(std::size_t id) const noexcept
{
	return staticMethodCast(getEntityById(id));
}

Field const* Database::getFieldById(std::size_t id) const noexcept
{
	return fieldCast(getEntityById(id));
}

StaticField const* Database::getStaticFieldById(std::size_t id) const noexcept
{
	return staticFieldCast(getEntityById(id));
}

EnumValue const* Database::getEnumValueById(std::size_t id) const noexcept
{
	return enumValueCast(getEntityById(id));
}

Database const& rfk::getDatabase() noexcept
{
	return Database::getInstance();
}