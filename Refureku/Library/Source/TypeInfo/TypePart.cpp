#include "Refureku/TypeInfo/TypePart.h"

using namespace rfk;

TypePart::TypePart() noexcept = default;

TypePart::TypePart(ETypePartDescriptor descriptor, AdditionalDataType additionalData) noexcept:
	_additionalData{additionalData},
	_descriptor{descriptor}
{
}

void TypePart::addDescriptorFlag(ETypePartDescriptor flag) noexcept
{
	_descriptor = _descriptor | flag;
}

bool TypePart::isPointer() const noexcept
{
	return static_cast<std::underlying_type_t<ETypePartDescriptor>>(_descriptor & ETypePartDescriptor::Ptr) != 0u;
}

bool TypePart::isLValueReference() const noexcept
{
	return static_cast<std::underlying_type_t<ETypePartDescriptor>>(_descriptor & ETypePartDescriptor::LRef) != 0u;
}

bool TypePart::isRValueReference() const noexcept
{
	return static_cast<std::underlying_type_t<ETypePartDescriptor>>(_descriptor & ETypePartDescriptor::RRef) != 0u;
}

bool TypePart::isCArray() const noexcept
{
	return static_cast<std::underlying_type_t<ETypePartDescriptor>>(_descriptor & ETypePartDescriptor::CArray) != 0u;
}

bool TypePart::isValue() const noexcept
{
	return static_cast<std::underlying_type_t<ETypePartDescriptor>>(_descriptor & ETypePartDescriptor::Value) != 0u;
}

bool TypePart::isConst() const noexcept
{
	return static_cast<std::underlying_type_t<ETypePartDescriptor>>(_descriptor & ETypePartDescriptor::Const) != 0u;
}

bool TypePart::isVolatile() const noexcept
{
	return static_cast<std::underlying_type_t<ETypePartDescriptor>>(_descriptor & ETypePartDescriptor::Volatile) != 0u;
}

TypePart::AdditionalDataType TypePart::getCArraySize() const noexcept
{
	return _additionalData;
}

void TypePart::setAdditionalData(AdditionalDataType data) noexcept
{
	_additionalData = data;
}