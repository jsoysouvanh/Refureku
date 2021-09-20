#include "Refureku/TypeInfo/Variables/StaticField.h"

using namespace rfk;

StaticField::StaticField(std::string&& name, std::size_t id, Type const& type, EFieldFlags flags, Struct const* containedIn, void* address, Entity const* outerEntity) noexcept:
	FieldBase(std::forward<std::string>(name), id, type, flags, containedIn, outerEntity),
	_address{address}
{
	assert(static_cast<std::underlying_type_t<EFieldFlags>>(flags & EFieldFlags::Static));
}

StaticField::StaticField(std::string&& name, std::size_t id, Type const& type, EFieldFlags flags, Struct const* containedIn, void const* address, Entity const* outerEntity) noexcept:
	FieldBase(std::forward<std::string>(name), id, type, flags, containedIn, outerEntity),
	_constAddress{address}
{
	assert(static_cast<std::underlying_type_t<EFieldFlags>>(flags & EFieldFlags::Static));
}