/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

inline NamespaceFragmentAPI::NamespaceFragmentImpl::NamespaceFragmentImpl(char const* name, std::size_t id) noexcept:
	EntityImpl(name, id, EEntityKind::Undefined)	//Fragments are used internally only, so it's fine to let it as undefined
{
}

inline void NamespaceFragmentAPI::NamespaceFragmentImpl::addNestedEntity(EntityAPI const* nestedEntity) noexcept
{
	_nestedEntities.push_back(nestedEntity);
}

inline void NamespaceFragmentAPI::NamespaceFragmentImpl::setNestedEntitiesCapacity(std::size_t capacity) noexcept
{
	_nestedEntities.reserve(capacity);
}

inline void NamespaceFragmentAPI::NamespaceFragmentImpl::optimizeMemory()
{
	_nestedEntities.shrink_to_fit();
}

inline std::vector<EntityAPI const*> const& NamespaceFragmentAPI::NamespaceFragmentImpl::getNestedEntities() const noexcept
{
	return _nestedEntities;
}