#include "Refureku/TypeInfo/Functions/MethodBase.h"

using namespace rfk;

MethodBase::MethodBase(std::string&& name, uint64 id, Type const& returnType, std::unique_ptr<ICallable>&& internalMethod, EMethodFlags flags, Entity const* outerEntity) noexcept:
	FunctionBase(std::forward<std::string>(name), id, EEntityKind::Method, returnType, std::forward<std::unique_ptr<ICallable>>(internalMethod), outerEntity),
	_flags{flags}
{
}

EAccessSpecifier MethodBase::getAccess() const noexcept
{
	using UnderlyingType = std::underlying_type_t<EMethodFlags>;

	return	(static_cast<UnderlyingType>(getFlags() & EMethodFlags::Public)) ? EAccessSpecifier::Public :
			(static_cast<UnderlyingType>(getFlags() & EMethodFlags::Protected)) ? EAccessSpecifier::Protected :
			(static_cast<UnderlyingType>(getFlags() & EMethodFlags::Private)) ? EAccessSpecifier::Private :
			EAccessSpecifier::Undefined;
}