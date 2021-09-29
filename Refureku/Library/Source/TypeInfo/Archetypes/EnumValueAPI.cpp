#include "Refureku/TypeInfo/Archetypes/EnumValueAPI.h"

#include "Refureku/TypeInfo/Archetypes/EnumValueImpl.h"

using namespace rfk;

template class REFUREKU_TEMPLATE_API_DEF rfk::Allocator<EnumValueAPI const*>;
template class REFUREKU_TEMPLATE_API_DEF rfk::Vector<EnumValueAPI const*, rfk::Allocator<EnumValueAPI const*>>;

EnumValueAPI::EnumValueAPI(char const* name, std::size_t id, int64 value, EntityAPI const* outerEntity) noexcept:
	EntityAPI(new EnumValueImpl(name, id, value, outerEntity))
{
}

EnumValueAPI::EnumValueAPI(EnumValueAPI&& other) noexcept = default;

EnumValueAPI::~EnumValueAPI() noexcept = default;

int64 EnumValueAPI::getValue() const noexcept
{
	return reinterpret_cast<EnumValueImpl const*>(getPimpl())->getValue();
}