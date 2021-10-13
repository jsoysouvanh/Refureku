#include "Refureku/TypeInfo/Functions/Function.h"

#include <type_traits>	//std::underlying_type_t

#include "Refureku/TypeInfo/Functions/FunctionImpl.h"

using namespace rfk;

using EFunctionFlagsUnderlyingType = std::underlying_type_t<EFunctionFlags>;

Function::Function(char const* name, std::size_t id, Type const& returnType, ICallable* internalFunction, EFunctionFlags flags) noexcept:
	FunctionBase(new FunctionImpl(name, id, returnType, internalFunction, flags))
{
}

Function::~Function() noexcept = default;

bool Function::isInline() const noexcept
{
	return static_cast<EFunctionFlagsUnderlyingType>(getFlags() & EFunctionFlags::Inline) != static_cast<EFunctionFlagsUnderlyingType>(0);
}

bool Function::isStatic() const noexcept
{
	return static_cast<EFunctionFlagsUnderlyingType>(getFlags() & EFunctionFlags::Static) != static_cast<EFunctionFlagsUnderlyingType>(0);
}

EFunctionFlags Function::getFlags() const noexcept
{
	return getPimpl()->getFlags();
}