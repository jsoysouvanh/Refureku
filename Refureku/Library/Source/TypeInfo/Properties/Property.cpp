#include "Refureku/TypeInfo/Properties/Property.h"

using namespace rfk;

Property::~Property() noexcept
{
	//Must define default destructor for correct vtable export on GCC/Clang
}

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