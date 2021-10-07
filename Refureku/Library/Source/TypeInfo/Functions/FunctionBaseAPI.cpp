#include "Refureku/TypeInfo/Functions/FunctionBaseAPI.h"

#include <string>	//std::to_string

#include "Refureku/TypeInfo/Functions/FunctionBaseImpl.h"
#include "Refureku/Exceptions/ArgCountMismatch.h"
#include "Refureku/Exceptions/ReturnTypeMismatch.h"
#include "Refureku/Exceptions/ArgTypeMismatch.h"

using namespace rfk;

FunctionBaseAPI::FunctionBaseAPI(FunctionBaseImpl* implementation) noexcept:
	Entity(implementation)
{
}

FunctionBaseAPI::FunctionBaseAPI(FunctionBaseAPI&&) noexcept = default;

FunctionBaseAPI::~FunctionBaseAPI() noexcept = default;

FunctionParameterAPI& FunctionBaseAPI::addParameter(char const* name, std::size_t id, Type const& type) noexcept
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

Type const& FunctionBaseAPI::getReturnType() const noexcept
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

void FunctionBaseAPI::throwArgCountMismatchException(std::size_t received) const
{
	throw ArgCountMismatch("Tried to call " + std::string(getName()) + " with " + std::to_string(received) + " arguments but " + std::to_string(getParametersCount()) + " were expected.");
}

void FunctionBaseAPI::throwArgTypeMismatchException(std::size_t paramIndex) const
{
	throw ArgTypeMismatch("Tried to call " + std::string(getName()) + " but argument " + std::to_string(paramIndex) + " (" + getParameterAt(paramIndex).getName() + ") type doesn't match.");
}

void FunctionBaseAPI::throwReturnTypeMismatchException() const
{
	throw ReturnTypeMismatch("Tried to call " + std::string(getName()) + " but the specified return type is incorrect.");
}