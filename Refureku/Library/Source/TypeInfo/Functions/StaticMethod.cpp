#include "Refureku/TypeInfo/Functions/StaticMethod.h"

#include "Refureku/TypeInfo/Functions/StaticMethodImpl.h"

using namespace rfk;

template class REFUREKU_TEMPLATE_API_DEF rfk::Allocator<StaticMethod const*>;
template class REFUREKU_TEMPLATE_API_DEF rfk::Vector<StaticMethod const*, rfk::Allocator<StaticMethod const*>>;

StaticMethod::StaticMethod(char const* name, std::size_t id, Type const& returnType,
								 ICallable* internalMethod, EMethodFlags flags, Entity const* outerEntity) noexcept:
	MethodBase(new StaticMethodImpl(name, id, returnType, internalMethod, flags, outerEntity))
{
}

StaticMethod::StaticMethod(StaticMethod&&) noexcept = default;

StaticMethod::~StaticMethod() noexcept = default;