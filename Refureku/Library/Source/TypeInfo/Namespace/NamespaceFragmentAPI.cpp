#include "Refureku/TypeInfo/Namespace/NamespaceFragmentAPI.h"

#include "Refureku/TypeInfo/Namespace/NamespaceFragmentImpl.h"
#include "Refureku/TypeInfo/Entity/EntityUtility.h"

using namespace rfk;

NamespaceFragmentAPI::NamespaceFragmentAPI(char const* name, std::size_t id) noexcept:
	Entity(new NamespaceFragmentImpl(name, id))
{
}

NamespaceFragmentAPI::~NamespaceFragmentAPI() noexcept = default;

bool NamespaceFragmentAPI::foreachNestedEntity(Visitor<Entity> visitor, void* userData) const
{
	return EntityUtility::foreachEntity(reinterpret_cast<NamespaceFragmentImpl const*>(getPimpl())->getNestedEntities(), visitor, userData);
}

void NamespaceFragmentAPI::addNestedEntity(Entity const* nestedEntity) noexcept
{
	reinterpret_cast<NamespaceFragmentImpl*>(getPimpl())->addNestedEntity(nestedEntity);
}

void NamespaceFragmentAPI::setNestedEntitiesCapacity(std::size_t capacity) noexcept
{
	reinterpret_cast<NamespaceFragmentImpl*>(getPimpl())->setNestedEntitiesCapacity(capacity);
}