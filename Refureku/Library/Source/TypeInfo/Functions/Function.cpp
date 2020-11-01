#include "Refureku/TypeInfo/Functions/Function.h"

using namespace rfk;

Function::Function(std::string&& name, uint64 id, Type const& returnType, std::unique_ptr<ICallable>&& internalMethod, EFunctionFlags flags) noexcept:
	FunctionBase(std::forward<std::string>(name), id, EEntityKind::Function, returnType, std::forward<std::unique_ptr<ICallable>>(internalMethod)),
	flags{flags}
{
}

bool Function::isInline() const noexcept
{
	return (flags & EFunctionFlags::Inline) != EFunctionFlags::Default;
}

bool Function::isStatic() const noexcept
{
	return (flags & EFunctionFlags::Static) != EFunctionFlags::Default;
}