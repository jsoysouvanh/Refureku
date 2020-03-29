#include "TypeInfo/Methods/MethodBase.h"

using namespace rfk;

MethodBase::MethodBase(std::string&& name, uint64 id, EMethodFlags flags, std::shared_ptr<ICallable>&& internalMethod) noexcept:
	Entity(std::forward<std::string>(name), id),
	_internalMethod{std::forward<std::shared_ptr<ICallable>>(internalMethod)},
	flags{flags}
{
}

EAccessSpecifier MethodBase::getAccess() const noexcept
{
	return	(flags & EMethodFlags::Public) ? EAccessSpecifier::Public :
			(flags & EMethodFlags::Protected) ? EAccessSpecifier::Protected :
			(flags & EMethodFlags::Private) ? EAccessSpecifier::Private :
			EAccessSpecifier::Undefined;
}

bool MethodBase::isStatic() const noexcept
{
	return flags & EMethodFlags::Static;
}

bool MethodBase::isInline() const noexcept
{
	return flags & EMethodFlags::Inline;
}

bool MethodBase::isVirtual() const noexcept
{
	return flags & EMethodFlags::Virtual;
}

bool MethodBase::isPureVirtual() const noexcept
{
	return flags & EMethodFlags::PureVirtual;
}

bool MethodBase::isOverride() const noexcept
{
	return flags & EMethodFlags::Override;
}

bool MethodBase::isFinal() const noexcept
{
	return flags & EMethodFlags::Final;
}

bool MethodBase::isConst() const noexcept
{
	return flags & EMethodFlags::Const;
}