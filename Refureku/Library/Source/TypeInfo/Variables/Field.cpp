#include "Refureku/TypeInfo/Variables/Field.h"

using namespace rfk;

Field::Field(std::string&& name, std::size_t id, Type const& type, EFieldFlags flags, Struct const* containedIn, std::size_t memoryOffset, Entity const* outerEntity) noexcept:
	FieldBase(std::forward<std::string>(name), id, type, flags, containedIn, outerEntity),
	_memoryOffset{memoryOffset}
{
	assert(!static_cast<std::underlying_type_t<EFieldFlags>>(flags & EFieldFlags::Static));
}