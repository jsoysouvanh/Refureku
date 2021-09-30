#include "Refureku/TypeInfo/Functions/FunctionAPI.h"

#include <type_traits>	//std::underlying_type_t

#include "Refureku/TypeInfo/Functions/FunctionImpl.h"

using namespace rfk;

using EFunctionFlagsUnderlyingType = std::underlying_type_t<EFunctionFlags>;

FunctionAPI::FunctionAPI(char const* name, std::size_t id, TypeAPI const& returnType, ICallable* internalFunction, EFunctionFlags flags) noexcept:
	FunctionBaseAPI(new FunctionImpl(name, id, returnType, internalFunction, flags))
{
}

FunctionAPI::~FunctionAPI() noexcept = default;

bool FunctionAPI::isInline() const noexcept
{
	return static_cast<EFunctionFlagsUnderlyingType>(getFlags() & EFunctionFlags::Inline) != static_cast<EFunctionFlagsUnderlyingType>(0);
}

bool FunctionAPI::isStatic() const noexcept
{
	return static_cast<EFunctionFlagsUnderlyingType>(getFlags() & EFunctionFlags::Static) != static_cast<EFunctionFlagsUnderlyingType>(0);
}

EFunctionFlags FunctionAPI::getFlags() const noexcept
{
	return reinterpret_cast<FunctionImpl const*>(getPimpl())->getFlags();
}