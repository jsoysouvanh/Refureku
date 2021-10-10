#include "Refureku/TypeInfo/Variables/FieldBase.h"

#include <type_traits>

#include "Refureku/TypeInfo/Variables/FieldBaseImpl.h"

using namespace rfk;

using EFieldFlagsUnderlyingType = std::underlying_type_t<EFieldFlags>;

FieldBase::FieldBase(FieldBaseImpl* implementation) noexcept:
	VariableBase(implementation)
{
}

FieldBase::FieldBase(FieldBase&&) noexcept = default;

FieldBase::~FieldBase() noexcept = default;

EAccessSpecifier FieldBase::getAccess() const noexcept
{
	EFieldFlags flags = reinterpret_cast<FieldBaseImpl const*>(getPimpl())->getFlags();

	return	(static_cast<EFieldFlagsUnderlyingType>(flags & EFieldFlags::Public) != static_cast<EFieldFlagsUnderlyingType>(0)) ? EAccessSpecifier::Public :
			(static_cast<EFieldFlagsUnderlyingType>(flags & EFieldFlags::Protected) != static_cast<EFieldFlagsUnderlyingType>(0)) ? EAccessSpecifier::Protected :
			(static_cast<EFieldFlagsUnderlyingType>(flags & EFieldFlags::Private) != static_cast<EFieldFlagsUnderlyingType>(0)) ? EAccessSpecifier::Private :
			EAccessSpecifier::Undefined;
}

bool FieldBase::isStatic() const noexcept
{
	return static_cast<EFieldFlagsUnderlyingType>(getFlags() & EFieldFlags::Static) != static_cast<EFieldFlagsUnderlyingType>(0);
}

bool FieldBase::isMutable() const noexcept
{
	return static_cast<EFieldFlagsUnderlyingType>(getFlags() & EFieldFlags::Mutable) != static_cast<EFieldFlagsUnderlyingType>(0);
}

EFieldFlags FieldBase::getFlags() const noexcept
{
	return reinterpret_cast<FieldBaseImpl const*>(getPimpl())->getFlags();
}

Struct const* FieldBase::getOwner() const noexcept
{
	return reinterpret_cast<FieldBaseImpl const*>(getPimpl())->getOwner();
}