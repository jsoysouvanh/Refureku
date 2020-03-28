#include "TypeInfo/Fields/StaticField.h"

#include <utility>	//std::forward

using namespace refureku;

StaticField::StaticField(std::string&& name, uint64 id, EAccessSpecifier access, Struct const* ownerStruct, Struct const* introducedBy, void* ptrToData) noexcept:
	FieldBase(std::forward<std::string>(name), id, access, ownerStruct, introducedBy),
	ptrToData{ptrToData}
{
}