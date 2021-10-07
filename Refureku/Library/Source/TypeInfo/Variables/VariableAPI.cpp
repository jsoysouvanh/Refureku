#include "Refureku/TypeInfo/Variables/VariableAPI.h"

#include "Refureku/TypeInfo/Variables/VariableImpl.h"

using namespace rfk;

VariableAPI::VariableAPI(char const* name, std::size_t id, Type const& type, void* ptr, EVarFlags flags) noexcept:
	VariableBaseAPI(new VariableImpl(name, id, type, ptr, flags))
{
}

VariableAPI::VariableAPI(char const* name, std::size_t id, Type const& type, void const* constPtr, EVarFlags flags) noexcept:
	VariableBaseAPI(new VariableImpl(name, id, type, constPtr, flags))
{
}

VariableAPI::VariableAPI(VariableAPI&&) noexcept = default;

VariableAPI::~VariableAPI() noexcept = default;

bool VariableAPI::isStatic() const noexcept
{
	using EVarFlagsUnderlyingType = std::underlying_type_t<EVarFlags>;

	return static_cast<EVarFlagsUnderlyingType>(getFlags() & EVarFlags::Static) != static_cast<EVarFlagsUnderlyingType>(0);
}

void VariableAPI::set(void const* valuePtr, std::size_t valueSize) const
{
	VariableBaseAPI::set(getPtr(), valuePtr, valueSize);
}

EVarFlags VariableAPI::getFlags() const noexcept
{
	return reinterpret_cast<VariableImpl const*>(getPimpl())->getFlags();
}

void* VariableAPI::getPtr() const noexcept
{
	return reinterpret_cast<VariableImpl const*>(getPimpl())->getPtr();
}

void const* VariableAPI::getConstPtr() const noexcept
{
	return reinterpret_cast<VariableImpl const*>(getPimpl())->getConstPtr();
}