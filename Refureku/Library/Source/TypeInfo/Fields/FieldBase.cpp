#include "TypeInfo/Fields/FieldBase.h"

#include <utility>	//std::forward

using namespace rfk;

FieldBase::FieldBase(std::string&& name, uint64 id, EFieldFlags flags, Struct const* ownerStruct, Struct const* introducedBy) noexcept:
	Entity(std::forward<std::string>(name), id, EKind::Field),
	flags{flags},
	ownerStruct{ownerStruct},
	introducedBy{introducedBy}
{
}

EAccessSpecifier FieldBase::getAccess() const noexcept
{
	using UnderlyingType = std::underlying_type_t<EFieldFlags>;

	return	(static_cast<UnderlyingType>(flags & EFieldFlags::Public)) ? EAccessSpecifier::Public :
			(static_cast<UnderlyingType>(flags & EFieldFlags::Protected)) ? EAccessSpecifier::Protected :
			(static_cast<UnderlyingType>(flags & EFieldFlags::Private)) ? EAccessSpecifier::Private :
			EAccessSpecifier::Undefined;
}

bool FieldBase::isStatic() const noexcept
{
	return static_cast<std::underlying_type_t<EFieldFlags>>(flags & EFieldFlags::Static);
}

bool FieldBase::isMutable() const noexcept
{
	return static_cast<std::underlying_type_t<EFieldFlags>>(flags & EFieldFlags::Mutable);
}