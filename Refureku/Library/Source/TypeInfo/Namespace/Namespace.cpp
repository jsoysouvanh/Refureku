#include "Refureku/TypeInfo/Namespace/Namespace.h"

#include "Refureku/TypeInfo/Namespace/NamespaceImpl.h"
#include "Refureku/TypeInfo/Archetypes/StructAPI.h"
#include "Refureku/TypeInfo/Archetypes/Enum.h"
#include "Refureku/TypeInfo/Entity/EntityUtility.h"

using namespace rfk;

Namespace::Namespace(char const* name, std::size_t id) noexcept:
	Entity(new NamespaceImpl(name, id))
{
}

Namespace::~Namespace() noexcept = default;

Namespace const* Namespace::getNamespaceByName(char const* name) const noexcept
{
	return EntityUtility::getEntityByName(reinterpret_cast<NamespaceImpl const*>(getPimpl())->getNamespaces(), name);
}

Namespace const* Namespace::getNamespaceByPredicate(Predicate<Namespace> predicate, void* userData) const
{
	return (predicate != nullptr) ?
		EntityUtility::getEntityByPredicate(reinterpret_cast<NamespaceImpl const*>(getPimpl())->getNamespaces(), [predicate, userData](Namespace const& n){ return predicate(n, userData); }) :
		nullptr;
}

Vector<Namespace const*>	Namespace::getNamespacesByPredicate(Predicate<Namespace> predicate, void* userData) const
{
	return (predicate != nullptr) ?
		EntityUtility::getEntitiesByPredicate(reinterpret_cast<NamespaceImpl const*>(getPimpl())->getNamespaces(),
											  [predicate, userData](Namespace const& n)
											  {
												  return predicate(n, userData);
											  }) : Vector<Namespace const*>(0);
}

bool Namespace::foreachNamespace(Visitor<Namespace> visitor, void* userData) const
{
	return EntityUtility::foreachEntity(reinterpret_cast<NamespaceImpl const*>(getPimpl())->getNamespaces(), visitor, userData);
}

StructAPI const* Namespace::getStructByName(char const* name) const noexcept
{
	return reinterpret_cast<StructAPI const*>(
		EntityUtility::getEntityByNameAndPredicate(reinterpret_cast<NamespaceImpl const*>(getPimpl())->getArchetypes(),
													name,
													[](Archetype const& arch) { return arch.getKind() == EEntityKind::Struct; }));
}

StructAPI const* Namespace::getStructByPredicate(Predicate<StructAPI> predicate, void* userData) const
{
	return (predicate != nullptr) ?
		reinterpret_cast<StructAPI const*>(
			EntityUtility::getEntityByPredicate(reinterpret_cast<NamespaceImpl const*>(getPimpl())->getArchetypes(),
												[predicate, userData](Archetype const& archetype)
												{
													return archetype.getKind() == EEntityKind::Struct &&
															predicate(static_cast<StructAPI const&>(archetype), userData);
												})) : nullptr;
}

Vector<StructAPI const*> Namespace::getStructsByPredicate(Predicate<StructAPI> predicate, void* userData) const
{
	if (predicate != nullptr)
	{
		return EntityUtility::getEntitiesByPredicate(reinterpret_cast<NamespaceImpl const*>(getPimpl())->getArchetypes(),
													 [predicate, userData](Archetype const& archetype)
													 {
														 return archetype.getKind() == EEntityKind::Struct &&
															 predicate(static_cast<StructAPI const&>(archetype), userData);
													 });
	}
	else
	{
		return Vector<StructAPI const*>(0);
	}
}

ClassAPI const* Namespace::getClassByName(char const* name) const noexcept
{
	return reinterpret_cast<ClassAPI const*>(
		EntityUtility::getEntityByNameAndPredicate(reinterpret_cast<NamespaceImpl const*>(getPimpl())->getArchetypes(),
													name,
													[](Archetype const& arch) { return arch.getKind() == EEntityKind::Class; }));
}

ClassAPI const* Namespace::getClassByPredicate(Predicate<ClassAPI> predicate, void* userData) const
{
	return (predicate != nullptr) ?
		reinterpret_cast<StructAPI const*>(
			EntityUtility::getEntityByPredicate(reinterpret_cast<NamespaceImpl const*>(getPimpl())->getArchetypes(),
			[predicate, userData](Archetype const& archetype)
			{
				return archetype.getKind() == EEntityKind::Class &&
					predicate(static_cast<ClassAPI const&>(archetype), userData);
			})) : nullptr;
}

Vector<ClassAPI const*> Namespace::getClassesByPredicate(Predicate<ClassAPI> predicate, void* userData) const
{
	if (predicate != nullptr)
	{
		return EntityUtility::getEntitiesByPredicate(reinterpret_cast<NamespaceImpl const*>(getPimpl())->getArchetypes(),
													 [predicate, userData](Archetype const& archetype)
													 {
														 return archetype.getKind() == EEntityKind::Class &&
															 predicate(static_cast<ClassAPI const&>(archetype), userData);
													 });
	}
	else
	{
		return Vector<ClassAPI const*>(0);
	}
}

Enum const* Namespace::getEnumByName(char const* name) const noexcept
{
	return reinterpret_cast<Enum const*>(
		EntityUtility::getEntityByNameAndPredicate(reinterpret_cast<NamespaceImpl const*>(getPimpl())->getArchetypes(),
													name,
													[](Archetype const& arch) { return arch.getKind() == EEntityKind::Enum; }));
}

Enum const* Namespace::getEnumByPredicate(Predicate<Enum> predicate, void* userData) const
{
	return (predicate != nullptr) ?
		reinterpret_cast<Enum const*>(
			EntityUtility::getEntityByPredicate(reinterpret_cast<NamespaceImpl const*>(getPimpl())->getArchetypes(),
			[predicate, userData](Archetype const& archetype)
			{
				return archetype.getKind() == EEntityKind::Enum &&
					predicate(static_cast<Enum const&>(archetype), userData);
			})) : nullptr;
}

Vector<Enum const*> Namespace::getEnumsByPredicate(Predicate<Enum> predicate, void* userData) const
{
	if (predicate != nullptr)
	{
		return EntityUtility::getEntitiesByPredicate(reinterpret_cast<NamespaceImpl const*>(getPimpl())->getArchetypes(),
													 [predicate, userData](Archetype const& archetype)
													 {
														 return archetype.getKind() == EEntityKind::Enum &&
															 predicate(static_cast<Enum const&>(archetype), userData);
													 });
	}
	else
	{
		return Vector<Enum const*>(0);
	}
}

bool Namespace::foreachArchetype(Visitor<Archetype> visitor, void* userData) const
{
	return EntityUtility::foreachEntity(reinterpret_cast<NamespaceImpl const*>(getPimpl())->getArchetypes(), visitor, userData);
}

VariableAPI const* Namespace::getVariableByName(char const* name, EVarFlags flags) const noexcept
{
	return reinterpret_cast<VariableAPI const*>(
		EntityUtility::getEntityByNameAndPredicate(reinterpret_cast<NamespaceImpl const*>(getPimpl())->getVariables(),
													name,
													[flags](VariableAPI const& var) { return (var.getFlags() & flags) == flags; }));
}

VariableAPI const* Namespace::getVariableByPredicate(Predicate<VariableAPI> predicate, void* userData) const
{
	return (predicate != nullptr) ?
		EntityUtility::getEntityByPredicate(reinterpret_cast<NamespaceImpl const*>(getPimpl())->getVariables(),
		[predicate, userData](VariableAPI const& variable)
		{
			return predicate(variable, userData);
		}) : nullptr;
}

Vector<VariableAPI const*> Namespace::getVariablesByPredicate(Predicate<VariableAPI> predicate, void* userData) const
{
	return (predicate != nullptr) ?
		EntityUtility::getEntitiesByPredicate(reinterpret_cast<NamespaceImpl const*>(getPimpl())->getVariables(),
											  [predicate, userData](VariableAPI const& variable)
											  {
												  return predicate(variable, userData);
											  }) : Vector<VariableAPI const*>(0);
}

bool Namespace::foreachVariable(Visitor<VariableAPI> visitor, void* userData) const
{
	return EntityUtility::foreachEntity(reinterpret_cast<NamespaceImpl const*>(getPimpl())->getVariables(), visitor, userData);
}

FunctionAPI const* Namespace::getFunctionByName(char const* name, EFunctionFlags flags) const noexcept
{
	return reinterpret_cast<FunctionAPI const*>(
		EntityUtility::getEntityByNameAndPredicate(reinterpret_cast<NamespaceImpl const*>(getPimpl())->getFunctions(),
													name,
													[flags](FunctionAPI const& func)
													{
														return (func.getFlags() & flags) == flags;
													}));
}

Vector<FunctionAPI const*> Namespace::getFunctionsByName(char const* name, EFunctionFlags flags) const noexcept
{
	return EntityUtility::getEntitiesByNameAndPredicate(reinterpret_cast<NamespaceImpl const*>(getPimpl())->getFunctions(),
														name,
														[flags](FunctionAPI const& func)
														{
															return (func.getFlags() & flags) == flags;
														});
}

FunctionAPI const* Namespace::getFunctionByPredicate(Predicate<FunctionAPI> predicate, void* userData) const
{
	return (predicate != nullptr) ?
		EntityUtility::getEntityByPredicate(reinterpret_cast<NamespaceImpl const*>(getPimpl())->getFunctions(),
											[predicate, userData](FunctionAPI const& function)
											{
												return predicate(function, userData);
											}) : nullptr;
}

Vector<FunctionAPI const*> Namespace::getFunctionsByPredicate(Predicate<FunctionAPI> predicate, void* userData) const
{
	return (predicate != nullptr) ?
		EntityUtility::getEntitiesByPredicate(reinterpret_cast<NamespaceImpl const*>(getPimpl())->getFunctions(),
											  [predicate, userData](FunctionAPI const& function)
											  {
												  return predicate(function, userData);
											  }) : Vector<FunctionAPI const*>(0);
}

bool Namespace::foreachFunction(Visitor<FunctionAPI> visitor, void* userData) const
{
	return EntityUtility::foreachEntity(reinterpret_cast<NamespaceImpl const*>(getPimpl())->getFunctions(), visitor, userData);
}

void Namespace::addNamespace(Namespace const& nestedNamespace) noexcept
{
	reinterpret_cast<NamespaceImpl*>(getPimpl())->addNamespace(nestedNamespace);
}

void Namespace::addArchetype(Archetype const& archetype) noexcept
{
	reinterpret_cast<NamespaceImpl*>(getPimpl())->addArchetype(archetype);
}

void Namespace::addVariable(VariableAPI const& variable) noexcept
{
	reinterpret_cast<NamespaceImpl*>(getPimpl())->addVariable(variable);
}

void Namespace::addFunction(FunctionAPI const& function) noexcept
{
	reinterpret_cast<NamespaceImpl*>(getPimpl())->addFunction(function);
}

void Namespace::removeNamespace(Namespace const& nestedNamespace) noexcept
{
	reinterpret_cast<NamespaceImpl*>(getPimpl())->removeNamespace(nestedNamespace);
}

void Namespace::removeArchetype(Archetype const& archetype) noexcept
{
	reinterpret_cast<NamespaceImpl*>(getPimpl())->removeArchetype(archetype);
}

void Namespace::removeVariable(VariableAPI const& variable) noexcept
{
	reinterpret_cast<NamespaceImpl*>(getPimpl())->removeVariable(variable);
}

void Namespace::removeFunction(FunctionAPI const& function) noexcept
{
	reinterpret_cast<NamespaceImpl*>(getPimpl())->removeFunction(function);
}