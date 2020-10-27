#include "Refureku/TypeInfo/Functions/Method.h"

#include <cassert>

using namespace rfk;

Method::Method(std::string&& methodName, uint64 methodId, Type const& returnType, std::unique_ptr<ICallable>&& internalMethod, EMethodFlags flags) noexcept:
	MethodBase(std::forward<std::string>(methodName), methodId, returnType, std::forward<std::unique_ptr<ICallable>>(internalMethod), flags)
{
	assert(!static_cast<std::underlying_type_t<EMethodFlags>>(flags & EMethodFlags::Static));
}