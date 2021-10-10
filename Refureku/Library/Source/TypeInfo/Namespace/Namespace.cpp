#include "Refureku/TypeInfo/Namespace/Namespace.h"

#include "Refureku/TypeInfo/Namespace/NamespaceImpl.h"
#include "Refureku/TypeInfo/Archetypes/Struct.h"
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

Vector<Namespace const*> Namespace::getNamespacesByPredicate(Predicate<Namespace> predicate, void* userData) const
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

Struct const* Namespace::getStructByName(char const* name) const noexcept
{
	return reinterpret_cast<Struct const*>(
		EntityUtility::getEntityByNameAndPredicate(reinterpret_cast<NamespaceImpl const*>(getPimpl())->getArchetypes(),
													name,
													[](Archetype const& arch) { return arch.getKind() == EEntityKind::Struct; }));
}

Struct const* Namespace::getStructByPredicate(Predicate<Struct> predicate, void* userData) const
{
	return (predicate != nullptr) ?
		reinterpret_cast<Struct const*>(
			EntityUtility::getEntityByPredicate(reinterpret_cast<NamespaceImpl const*>(getPimpl())->getArchetypes(),
												[predicate, userData](Archetype const& archetype)
												{
													return archetype.getKind() == EEntityKind::Struct &&
															predicate(static_cast<Struct const&>(archetype), userData);
												})) : nullptr;
}

Vector<Struct const*> Namespace::getStructsByPredicate(Predicate<Struct> predicate, void* userData) const
{
	if (predicate != nullptr)
	{
		return EntityUtility::getEntitiesByPredicate(reinterpret_cast<NamespaceImpl const*>(getPimpl())->getArchetypes(),
													 [predicate, userData](Archetype const& archetype)
													 {
														 return archetype.getKind() == EEntityKind::Struct &&
															 predicate(static_cast<Struct const&>(archetype), userData);
													 });
	}
	else
	{
		return Vector<Struct const*>(0);
	}
}

Class const* Namespace::getClassByName(char const* name) const noexcept
{
	return reinterpret_cast<Class const*>(
		EntityUtility::getEntityByNameAndPredicate(reinterpret_cast<NamespaceImpl const*>(getPimpl())->getArchetypes(),
													name,
													[](Archetype const& arch) { return arch.getKind() == EEntityKind::Class; }));
}

Class const* Namespace::getClassByPredicate(Predicate<Class> predicate, void* userData) const
{
	return (predicate != nullptr) ?
		reinterpret_cast<Struct const*>(
			EntityUtility::getEntityByPredicate(reinterpret_cast<NamespaceImpl const*>(getPimpl())->getArchetypes(),
			[predicate, userData](Archetype const& archetype)
			{
				return archetype.getKind() == EEntityKind::Class &&
					predicate(static_cast<Class const&>(archetype), userData);
			})) : nullptr;
}

Vector<Class const*> Namespace::getClassesByPredicate(Predicate<Class> predicate, void* userData) const
{
	if (predicate != nullptr)
	{
		return EntityUtility::getEntitiesByPredicate(reinterpret_cast<NamespaceImpl const*>(getPimpl())->getArchetypes(),
													 [predicate, userData](Archetype const& archetype)
													 {
														 return archetype.getKind() == EEntityKind::Class &&
															 predicate(static_cast<Class const&>(archetype), userData);
													 });
	}
	else
	{
		return Vector<Class const*>(0);
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

Variable const* Namespace::getVariableByName(char const* name, EVarFlags flags) const noexcept
{
	return reinterpret_cast<Variable const*>(
		EntityUtility::getEntityByNameAndPredicate(reinterpret_cast<NamespaceImpl const*>(getPimpl())->getVariables(),
													name,
													[flags](Variable const& var) { return (var.getFlags() & flags) == flags; }));
}

Variable const* Namespace::getVariableByPredicate(Predicate<Variable> predicate, void* userData) const
{
	return (predicate != nullptr) ?
		EntityUtility::getEntityByPredicate(reinterpret_cast<NamespaceImpl const*>(getPimpl())->getVariables(),
		[predicate, userData](Variable const& variable)
		{
			return predicate(variable, userData);
		}) : nullptr;
}

Vector<Variable const*> Namespace::getVariablesByPredicate(Predicate<Variable> predicate, void* userData) const
{
	return (predicate != nullptr) ?
		EntityUtility::getEntitiesByPredicate(reinterpret_cast<NamespaceImpl const*>(getPimpl())->getVariables(),
											  [predicate, userData](Variable const& variable)
											  {
												  return predicate(variable, userData);
											  }) : Vector<Variable const*>(0);
}

bool Namespace::foreachVariable(Visitor<Variable> visitor, void* userData) const
{
	return EntityUtility::foreachEntity(reinterpret_cast<NamespaceImpl const*>(getPimpl())->getVariables(), visitor, userData);
}

Function const* Namespace::getFunctionByName(char const* name, EFunctionFlags flags) const noexcept
{
	return reinterpret_cast<Function const*>(
		EntityUtility::getEntityByNameAndPredicate(reinterpret_cast<NamespaceImpl const*>(getPimpl())->getFunctions(),
													name,
													[flags](Function const& func)
													{
														return (func.getFlags() & flags) == flags;
													}));
}

Vector<Function const*> Namespace::getFunctionsByName(char const* name, EFunctionFlags flags) const noexcept
{
	return EntityUtility::getEntitiesByNameAndPredicate(reinterpret_cast<NamespaceImpl const*>(getPimpl())->getFunctions(),
														name,
														[flags](Function const& func)
														{
															return (func.getFlags() & flags) == flags;
														});
}

Function const* Namespace::getFunctionByPredicate(Predicate<Function> predicate, void* userData) const
{
	return (predicate != nullptr) ?
		EntityUtility::getEntityByPredicate(reinterpret_cast<NamespaceImpl const*>(getPimpl())->getFunctions(),
											[predicate, userData](Function const& function)
											{
												return predicate(function, userData);
											}) : nullptr;
}

Vector<Function const*> Namespace::getFunctionsByPredicate(Predicate<Function> predicate, void* userData) const
{
	return (predicate != nullptr) ?
		EntityUtility::getEntitiesByPredicate(reinterpret_cast<NamespaceImpl const*>(getPimpl())->getFunctions(),
											  [predicate, userData](Function const& function)
											  {
												  return predicate(function, userData);
											  }) : Vector<Function const*>(0);
}

bool Namespace::foreachFunction(Visitor<Function> visitor, void* userData) const
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

void Namespace::addVariable(Variable const& variable) noexcept
{
	reinterpret_cast<NamespaceImpl*>(getPimpl())->addVariable(variable);
}

void Namespace::addFunction(Function const& function) noexcept
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

void Namespace::removeVariable(Variable const& variable) noexcept
{
	reinterpret_cast<NamespaceImpl*>(getPimpl())->removeVariable(variable);
}

void Namespace::removeFunction(Function const& function) noexcept
{
	reinterpret_cast<NamespaceImpl*>(getPimpl())->removeFunction(function);
}