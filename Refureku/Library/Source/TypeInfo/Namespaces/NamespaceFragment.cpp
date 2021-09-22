#include "Refureku/TypeInfo/Namespaces/NamespaceFragment.h"

using namespace rfk;

NamespaceFragment::NamespaceFragment(std::string&& newName, uint64 newId) noexcept:
	Entity(std::forward<std::string>(newName), newId, EEntityKind::Undefined)	//Fragments are used internally only, so it's fine to let it as undefined
{
}

NamespaceFragment* NamespaceFragment::addNestedEntity(Entity const* nestedEntity) noexcept
{
	_nestedEntities.emplace_back(nestedEntity);

	return this;
}

void NamespaceFragment::setNestedEntitiesCapacity(std::size_t capacity) noexcept
{
	_nestedEntities.reserve(capacity);
}

std::vector<Entity const*> const& NamespaceFragment::getNestedEntities() const noexcept
{
	return _nestedEntities;
}