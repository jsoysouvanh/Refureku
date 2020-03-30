#include "TypeInfo/Methods/StaticMethod.h"

#include <utility>	//std::forward
#include <cassert>

using namespace rfk;

StaticMethod::StaticMethod(std::string&&				name,
						   uint64						id,
						   EMethodFlags					flags,
						   std::shared_ptr<ICallable>&&	internalMethod)	noexcept:
	MethodBase(std::forward<std::string>(name), id, flags, std::forward<std::shared_ptr<ICallable>>(internalMethod))
{
	assert(static_cast<std::underlying_type_t<EMethodFlags>>(flags & EMethodFlags::Static));
}