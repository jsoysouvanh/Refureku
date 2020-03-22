#include "TypeInfo/StaticMethod.h"

#include <utility>	//std::forward

using namespace refureku;

StaticMethod::StaticMethod(ICallable* internalMethod) noexcept:
	MethodBase(internalMethod)
{}

StaticMethod::StaticMethod(StaticMethod&& other) noexcept:
	MethodBase(std::forward<StaticMethod>(other))
{}