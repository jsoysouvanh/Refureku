/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

inline NamespaceFragment::NamespaceFragmentImpl::NamespaceFragmentImpl(char const* name, std::size_t id) noexcept:
	EntityImpl(name, id, EEntityKind::Undefined)	//Fragments are used internally only, so it's fine to let it as undefined
{
}

inline void NamespaceFragment::NamespaceFragmentImpl::addNestedEntity(Entity const* nestedEntity) noexcept
{
	_nestedEntities.push_back(nestedEntity);
}

inline void NamespaceFragment::NamespaceFragmentImpl::setNestedEntitiesCapacity(std::size_t capacity) noexcept
{
	_nestedEntities.reserve(capacity);
}

inline std::vector<Entity const*> const& NamespaceFragment::NamespaceFragmentImpl::getNestedEntities() const noexcept
{
	return _nestedEntities;
}