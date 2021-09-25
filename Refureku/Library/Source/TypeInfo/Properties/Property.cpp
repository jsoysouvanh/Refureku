#include "Refureku/TypeInfo/Properties/Property.h"

using namespace rfk;

template class REFUREKU_API rfk::Allocator<Property const*>;
template class REFUREKU_API Vector<Property const*, rfk::Allocator<Property const*>>;

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