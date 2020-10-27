#include "Refureku/TypeInfo/Namespaces/Namespace.h"

#include "Refureku/TypeInfo/Archetypes/Struct.h"
#include "Refureku/TypeInfo/Archetypes/Class.h"
#include "Refureku/TypeInfo/Archetypes/Enum.h"

using namespace rfk;

Namespace::Namespace(std::string&& newName, uint64 newId) noexcept:
	Entity(std::forward<std::string>(newName), newId, Entity::EKind::Namespace)
{
}

Namespace const* Namespace::getNamespace(std::string namespaceName) const noexcept
{
	//Use an Entity instead of a Namespace to avoid containers initialization
	Entity searchingNamespace(std::move(namespaceName), 0u);

	//We know the hash method only uses the name inherited from Entity so cast is fine
	decltype(namespaces)::const_iterator it = namespaces.find(reinterpret_cast<Namespace const*>(&searchingNamespace));

	return (it != namespaces.cend()) ? *it : nullptr;
}

Struct const* Namespace::getStruct(std::string structName) const noexcept
{
	//Use an Entity instead of a Struct to avoid containers initialization
	Entity searchingStruct(std::move(structName), 0u);

	//We know the hash method only uses the name inherited from Entity so cast is fine
	decltype(archetypes)::const_iterator it = archetypes.find(reinterpret_cast<Archetype const*>(&searchingStruct));

	return (it != archetypes.cend()) ? reinterpret_cast<Struct const*>(*it) : nullptr;
}

Class const* Namespace::getClass(std::string className) const noexcept
{
	//Use an Entity instead of a Class to avoid containers initialization
	Entity searchingClass(std::move(className), 0u);

	//We know the hash method only uses the name inherited from Entity so cast is fine
	decltype(archetypes)::const_iterator it = archetypes.find(reinterpret_cast<Archetype const*>(&searchingClass));

	return (it != archetypes.cend()) ? reinterpret_cast<Class const*>(*it) : nullptr;
}

Enum const* Namespace::getEnum(std::string enumName) const noexcept
{
	//Use an Entity instead of an Enum to avoid containers initialization
	Entity searchingEnum(std::move(enumName), 0u);

	//We know the hash method only uses the name inherited from Entity so cast is fine
	decltype(archetypes)::const_iterator it = archetypes.find(reinterpret_cast<Archetype const*>(&searchingEnum));

	return (it != archetypes.cend()) ? reinterpret_cast<Enum const*>(*it) : nullptr;
}

Variable const* Namespace::getVariable(std::string variableName, EVarFlags flags) const noexcept
{
	//Use an Entity instead of an Enum to avoid containers initialization
	Entity searchingVariable(std::move(variableName), 0u);

	//We know the hash method only uses the name inherited from Entity so cast is fine
	decltype(variables)::const_iterator it = variables.find(reinterpret_cast<Variable const*>(&searchingVariable));
	
	return (it != variables.cend() && ((*it)->flags & flags) == flags) ? *it : nullptr;
}

Function const* Namespace::getFunction(std::string functionName, EFunctionFlags flags) const noexcept
{
	//Use an Entity instead of a Function to avoid containers initialization
	Entity searchingMethod(std::move(functionName), 0u);

	//We know the hash method only uses the name inherited from Entity so cast is fine
	decltype(functions)::const_iterator it = functions.find(reinterpret_cast<Function const*>(&searchingMethod));

	return (it != functions.cend() && ((*it)->flags & flags) == flags) ? *it : nullptr;
}