#include "Refureku/TypeInfo/Namespace/NamespaceFragmentAPI.h"

#include "Refureku/TypeInfo/Namespace/NamespaceFragmentImpl.h"
#include "Refureku/TypeInfo/Entity/EntityUtility.h"

using namespace rfk;

NamespaceFragmentAPI::NamespaceFragmentAPI(char const* name, std::size_t id) noexcept:
	EntityAPI(new NamespaceFragmentImpl(name, id))
{
}

NamespaceFragmentAPI::~NamespaceFragmentAPI() noexcept = default;

bool NamespaceFragmentAPI::foreachNestedEntity(bool (*visitor)(EntityAPI const&, void*), void* userData) const noexcept
{
	return EntityUtility::foreachEntityPtr(reinterpret_cast<NamespaceFragmentImpl const*>(getPimpl())->getNestedEntities(), visitor, userData);
}

NamespaceFragmentAPI* NamespaceFragmentAPI::addNestedEntity(EntityAPI const* nestedEntity) noexcept
{
	reinterpret_cast<NamespaceFragmentImpl*>(getPimpl())->addNestedEntity(nestedEntity);

	return this;
}

void NamespaceFragmentAPI::setNestedEntitiesCapacity(std::size_t capacity) noexcept
{
	reinterpret_cast<NamespaceFragmentImpl*>(getPimpl())->setNestedEntitiesCapacity(capacity);
}

void NamespaceFragmentAPI::optimizeMemory()
{
	reinterpret_cast<NamespaceFragmentImpl*>(getPimpl())->optimizeMemory();
}