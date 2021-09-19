#include "Refureku/TypeInfo/Functions/StaticMethod.h"

#include <utility>	//std::forward
#include <cassert>

using namespace rfk;

StaticMethod::StaticMethod(std::string&& name, uint64 id, Type const& returnType, std::unique_ptr<ICallable>&& internalMethod, EMethodFlags flags, Entity const* outerEntity) noexcept:
	MethodBase(std::forward<std::string>(name), id, returnType, std::forward<std::unique_ptr<ICallable>>(internalMethod), flags, outerEntity)
{
	assert(static_cast<std::underlying_type_t<EMethodFlags>>(flags & EMethodFlags::Static));
}