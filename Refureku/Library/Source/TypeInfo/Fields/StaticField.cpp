#include "TypeInfo/Fields/StaticField.h"

#include <cstring>	//std::memcpy
#include <utility>	//std::forward

using namespace rfk;

StaticField::StaticField(std::string&& name, uint64 id, EAccessSpecifier access, Struct const* ownerStruct, Struct const* introducedBy, void* ptrToData) noexcept:
	FieldBase(std::forward<std::string>(name), id, access, ownerStruct, introducedBy),
	dataAddress{ptrToData}
{
}

void* StaticField::getDataAddress() const noexcept
{
	return dataAddress;
}

void StaticField::setData(void const* data, uint64 dataSize) const noexcept
{
	std::memcpy(getDataAddress(), data, dataSize);
}