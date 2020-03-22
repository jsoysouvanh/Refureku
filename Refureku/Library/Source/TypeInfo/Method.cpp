#include "TypeInfo/Method.h"

using namespace refureku;

Method::Method(ICallable* internalMethod) noexcept:
	MethodBase(internalMethod)
{}

Method::Method(Method&& other) noexcept:
	MethodBase(std::forward<Method>(other))
{}