/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

inline NamespaceAPI::NamespaceImpl::NamespaceImpl(char const* name, std::size_t id) noexcept:
	EntityImpl(name, id, EEntityKind::Namespace)
{
}

inline void NamespaceAPI::NamespaceImpl::addNamespace(NamespaceAPI const* nestedNamespace) noexcept
{
	_namespaces.emplace(nestedNamespace);
}

inline void NamespaceAPI::NamespaceImpl::addArchetype(ArchetypeAPI const* archetype) noexcept
{
	_archetypes.emplace(archetype);
}

inline void NamespaceAPI::NamespaceImpl::addVariable(VariableAPI const* variable) noexcept
{
	_variables.emplace(variable);
}

inline void NamespaceAPI::NamespaceImpl::addFunction(FunctionAPI const* function) noexcept
{
	_functions.emplace(function);
}

inline void NamespaceAPI::NamespaceImpl::removeNamespace(NamespaceAPI const* nestedNamespace) noexcept
{
	_namespaces.erase(nestedNamespace);
}

inline void NamespaceAPI::NamespaceImpl::removeArchetype(ArchetypeAPI const* archetype) noexcept
{
	_archetypes.erase(archetype);
}

inline void NamespaceAPI::NamespaceImpl::removeVariable(VariableAPI const* variable) noexcept
{
	_variables.erase(variable);
}

inline void NamespaceAPI::NamespaceImpl::removeFunction(FunctionAPI const* function) noexcept
{
	_functions.erase(function);
}

inline NamespaceAPI::NamespaceImpl::NamespaceHashSet const& NamespaceAPI::NamespaceImpl::getNamespaces() const noexcept
{
	return _namespaces;
}

inline NamespaceAPI::NamespaceImpl::ArchetypeHashSet const& NamespaceAPI::NamespaceImpl::getArchetypes() const noexcept
{
	return _archetypes;
}

inline NamespaceAPI::NamespaceImpl::VariableHashSet const& NamespaceAPI::NamespaceImpl::getVariables() const noexcept
{
	return _variables;
}

inline NamespaceAPI::NamespaceImpl::FunctionHashSet const& NamespaceAPI::NamespaceImpl::getFunctions() const noexcept
{
	return _functions;
}