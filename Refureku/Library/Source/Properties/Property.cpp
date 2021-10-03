#include "Refureku/Properties/Property.h"

using namespace rfk;

template class REFUREKU_TEMPLATE_API_DEF rfk::Allocator<Property const*>;
template class REFUREKU_TEMPLATE_API_DEF rfk::Vector<Property const*, rfk::Allocator<Property const*>>;

rfk::EEntityKind Property::getTargetEntityKind() const noexcept
{
	return Property::targetEntityKind;
}

bool Property::getShouldInherit() const noexcept
{
	return Property::shouldInherit;
}

bool Property::getAllowMultiple() const noexcept
{
	return Property::allowMultiple;
}