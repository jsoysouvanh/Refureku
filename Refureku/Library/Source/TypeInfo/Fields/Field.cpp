#include "TypeInfo/Fields/Field.h"

#include <cstring>	//std::memcpy
#include <utility>	//std::forward

using namespace refureku;

Field::Field(std::string&& name, uint64 id, EAccessSpecifier access, Struct const* ownerStruct, Struct const* introducedBy, uint32 memoryOffset, bool isMutable) noexcept:
	FieldBase(std::forward<std::string>(name), id, access, ownerStruct, introducedBy),
	memoryOffset{memoryOffset},
	isMutable{isMutable}
{
}

void* Field::getDataAddress(void* instance) const noexcept
{
	return reinterpret_cast<char*>(instance) + memoryOffset;
}

void Field::setData(void* instance, void const* data, uint64 dataSize) const noexcept
{
	std::memcpy(getDataAddress(instance), data, dataSize);
}