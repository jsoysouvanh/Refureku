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
	return EntityUtility::getEntityByName(reinterpret_cast<NamespaceImpl const*>(getPimpl())->getNamespaces(), name);
}

NamespaceAPI const* NamespaceAPI::getNamespaceByPredicate(Predicate<NamespaceAPI> predicate, void* userData) const
{
	return EntityUtility::getEntityByPredicate(reinterpret_cast<NamespaceImpl const*>(getPimpl())->getNamespaces(), predicate, userData);
}

Vector<NamespaceAPI const*>	NamespaceAPI::getNamespacesByPredicate(Predicate<NamespaceAPI> predicate, void* userData) const
{
	return EntityUtility::getEntitiesByPredicate(reinterpret_cast<NamespaceImpl const*>(getPimpl())->getNamespaces(), predicate, userData);
}

bool NamespaceAPI::foreachNamespace(Visitor<NamespaceAPI> visitor, void* userData) const
{
	return EntityUtility::foreachEntity(reinterpret_cast<NamespaceImpl const*>(getPimpl())->getNamespaces(), visitor, userData);
}

StructAPI const* NamespaceAPI::getStructByName(char const* name) const noexcept
{
	return reinterpret_cast<StructAPI const*>(
		EntityUtility::getEntityByNameAndPredicate(reinterpret_cast<NamespaceImpl const*>(getPimpl())->getArchetypes(),
													name,
													[](ArchetypeAPI const& arch) { return arch.getKind() == EEntityKind::Struct; }));
}

ClassAPI const* NamespaceAPI::getClassByName(char const* name) const noexcept
{
	return reinterpret_cast<ClassAPI const*>(
		EntityUtility::getEntityByNameAndPredicate(reinterpret_cast<NamespaceImpl const*>(getPimpl())->getArchetypes(),
													name,
													[](ArchetypeAPI const& arch) { return arch.getKind() == EEntityKind::Class; }));
}

EnumAPI const* NamespaceAPI::getEnumByName(char const* name) const noexcept
{
	return reinterpret_cast<EnumAPI const*>(
		EntityUtility::getEntityByNameAndPredicate(reinterpret_cast<NamespaceImpl const*>(getPimpl())->getArchetypes(),
													name,
													[](ArchetypeAPI const& arch) { return arch.getKind() == EEntityKind::Enum; }));
}

bool NamespaceAPI::foreachArchetype(Visitor<ArchetypeAPI> visitor, void* userData) const
{
	return EntityUtility::foreachEntity(reinterpret_cast<NamespaceImpl const*>(getPimpl())->getArchetypes(), visitor, userData);
}

VariableAPI const* NamespaceAPI::getVariableByName(char const* name, EVarFlags flags) const noexcept
{
	return reinterpret_cast<VariableAPI const*>(
		EntityUtility::getEntityByNameAndPredicate(reinterpret_cast<NamespaceImpl const*>(getPimpl())->getVariables(),
													name,
													[flags](VariableAPI const& var) { return (var.getFlags() & flags) == flags; }));
}

bool NamespaceAPI::foreachVariable(Visitor<VariableAPI> visitor, void* userData) const
{
	return EntityUtility::foreachEntity(reinterpret_cast<NamespaceImpl const*>(getPimpl())->getVariables(), visitor, userData);
}

FunctionAPI const* NamespaceAPI::getFunctionByName(char const* name, EFunctionFlags flags) const noexcept
{
	return reinterpret_cast<FunctionAPI const*>(
		EntityUtility::getEntityByNameAndPredicate(reinterpret_cast<NamespaceImpl const*>(getPimpl())->getFunctions(),
													name,
													[flags](FunctionAPI const& func) { return (func.getFlags() & flags) == flags; }));
}

bool NamespaceAPI::foreachFunction(Visitor<FunctionAPI> visitor, void* userData) const
{
	return EntityUtility::foreachEntity(reinterpret_cast<NamespaceImpl const*>(getPimpl())->getFunctions(), visitor, userData);
}