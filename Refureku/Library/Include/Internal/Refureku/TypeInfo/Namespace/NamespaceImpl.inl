/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

inline Namespace::NamespaceImpl::NamespaceImpl(char const* name, std::size_t id) noexcept:
	EntityImpl(name, id, EEntityKind::Namespace)
{
}

inline void Namespace::NamespaceImpl::addNamespace(Namespace const& nestedNamespace) noexcept
{
	_namespaces.emplace(&nestedNamespace);
}

inline void Namespace::NamespaceImpl::addArchetype(Archetype const& archetype) noexcept
{
	_archetypes.emplace(&archetype);
}

inline void Namespace::NamespaceImpl::addVariable(Variable const& variable) noexcept
{
	_variables.emplace(&variable);
}

inline void Namespace::NamespaceImpl::addFunction(Function const& function) noexcept
{
	_functions.emplace(&function);
}

inline void Namespace::NamespaceImpl::removeNamespace(Namespace const& nestedNamespace) noexcept
{
	_namespaces.erase(&nestedNamespace);
}

inline void Namespace::NamespaceImpl::removeArchetype(Archetype const& archetype) noexcept
{
	_archetypes.erase(&archetype);
}

inline void Namespace::NamespaceImpl::removeVariable(Variable const& variable) noexcept
{
	_variables.erase(&variable);
}

inline void Namespace::NamespaceImpl::removeFunction(Function const& function) noexcept
{
	_functions.erase(&function);
}

inline void Namespace::NamespaceImpl::setOuterEntity(Entity& entity, Namespace const& ref) const noexcept
{
	entity.setOuterEntity(&ref);
}

inline Namespace::NamespaceImpl::NamespaceHashSet const& Namespace::NamespaceImpl::getNamespaces() const noexcept
{
	return _namespaces;
}

inline Namespace::NamespaceImpl::ArchetypeHashSet const& Namespace::NamespaceImpl::getArchetypes() const noexcept
{
	return _archetypes;
}

inline Namespace::NamespaceImpl::VariableHashSet const& Namespace::NamespaceImpl::getVariables() const noexcept
{
	return _variables;
}

inline Namespace::NamespaceImpl::FunctionHashSet const& Namespace::NamespaceImpl::getFunctions() const noexcept
{
	return _functions;
}