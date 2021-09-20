#include "Refureku/TypeInfo/Functions/Function.h"

using namespace rfk;

Function::Function(std::string&& name, std::size_t id, Type const& returnType, std::unique_ptr<ICallable>&& internalMethod, EFunctionFlags flags) noexcept:
	FunctionBase(std::forward<std::string>(name), id, EEntityKind::Function, returnType, std::forward<std::unique_ptr<ICallable>>(internalMethod)),
	_flags{flags}
{
}