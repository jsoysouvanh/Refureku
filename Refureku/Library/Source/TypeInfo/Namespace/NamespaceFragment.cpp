#include "Refureku/TypeInfo/Namespace/NamespaceFragment.h"

#include "Refureku/TypeInfo/Namespace/NamespaceFragmentImpl.h"
#include "Refureku/TypeInfo/Entity/EntityUtility.h"

using namespace rfk;

NamespaceFragment::NamespaceFragment(char const* name, std::size_t id) noexcept:
	Entity(new NamespaceFragmentImpl(name, id))
{
}

NamespaceFragment::~NamespaceFragment() noexcept = default;

bool NamespaceFragment::foreachNestedEntity(Visitor<Entity> visitor, void* userData) const
{
	return EntityUtility::foreachEntity(getPimpl()->getNestedEntities(), visitor, userData);
}

void NamespaceFragment::addNestedEntity(Entity const* nestedEntity) noexcept
{
	getPimpl()->addNestedEntity(nestedEntity);
}

void NamespaceFragment::setNestedEntitiesCapacity(std::size_t capacity) noexcept
{
	getPimpl()->setNestedEntitiesCapacity(capacity);
}