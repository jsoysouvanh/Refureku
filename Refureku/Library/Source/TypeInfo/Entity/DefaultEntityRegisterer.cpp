#include "Refureku/TypeInfo/Entity/DefaultEntityRegisterer.h"

#include "Refureku/TypeInfo/Entity/DefaultEntityRegistererImpl.h"

using namespace rfk;

DefaultEntityRegisterer::DefaultEntityRegisterer(Entity const& entity) noexcept:
	_pimpl(new internal::DefaultEntityRegistererImpl(entity))
{
}

DefaultEntityRegisterer::~DefaultEntityRegisterer() noexcept = default;