#include "Refureku/TypeInfo/Functions/FunctionBase.h"

using namespace rfk;

FunctionBase::FunctionBase(std::string&& name, uint64 id, EKind kind, Type const& returnType, std::unique_ptr<ICallable>&& internalMethod) noexcept:
	Entity(std::forward<std::string>(name), id, kind),
	internalMethod{std::forward<std::unique_ptr<ICallable>>(internalMethod)},
	returnType{returnType}
{
}