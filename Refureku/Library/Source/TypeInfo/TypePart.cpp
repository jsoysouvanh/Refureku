#include "TypeInfo/TypePart.h"

using namespace rfk;

TypePart::TypePart(uint16 padding, ETypePartDescriptor descriptor, uint32 additionalData) noexcept:
	padding{padding},
	descriptor{descriptor},
	additionalData{additionalData}
{
}