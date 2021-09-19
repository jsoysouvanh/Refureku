#include "Refureku/TypeInfo/Variables/StaticField.h"

using namespace rfk;

StaticField::StaticField(std::string&& name, uint64 id, Type const& type, EFieldFlags flags, Struct const* ownerStruct, void* address, Entity const* outerEntity) noexcept:
	FieldBase(std::forward<std::string>(name), id, type, flags, ownerStruct, outerEntity),
	_address{address}
{
	assert(static_cast<std::underlying_type_t<EFieldFlags>>(flags & EFieldFlags::Static));
}

StaticField::StaticField(std::string&& name, uint64 id, Type const& type, EFieldFlags flags, Struct const* ownerStruct, void const* address, Entity const* outerEntity) noexcept:
	FieldBase(std::forward<std::string>(name), id, type, flags, ownerStruct, outerEntity),
	_constAddress{address}
{
	assert(static_cast<std::underlying_type_t<EFieldFlags>>(flags & EFieldFlags::Static));
}