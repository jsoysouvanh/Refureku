#include "Refureku/TypeInfo/Namespaces/Namespace.h"

#include "Refureku/TypeInfo/Archetypes/Struct.h"
#include "Refureku/TypeInfo/Archetypes/Class.h"
#include "Refureku/TypeInfo/Archetypes/Enum.h"
#include "Refureku/TypeInfo/Entity/EntityCast.h"

using namespace rfk;

Namespace::Namespace(std::string&& name, std::size_t id) noexcept:
	Entity(std::forward<std::string>(name), id, EEntityKind::Namespace)
{
}

Namespace const* Namespace::getNamespace(std::string namespaceName) const noexcept
{
	//Use an Entity instead of a Namespace to avoid containers initialization
	Entity searchingNamespace(std::move(namespaceName), 0u);

	//We know the hash method only uses the name inherited from Entity so cast is fine
	decltype(_namespaces)::const_iterator it = _namespaces.find(reinterpret_cast<Namespace const*>(&searchingNamespace));

	return (it != _namespaces.cend()) ? *it : nullptr;
}

Struct const* Namespace::getStruct(std::string structName) const noexcept
{
	//Use an Entity instead of a Struct to avoid containers initialization
	Entity searchingStruct(std::move(structName), 0u);

	//We know the hash method only uses the name inherited from Entity so cast is fine
	decltype(_archetypes)::const_iterator it = _archetypes.find(reinterpret_cast<Archetype const*>(&searchingStruct));

	return (it != _archetypes.cend()) ? entityCast<Struct>(*it) : nullptr;
}

Class const* Namespace::getClass(std::string className) const noexcept
{
	//Use an Entity instead of a Class to avoid containers initialization
	Entity searchingClass(std::move(className), 0u);

	//We know the hash method only uses the name inherited from Entity so cast is fine
	decltype(_archetypes)::const_iterator it = _archetypes.find(reinterpret_cast<Archetype const*>(&searchingClass));

	return (it != _archetypes.cend() && (*it)->getKind() == EEntityKind::Class) ? reinterpret_cast<Class const*>(*it) : nullptr;
}

Enum const* Namespace::getEnum(std::string enumName) const noexcept
{
	//Use an Entity instead of an Enum to avoid containers initialization
	Entity searchingEnum(std::move(enumName), 0u);

	//We know the hash method only uses the name inherited from Entity so cast is fine
	decltype(_archetypes)::const_iterator it = _archetypes.find(reinterpret_cast<Archetype const*>(&searchingEnum));

	return (it != _archetypes.cend()) ? entityCast<Enum>(*it) : nullptr;
}

Variable const* Namespace::getVariable(std::string variableName, EVarFlags flags) const noexcept
{
	//Use an Entity instead of an Enum to avoid containers initialization
	Entity searchingVariable(std::move(variableName), 0u);

	//We know the hash method only uses the name inherited from Entity so cast is fine
	decltype(_variables)::const_iterator it = _variables.find(reinterpret_cast<Variable const*>(&searchingVariable));
	
	return (it != _variables.cend() && ((*it)->getFlags() & flags) == flags) ? *it : nullptr;
}

Function const* Namespace::getFunction(std::string functionName, EFunctionFlags flags) const noexcept
{
	//Use an Entity instead of a Function to avoid containers initialization
	Entity searchingMethod(std::move(functionName), 0u);

	//We know the hash method only uses the name inherited from Entity so cast is fine
	decltype(_functions)::const_iterator it = _functions.find(reinterpret_cast<Function const*>(&searchingMethod));

	return (it != _functions.cend() && ((*it)->getFlags() & flags) == flags) ? *it : nullptr;
}

Namespace::NamespaceHashSet const& Namespace::getNamespaces() const noexcept
{
	return _namespaces;
}

Namespace::ArchetypeHashSet const& Namespace::getArchetypes() const noexcept
{
	return _archetypes;
}

Namespace::VariableHashSet const& Namespace::getVariables() const noexcept
{
	return _variables;
}

Namespace::FunctionHashSet const& Namespace::getFunctions() const noexcept
{
	return _functions;
}


void Namespace::addNamespace(Namespace const* nestedNamespace) noexcept
{
	_namespaces.emplace(nestedNamespace);
}

void Namespace::addArchetype(Archetype const* archetype) noexcept
{
	_archetypes.emplace(archetype);
}

void Namespace::addVariable(Variable const* variable) noexcept
{
	_variables.emplace(variable);
}

void Namespace::addFunction(Function const* function) noexcept
{
	_functions.emplace(function);
}

void Namespace::removeNamespace(Namespace const* nestedNamespace) noexcept
{
	_namespaces.erase(nestedNamespace);
}

void Namespace::removeArchetype(Archetype const* archetype) noexcept
{
	_archetypes.erase(archetype);
}

void Namespace::removeVariable(Variable const* variable) noexcept
{
	_variables.erase(variable);
}

void Namespace::removeFunction(Function const* function) noexcept
{
	_functions.erase(function);
}