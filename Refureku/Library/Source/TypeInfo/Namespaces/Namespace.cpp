#include "TypeInfo/Namespaces/Namespace.h"

#include "TypeInfo/Archetypes/Struct.h"
#include "TypeInfo/Archetypes/Class.h"
#include "TypeInfo/Archetypes/Enum.h"

using namespace rfk;

Namespace::Namespace(std::string&& newName, uint64 newId) noexcept:
	Entity(std::forward<std::string>(newName), newId, Entity::EKind::Namespace)
{
}

Namespace const* Namespace::getNestedNamespace(std::string namespaceName) const noexcept
{
	//Use an Entity instead of a Namespace to avoid containers initialization
	Entity searchingNamespace(std::move(namespaceName), 0u);

	//We know the hash method only uses the name inherited from Entity so cast is fine
	decltype(nestedNamespaces)::const_iterator it = nestedNamespaces.find(reinterpret_cast<Namespace const*>(&searchingNamespace));

	return (it != nestedNamespaces.cend()) ? *it : nullptr;
}

Struct const* Namespace::getNestedStruct(std::string structName, EAccessSpecifier access) const noexcept
{
	//Use an Entity instead of a Struct to avoid containers initialization
	Entity searchingStruct(std::move(structName), 0u);

	//We know the hash method only uses the name inherited from Entity so cast is fine
	decltype(nestedArchetypes)::const_iterator it = nestedArchetypes.find(reinterpret_cast<Archetype const*>(&searchingStruct));

	return (it != nestedArchetypes.cend() && (access == EAccessSpecifier::Undefined || (*it)->accessSpecifier == access)) ? reinterpret_cast<Struct const*>(*it) : nullptr;
}

Class const* Namespace::getNestedClass(std::string className, EAccessSpecifier access) const noexcept
{
	//Use an Entity instead of a Class to avoid containers initialization
	Entity searchingClass(std::move(className), 0u);

	//We know the hash method only uses the name inherited from Entity so cast is fine
	decltype(nestedArchetypes)::const_iterator it = nestedArchetypes.find(reinterpret_cast<Archetype const*>(&searchingClass));

	return (it != nestedArchetypes.cend() && (access == EAccessSpecifier::Undefined || (*it)->accessSpecifier == access)) ? reinterpret_cast<Class const*>(*it) : nullptr;
}

Enum const* Namespace::getNestedEnum(std::string enumName, EAccessSpecifier access) const noexcept
{
	//Use an Entity instead of a Class to avoid containers initialization
	Entity searchingEnum(std::move(enumName), 0u);

	//We know the hash method only uses the name inherited from Entity so cast is fine
	decltype(nestedArchetypes)::const_iterator it = nestedArchetypes.find(reinterpret_cast<Archetype const*>(&searchingEnum));

	return (it != nestedArchetypes.cend() && (access == EAccessSpecifier::Undefined || (*it)->accessSpecifier == access)) ? reinterpret_cast<Enum const*>(*it) : nullptr;
}