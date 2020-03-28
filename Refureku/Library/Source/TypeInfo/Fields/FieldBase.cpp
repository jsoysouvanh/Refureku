#include "TypeInfo/Fields/FieldBase.h"

#include <utility>	//std::forward

using namespace refureku;

FieldBase::FieldBase(std::string&& name, uint64 id, EAccessSpecifier access, Struct const* ownerStruct, Struct const* introducedBy) noexcept:
	Entity(std::forward<std::string>(name), id),
	access{access},
	ownerStruct{ownerStruct},
	introducedBy{introducedBy}
{
}