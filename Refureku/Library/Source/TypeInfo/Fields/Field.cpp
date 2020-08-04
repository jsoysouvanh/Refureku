#include "Refureku/TypeInfo/Fields/Field.h"

using namespace rfk;

Field::Field(std::string&& name, uint64 id, EFieldFlags flags, Struct const* ownerStruct, uint64 memoryOffset, bool isMutable) noexcept:
	FieldBase(std::forward<std::string>(name), id, flags, ownerStruct),
	memoryOffset{memoryOffset},
	isMutable{isMutable}
{
	assert(!static_cast<std::underlying_type_t<EFieldFlags>>(flags & EFieldFlags::Static));
}