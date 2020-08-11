#include "Refureku/TypeInfo/Functions/Function.h"

using namespace rfk;

Function::Function(std::string&& name, uint64 id, Type const& returnType, std::unique_ptr<ICallable>&& internalMethod, EFunctionFlags flags) noexcept:
	FunctionBase(std::forward<std::string>(name), id, EKind::Function, returnType, std::forward<std::unique_ptr<ICallable>>(internalMethod)),
	flags{flags}
{
}