#include "Refureku/TypeInfo/Fields/FieldBase.h"

#include <utility>	//std::forward

using namespace rfk;

FieldBase::FieldBase(std::string&& name, uint64 id, Type const& type, EFieldFlags flags, Struct const* ownerStruct) noexcept:
	VariableBase(std::forward<std::string>(name), id, EKind::Field, type),
	flags{flags},
	ownerStruct{ownerStruct}
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