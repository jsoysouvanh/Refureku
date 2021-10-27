#include "Refureku/TypeInfo/Namespace/NamespaceFragment.h"

#include "Refureku/TypeInfo/DatabaseImpl.h"
#include "Refureku/TypeInfo/Namespace/NamespaceFragmentImpl.h"
#include "Refureku/Misc/Algorithm.h"

using namespace rfk;

NamespaceFragment::NamespaceFragment(char const* name, std::size_t id) noexcept:
	Entity(new NamespaceFragmentImpl(name, id, Database::getInstance()._pimpl->getOrCreateNamespace(name, id)))
{
}

NamespaceFragment::~NamespaceFragment() noexcept
{
	//Check if this namespace fragment was the last fragment of the merged namespace
	//If this is the case, the namespace will be completely removed from the database
	Database::getInstance()._pimpl->checkNamespaceRefCount(getPimpl()->getMergedNamespace());
}

void NamespaceFragment::addNestedEntity(Entity const* nestedEntity) noexcept
{
	getPimpl()->addNestedEntity(*nestedEntity);
}

void NamespaceFragment::setNestedEntitiesCapacity(std::size_t capacity) noexcept
{
	getPimpl()->setNestedEntitiesCapacity(capacity);
}

bool NamespaceFragment::addProperty(Property const* property) noexcept
{
	return getPimpl()->addProperty(property);
}

Namespace const& NamespaceFragment::getMergedNamespace() const noexcept
{
	return *getPimpl()->getMergedNamespace().get();
}

bool NamespaceFragment::foreachNestedEntity(Visitor<Entity> visitor, void* userData) const
{
	return Algorithm::foreach(getPimpl()->getNestedEntities(), visitor, userData);
}

void NamespaceFragment::unmergeFragment() const noexcept
{
	getPimpl()->unmergeFragment();
}