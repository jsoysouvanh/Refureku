#include "Refureku/TypeInfo/Variables/FieldBase.h"

#include <utility>	//std::forward

using namespace rfk;

FieldBase::FieldBase(std::string&& name, uint64 id, Type const& type, EFieldFlags flags, Struct const* containedIn, Entity const* outerEntity) noexcept:
	VariableBase(std::forward<std::string>(name), id, EEntityKind::Field, type, outerEntity),
	_flags{flags},
	_containedIn{containedIn}
{
}

EAccessSpecifier FieldBase::getAccess() const noexcept
{
	using UnderlyingType = std::underlying_type_t<EFieldFlags>;

	return	(static_cast<UnderlyingType>(_flags & EFieldFlags::Public)) ? EAccessSpecifier::Public :
			(static_cast<UnderlyingType>(_flags & EFieldFlags::Protected)) ? EAccessSpecifier::Protected :
			(static_cast<UnderlyingType>(_flags & EFieldFlags::Private)) ? EAccessSpecifier::Private :
			EAccessSpecifier::Undefined;
}