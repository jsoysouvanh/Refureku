#include "Refureku/TypeInfo/Methods/MethodBase.h"

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