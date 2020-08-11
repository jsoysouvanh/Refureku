#include "Refureku/TypeInfo/Variables/StaticField.h"

using namespace rfk;

StaticField::StaticField(std::string&& name, uint64 id, Type const& type, EFieldFlags flags, Struct const* ownerStruct, void* ptrToData) noexcept:
	FieldBase(std::forward<std::string>(name), id, type, flags, ownerStruct),
	dataAddress{ptrToData}
{
	assert(static_cast<std::underlying_type_t<EFieldFlags>>(flags & EFieldFlags::Static));
}