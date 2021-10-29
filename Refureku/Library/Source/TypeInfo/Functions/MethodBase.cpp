#include "Refureku/TypeInfo/Functions/MethodBase.h"

#include <type_traits>	//std::underlying_type_t

#include "Refureku/TypeInfo/Functions/MethodBaseImpl.h"

using namespace rfk;

using EMethodFlagsUnderlyingType = std::underlying_type_t<EMethodFlags>;

MethodBase::MethodBase(MethodBaseImpl* implementation) noexcept:
	FunctionBase(implementation)
{
}

MethodBase::MethodBase(MethodBase&&) noexcept = default;

MethodBase::~MethodBase() noexcept = default;

bool MethodBase::hasSameSignature(MethodBase const& other) const noexcept
{
	return isConst() == other.isConst() && FunctionBase::hasSameSignature(other);
}

bool MethodBase::isStatic() const noexcept
{
	return static_cast<EMethodFlagsUnderlyingType>(getFlags() & EMethodFlags::Static) != static_cast<EMethodFlagsUnderlyingType>(0);
}
	 
bool MethodBase::isInline() const noexcept
{
	return static_cast<EMethodFlagsUnderlyingType>(getFlags() & EMethodFlags::Inline) != static_cast<EMethodFlagsUnderlyingType>(0);
}
	 
bool MethodBase::isVirtual() const noexcept
{
	return static_cast<EMethodFlagsUnderlyingType>(getFlags() & EMethodFlags::Virtual) != static_cast<EMethodFlagsUnderlyingType>(0);
}
	 
bool MethodBase::isPureVirtual() const noexcept
{
	return static_cast<EMethodFlagsUnderlyingType>(getFlags() & EMethodFlags::PureVirtual) != static_cast<EMethodFlagsUnderlyingType>(0);
}	 
	 
bool MethodBase::isOverride() const noexcept
{
	return static_cast<EMethodFlagsUnderlyingType>(getFlags() & EMethodFlags::Override) != static_cast<EMethodFlagsUnderlyingType>(0);
}
	 
bool MethodBase::isFinal() const noexcept
{
	return static_cast<EMethodFlagsUnderlyingType>(getFlags() & EMethodFlags::Final) != static_cast<EMethodFlagsUnderlyingType>(0);
}
	 
bool MethodBase::isConst() const noexcept
{
	return static_cast<EMethodFlagsUnderlyingType>(getFlags() & EMethodFlags::Const) != static_cast<EMethodFlagsUnderlyingType>(0);
}

EMethodFlags MethodBase::getFlags() const noexcept
{
	return getPimpl()->getFlags();
}

EAccessSpecifier MethodBase::getAccess() const noexcept
{
	EMethodFlags flags = getFlags();

	return	(static_cast<EMethodFlagsUnderlyingType>(flags & EMethodFlags::Public) != static_cast<EMethodFlagsUnderlyingType>(0)) ? EAccessSpecifier::Public :
			(static_cast<EMethodFlagsUnderlyingType>(flags & EMethodFlags::Protected) != static_cast<EMethodFlagsUnderlyingType>(0)) ? EAccessSpecifier::Protected :
			(static_cast<EMethodFlagsUnderlyingType>(flags & EMethodFlags::Private) != static_cast<EMethodFlagsUnderlyingType>(0)) ? EAccessSpecifier::Private :
			EAccessSpecifier::Undefined;
}