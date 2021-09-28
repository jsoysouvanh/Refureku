#include "Refureku/TypeInfo/Archetypes/EnumValueAPI.h"

#include "Refureku/TypeInfo/Archetypes/EnumValueImpl.h"

using namespace rfk;

template class REFUREKU_TEMPLATE_API_DEF rfk::Allocator<EnumValueAPI const*>;
template class REFUREKU_TEMPLATE_API_DEF rfk::Vector<EnumValueAPI const*, rfk::Allocator<EnumValueAPI const*>>;

EnumValueAPI::EnumValueAPI(char const* name, std::size_t id, int64 value, EntityAPI const* outerEntity) noexcept:
	EntityAPI(new EnumValueImpl(name, id, value, outerEntity), &EnumValueAPI::customDeleter)
{
}

EnumValueAPI::EnumValueAPI(EnumValueAPI const& other) noexcept:
	EntityAPI(new EnumValueImpl(*reinterpret_cast<EnumValueImpl const*>(other.getPimpl())), &EnumValueAPI::customDeleter)
{
}

EnumValueAPI::EnumValueAPI(EnumValueAPI&& other) noexcept = default;

EnumValueAPI::~EnumValueAPI() noexcept
{
	//Must be defined in cpp since _pimpl is an incomplete type in the header file
}

void EnumValueAPI::customDeleter(EntityImpl* ptr) noexcept
{
	delete reinterpret_cast<EnumValueImpl*>(ptr);
}

int64 EnumValueAPI::getValue() const noexcept
{
	return reinterpret_cast<EnumValueImpl const*>(getPimpl())->getValue();
}