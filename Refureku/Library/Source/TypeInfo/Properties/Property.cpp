#include "Refureku/TypeInfo/Properties/Property.h"

using namespace rfk;

rfk::EEntityKind Property::getTargetEntityKind() const noexcept
{
	return targetEntityKind;
}

bool Property::getShouldInherit() const noexcept
{
	return shouldInherit;
}

bool Property::getAllowMultiple() const noexcept
{
	return allowMultiple;
}