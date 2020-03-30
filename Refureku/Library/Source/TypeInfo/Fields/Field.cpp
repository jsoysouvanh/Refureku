#include "TypeInfo/Fields/Field.h"

#include <cstring>	//std::memcpy
#include <utility>	//std::forward
#include <cassert>

using namespace rfk;

Field::Field(std::string&& name, uint64 id, EFieldFlags flags, Struct const* ownerStruct, Struct const* introducedBy, uint32 memoryOffset, bool isMutable) noexcept:
	FieldBase(std::forward<std::string>(name), id, flags, ownerStruct, introducedBy),
	memoryOffset{memoryOffset},
	isMutable{isMutable}
{
	assert(!static_cast<std::underlying_type_t<EFieldFlags>>(flags & EFieldFlags::Static));
}

void* Field::getDataAddress(void* instance) const noexcept
{
	return reinterpret_cast<char*>(instance) + memoryOffset;
}

void Field::setData(void* instance, void const* data, uint64 dataSize) const noexcept
{
	std::memcpy(getDataAddress(instance), data, dataSize);
}