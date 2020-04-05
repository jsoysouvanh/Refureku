#include "TypeInfo/Fields/StaticField.h"

using namespace rfk;

StaticField::StaticField(std::string&& name, uint64 id, EFieldFlags flags, Struct const* ownerStruct, Struct const* introducedBy, void* ptrToData) noexcept:
	FieldBase(std::forward<std::string>(name), id, flags, ownerStruct, introducedBy),
	dataAddress{ptrToData}
{
	assert(static_cast<std::underlying_type_t<EFieldFlags>>(flags & EFieldFlags::Static));
}