#include "Refureku/TypeInfo/Functions/FunctionBaseAPI.h"

#include "Refureku/TypeInfo/Functions/FunctionBaseImpl.h"

using namespace rfk;

FunctionBaseAPI::FunctionBaseAPI(FunctionBaseImpl* implementation) noexcept:
	EntityAPI(implementation)
{
}

FunctionBaseAPI::~FunctionBaseAPI() noexcept = default;

FunctionParameterAPI& FunctionBaseAPI::addParameter(char const* name, std::size_t id, TypeAPI const& type) noexcept
{
	return reinterpret_cast<FunctionBaseImpl*>(getPimpl())->addParameter(name, id, type, this);
}

bool FunctionBaseAPI::hasSamePrototype(FunctionBaseAPI const& other) const noexcept
{
	//Compare return type
	if (getReturnType() != other.getReturnType())
	{
		return false;
	}

	//Compare parameters
	std::size_t paramsCount = getParametersCount();
	if (paramsCount != other.getParametersCount())
	{
		return false;
	}

	for (std::size_t i = 0u; i < paramsCount; i++)
	{
		if (getParameterAt(i) != other.getParameterAt(i))
		{
			return false;
		}
	}

	return true;
}

TypeAPI const& FunctionBaseAPI::getReturnType() const noexcept
{
	return reinterpret_cast<FunctionBaseImpl const*>(getPimpl())->getReturnType();
}

FunctionParameterAPI const& FunctionBaseAPI::getParameterAt(std::size_t index) const noexcept
{
	return reinterpret_cast<FunctionBaseImpl const*>(getPimpl())->getParameters()[index];
}

std::size_t FunctionBaseAPI::getParametersCount() const noexcept
{
	return reinterpret_cast<FunctionBaseImpl const*>(getPimpl())->getParameters().size();
}

void FunctionBaseAPI::setParametersCapacity(std::size_t capacity) noexcept
{
	return reinterpret_cast<FunctionBaseImpl*>(getPimpl())->setParametersCapacity(capacity);
}

ICallable* FunctionBaseAPI::getInternalFunction() const noexcept
{
	return reinterpret_cast<FunctionBaseImpl const*>(getPimpl())->getInternalFunction();
}