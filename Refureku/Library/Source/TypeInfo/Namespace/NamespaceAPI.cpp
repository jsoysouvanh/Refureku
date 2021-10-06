#include "Refureku/TypeInfo/Namespace/NamespaceAPI.h"

#include "Refureku/TypeInfo/Namespace/NamespaceImpl.h"
#include "Refureku/TypeInfo/Archetypes/StructAPI.h"
#include "Refureku/TypeInfo/Archetypes/EnumAPI.h"
#include "Refureku/TypeInfo/Entity/EntityUtility.h"

using namespace rfk;

NamespaceAPI::NamespaceAPI(char const* name, std::size_t id) noexcept:
	Entity(new NamespaceImpl(name, id))
{
}

NamespaceAPI::~NamespaceAPI() noexcept = default;

NamespaceAPI const* NamespaceAPI::getNamespaceByName(char const* name) const noexcept
{
	return EntityUtility::getEntityPtrByNameAndPredicate(	reinterpret_cast<NamespaceImpl const*>(getPimpl())->getNamespaces(),
															name,
															[](NamespaceAPI const*) { return true; });
}

bool NamespaceAPI::foreachNestedNamespace(Visitor<NamespaceAPI> visitor, void* userData) const
{
	return EntityUtility::foreachEntityPtr(reinterpret_cast<NamespaceImpl const*>(getPimpl())->getNamespaces(), visitor, userData);
}

StructAPI const* NamespaceAPI::getStructByName(char const* name) const noexcept
{
	return reinterpret_cast<StructAPI const*>(
		EntityUtility::getEntityPtrByNameAndPredicate(	reinterpret_cast<NamespaceImpl const*>(getPimpl())->getArchetypes(),
														name,
														[](ArchetypeAPI const* arch) { return arch->getKind() == EEntityKind::Struct; }));
}

ClassAPI const* NamespaceAPI::getClassByName(char const* name) const noexcept
{
	return reinterpret_cast<ClassAPI const*>(
		EntityUtility::getEntityPtrByNameAndPredicate(	reinterpret_cast<NamespaceImpl const*>(getPimpl())->getArchetypes(),
														name,
														[](ArchetypeAPI const* arch) { return arch->getKind() == EEntityKind::Class; }));
}

EnumAPI const* NamespaceAPI::getEnumByName(char const* name) const noexcept
{
	return reinterpret_cast<EnumAPI const*>(
		EntityUtility::getEntityPtrByNameAndPredicate(	reinterpret_cast<NamespaceImpl const*>(getPimpl())->getArchetypes(),
														name,
														[](ArchetypeAPI const* arch) { return arch->getKind() == EEntityKind::Enum; }));
}

bool NamespaceAPI::foreachNestedArchetype(Visitor<ArchetypeAPI> visitor, void* userData) const
{
	return EntityUtility::foreachEntityPtr(reinterpret_cast<NamespaceImpl const*>(getPimpl())->getArchetypes(), visitor, userData);
}

VariableAPI const* NamespaceAPI::getVariableByName(char const* name, EVarFlags flags) const noexcept
{
	return reinterpret_cast<VariableAPI const*>(
		EntityUtility::getEntityPtrByNameAndPredicate(	reinterpret_cast<NamespaceImpl const*>(getPimpl())->getVariables(),
														name,
														[flags](VariableAPI const* var) { return (var->getFlags() & flags) == flags; }));
}

bool NamespaceAPI::foreachNestedVariable(Visitor<VariableAPI> visitor, void* userData) const
{
	return EntityUtility::foreachEntityPtr(reinterpret_cast<NamespaceImpl const*>(getPimpl())->getVariables(), visitor, userData);
}

FunctionAPI const* NamespaceAPI::getFunctionByName(char const* name, EFunctionFlags flags) const noexcept
{
	return reinterpret_cast<FunctionAPI const*>(
		EntityUtility::getEntityPtrByNameAndPredicate(	reinterpret_cast<NamespaceImpl const*>(getPimpl())->getFunctions(),
														name,
														[flags](FunctionAPI const* func) { return (func->getFlags() & flags) == flags; }));
}

bool NamespaceAPI::foreachNestedFunction(Visitor<FunctionAPI> visitor, void* userData) const
{
	return EntityUtility::foreachEntityPtr(reinterpret_cast<NamespaceImpl const*>(getPimpl())->getFunctions(), visitor, userData);
}