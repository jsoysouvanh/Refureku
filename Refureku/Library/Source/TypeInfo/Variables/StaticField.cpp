#include "Refureku/TypeInfo/Variables/StaticField.h"

using namespace rfk;

StaticField::StaticField(std::string&& name, uint64 id, Type const& type, EFieldFlags flags, Struct const* ownerStruct, void* address) noexcept:
	FieldBase(std::forward<std::string>(name), id, type, flags, ownerStruct),
	_address{address}
{
	assert(static_cast<std::underlying_type_t<EFieldFlags>>(flags & EFieldFlags::Static));
}

StaticField::StaticField(std::string&& name, uint64 id, Type const& type, EFieldFlags flags, Struct const* ownerStruct, void const* address) noexcept:
	FieldBase(std::forward<std::string>(name), id, type, flags, ownerStruct),
	_constAddress{address}
{
	assert(static_cast<std::underlying_type_t<EFieldFlags>>(flags & EFieldFlags::Static));
}