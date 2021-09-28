#include "Refureku/TypeInfo/TypePartAPI.h"

using namespace rfk;

TypePartAPI::TypePartAPI(ETypePartDescriptor descriptor, AdditionalDataType additionalData) noexcept:
	_additionalData{additionalData},
	_descriptor{descriptor}
{
}

void TypePartAPI::addDescriptorFlag(ETypePartDescriptor flag) noexcept
{
	_descriptor = _descriptor | flag;
}

bool TypePartAPI::isPointer() const noexcept
{
	return static_cast<std::underlying_type_t<ETypePartDescriptor>>(_descriptor & ETypePartDescriptor::Ptr) != 0u;
}

bool TypePartAPI::isLValueReference() const noexcept
{
	return static_cast<std::underlying_type_t<ETypePartDescriptor>>(_descriptor & ETypePartDescriptor::LRef) != 0u;
}

bool TypePartAPI::isRValueReference() const noexcept
{
	return static_cast<std::underlying_type_t<ETypePartDescriptor>>(_descriptor & ETypePartDescriptor::RRef) != 0u;
}

bool TypePartAPI::isCArray() const noexcept
{
	return static_cast<std::underlying_type_t<ETypePartDescriptor>>(_descriptor & ETypePartDescriptor::CArray) != 0u;
}

bool TypePartAPI::isValue() const noexcept
{
	return static_cast<std::underlying_type_t<ETypePartDescriptor>>(_descriptor & ETypePartDescriptor::Value) != 0u;
}

bool TypePartAPI::isConst() const noexcept
{
	return static_cast<std::underlying_type_t<ETypePartDescriptor>>(_descriptor & ETypePartDescriptor::Const) != 0u;
}

bool TypePartAPI::isVolatile() const noexcept
{
	return static_cast<std::underlying_type_t<ETypePartDescriptor>>(_descriptor & ETypePartDescriptor::Volatile) != 0u;
}

TypePartAPI::AdditionalDataType TypePartAPI::getCArraySize() const noexcept
{
	return (isCArray()) ? _additionalData : 0u;
}

void TypePartAPI::setAdditionalData(AdditionalDataType data) noexcept
{
	_additionalData = data;
}