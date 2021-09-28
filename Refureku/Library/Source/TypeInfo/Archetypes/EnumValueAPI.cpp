#include "Refureku/TypeInfo/Archetypes/EnumValueAPI.h"

#include "Refureku/TypeInfo/Archetypes/EnumValueImpl.h"

using namespace rfk;

template class REFUREKU_TEMPLATE_API_DEF rfk::Allocator<EnumValueAPI const*>;
template class REFUREKU_TEMPLATE_API_DEF rfk::Vector<EnumValueAPI const*, rfk::Allocator<EnumValueAPI const*>>;

EnumValueAPI::EnumValueAPI(char const* name, std::size_t id, int64 value, EntityAPI const* outerEntity) noexcept:
	EntityAPI(),
	_pimpl(name, id, value, outerEntity)
{
	EntityAPI::setImpl(_pimpl.get());
}

EnumValueAPI::EnumValueAPI(EnumValueAPI const& other) noexcept:
	_pimpl{other._pimpl}
{
	EntityAPI::setImpl(_pimpl.get());
}

EnumValueAPI::EnumValueAPI(EnumValueAPI&& other) noexcept:
	_pimpl{std::forward<Pimpl<EnumValueImpl>>(other._pimpl)}
{
	EntityAPI::setImpl(_pimpl.get());
}

EnumValueAPI::~EnumValueAPI() noexcept
{
	//Must be defined in cpp since _pimpl is an incomplete type in the header file
}

int64 EnumValueAPI::getValue() const noexcept
{
	return _pimpl->getValue();
}