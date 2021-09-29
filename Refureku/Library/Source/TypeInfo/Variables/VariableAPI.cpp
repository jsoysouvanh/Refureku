#include "Refureku/TypeInfo/Variables/VariableAPI.h"

#include <cstring>	//std::memcpy

#include "Refureku/TypeInfo/Variables/VariableImpl.h"

using namespace rfk;

bool VariableAPI::isStatic() const noexcept
{
	using EVarFlagsUnderlyingType = std::underlying_type_t<EVarFlags>;

	return static_cast<EVarFlagsUnderlyingType>(getFlags() & EVarFlags::Static) != static_cast<EVarFlagsUnderlyingType>(0);
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

void VariableAPI::set(void const* data, std::size_t dataSize) const
{
	if (getType().isConst())
	{
		throw ConstViolation("Can't use Variable::set on a const variable.");
	}

	std::memcpy(getPtr(), data, dataSize);
}