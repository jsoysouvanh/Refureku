#include "Refureku/TypeInfo/Fields/StaticField.h"

using namespace rfk;

StaticField::StaticField(std::string&& name, uint64 id, EFieldFlags flags, Struct const* ownerStruct, void* ptrToData) noexcept:
	FieldBase(std::forward<std::string>(name), id, flags, ownerStruct),
	dataAddress{ptrToData}
{
	assert(static_cast<std::underlying_type_t<EFieldFlags>>(flags & EFieldFlags::Static));
}