#include "TypeInfo/Fields/Field.h"

#include <utility>	//std::forward

using namespace refureku;

Field::Field(std::string&& name, uint64 id, EAccessSpecifier access, Struct const* ownerStruct, Struct const* introducedBy, uint32 memoryOffset) noexcept:
	FieldBase(std::forward<std::string>(name), id, access, ownerStruct, introducedBy),
	memoryOffset{memoryOffset}
{
}

void* Field::getDataAddress(void* instance) const noexcept
{
	return reinterpret_cast<char*>(instance) + memoryOffset;
}