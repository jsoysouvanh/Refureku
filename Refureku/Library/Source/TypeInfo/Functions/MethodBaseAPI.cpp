#include "Refureku/TypeInfo/Functions/MethodBaseAPI.h"

#include <type_traits>

#include "Refureku/TypeInfo/Functions/MethodBaseImpl.h"

using namespace rfk;

using EMethodFlagsUnderlyingType = std::underlying_type_t<EMethodFlags>;

MethodBaseAPI::MethodBaseAPI(MethodBaseImpl* implementation) noexcept:
	FunctionBaseAPI(implementation)
{
}

MethodBaseAPI::MethodBaseAPI(MethodBaseAPI&&) noexcept = default;

MethodBaseAPI::~MethodBaseAPI() noexcept = default;

bool MethodBaseAPI::isStatic() const noexcept
{
	return static_cast<EMethodFlagsUnderlyingType>(getFlags() & EMethodFlags::Static) != static_cast<EMethodFlagsUnderlyingType>(0);
}
	 
bool MethodBaseAPI::isInline() const noexcept
{
	return static_cast<EMethodFlagsUnderlyingType>(getFlags() & EMethodFlags::Inline) != static_cast<EMethodFlagsUnderlyingType>(0);
}
	 
bool MethodBaseAPI::isVirtual() const noexcept
{
	return static_cast<EMethodFlagsUnderlyingType>(getFlags() & EMethodFlags::Virtual) != static_cast<EMethodFlagsUnderlyingType>(0);
}
	 
bool MethodBaseAPI::isPureVirtual() const noexcept
{
	return static_cast<EMethodFlagsUnderlyingType>(getFlags() & EMethodFlags::PureVirtual) != static_cast<EMethodFlagsUnderlyingType>(0);
}	 
	 
bool MethodBaseAPI::isOverride() const noexcept
{
	return static_cast<EMethodFlagsUnderlyingType>(getFlags() & EMethodFlags::Override) != static_cast<EMethodFlagsUnderlyingType>(0);
}
	 
bool MethodBaseAPI::isFinal() const noexcept
{
	return static_cast<EMethodFlagsUnderlyingType>(getFlags() & EMethodFlags::Final) != static_cast<EMethodFlagsUnderlyingType>(0);
}
	 
bool MethodBaseAPI::isConst() const noexcept
{
	return static_cast<EMethodFlagsUnderlyingType>(getFlags() & EMethodFlags::Const) != static_cast<EMethodFlagsUnderlyingType>(0);
}

EMethodFlags MethodBaseAPI::getFlags() const noexcept
{
	return reinterpret_cast<MethodBaseImpl const*>(getPimpl())->getFlags();
}

EAccessSpecifier MethodBaseAPI::getAccess() const noexcept
{
	EMethodFlags flags = getFlags();

	return	(static_cast<EMethodFlagsUnderlyingType>(flags & EMethodFlags::Public) != static_cast<EMethodFlagsUnderlyingType>(0)) ? EAccessSpecifier::Public :
			(static_cast<EMethodFlagsUnderlyingType>(flags & EMethodFlags::Protected) != static_cast<EMethodFlagsUnderlyingType>(0)) ? EAccessSpecifier::Protected :
			(static_cast<EMethodFlagsUnderlyingType>(flags & EMethodFlags::Private) != static_cast<EMethodFlagsUnderlyingType>(0)) ? EAccessSpecifier::Private :
			EAccessSpecifier::Undefined;
}