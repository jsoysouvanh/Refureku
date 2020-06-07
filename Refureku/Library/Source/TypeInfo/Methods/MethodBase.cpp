#include "TypeInfo/Methods/MethodBase.h"

using namespace rfk;

MethodBase::MethodBase(std::string&& name, uint64 id, EMethodFlags flags, std::shared_ptr<ICallable>&& internalMethod) noexcept:
	Entity(std::forward<std::string>(name), id, EKind::Method),
	_internalMethod{std::forward<std::shared_ptr<ICallable>>(internalMethod)},
	flags{flags}
{
}

EAccessSpecifier MethodBase::getAccess() const noexcept
{
	using UnderlyingType = std::underlying_type_t<EMethodFlags>;

	return	(static_cast<UnderlyingType>(flags & EMethodFlags::Public)) ? EAccessSpecifier::Public :
			(static_cast<UnderlyingType>(flags & EMethodFlags::Protected)) ? EAccessSpecifier::Protected :
			(static_cast<UnderlyingType>(flags & EMethodFlags::Private)) ? EAccessSpecifier::Private :
			EAccessSpecifier::Undefined;
}

bool MethodBase::isStatic() const noexcept
{
	return static_cast<std::underlying_type_t<EMethodFlags>>(flags & EMethodFlags::Static);
}

bool MethodBase::isInline() const noexcept
{
	return static_cast<std::underlying_type_t<EMethodFlags>>(flags & EMethodFlags::Inline);
}

bool MethodBase::isVirtual() const noexcept
{
	return static_cast<std::underlying_type_t<EMethodFlags>>(flags & EMethodFlags::Virtual);
}

bool MethodBase::isPureVirtual() const noexcept
{
	return static_cast<std::underlying_type_t<EMethodFlags>>(flags & EMethodFlags::PureVirtual);
}

bool MethodBase::isOverride() const noexcept
{
	return static_cast<std::underlying_type_t<EMethodFlags>>(flags & EMethodFlags::Override);
}

bool MethodBase::isFinal() const noexcept
{
	return static_cast<std::underlying_type_t<EMethodFlags>>(flags & EMethodFlags::Final);
}

bool MethodBase::isConst() const noexcept
{
	return static_cast<std::underlying_type_t<EMethodFlags>>(flags & EMethodFlags::Const);
}