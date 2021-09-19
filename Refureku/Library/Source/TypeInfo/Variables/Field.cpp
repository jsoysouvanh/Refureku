#include "Refureku/TypeInfo/Variables/Field.h"

using namespace rfk;

Field::Field(std::string&& name, uint64 id, Type const& type, EFieldFlags flags, Struct const* ownerStruct, uint64 memoryOffset, Entity const* outerEntity) noexcept:
	FieldBase(std::forward<std::string>(name), id, type, flags, ownerStruct, outerEntity),
	memoryOffset{memoryOffset}
{
	assert(!static_cast<std::underlying_type_t<EFieldFlags>>(flags & EFieldFlags::Static));
}