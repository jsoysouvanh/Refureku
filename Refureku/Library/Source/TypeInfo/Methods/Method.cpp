#include "TypeInfo/Methods/Method.h"

#include <cassert>

using namespace rfk;

Method::Method(std::string&&				methodName,
			   uint64						methodId,
			   EMethodFlags					flags,
			   std::shared_ptr<ICallable>&& internalMethod,
			   Struct const*				methodOwnerType) noexcept:
	MethodBase(std::forward<std::string>(methodName), methodId, flags, std::forward<std::shared_ptr<ICallable>>(internalMethod)),
	ownerType{methodOwnerType}
{
	assert(!static_cast<std::underlying_type_t<EMethodFlags>>(flags & EMethodFlags::Static));
}