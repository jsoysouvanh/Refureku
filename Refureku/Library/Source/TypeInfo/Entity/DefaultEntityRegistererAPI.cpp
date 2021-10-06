#include "Refureku/TypeInfo/Entity/DefaultEntityRegistererAPI.h"

#include "Refureku/TypeInfo/Entity/DefaultEntityRegistererImpl.h"

using namespace rfk;

DefaultEntityRegistererAPI::DefaultEntityRegistererAPI(Entity const& entity) noexcept:
	_pimpl(new internal::DefaultEntityRegistererImpl(entity))
{
}

DefaultEntityRegistererAPI::~DefaultEntityRegistererAPI() noexcept = default;