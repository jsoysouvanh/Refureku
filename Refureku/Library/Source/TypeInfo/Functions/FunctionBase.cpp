#include "Refureku/TypeInfo/Functions/FunctionBase.h"

#include <string>	//std::to_string

#include "Refureku/TypeInfo/Functions/FunctionBaseImpl.h"
#include "Refureku/Exceptions/ArgCountMismatch.h"
#include "Refureku/Exceptions/ReturnTypeMismatch.h"
#include "Refureku/Exceptions/ArgTypeMismatch.h"

using namespace rfk;

FunctionBase::FunctionBase(FunctionBaseImpl* implementation) noexcept:
	Entity(implementation)
{
}

FunctionBase::FunctionBase(FunctionBase&&) noexcept = default;

FunctionBase::~FunctionBase() noexcept = default;

FunctionParameter& FunctionBase::addParameter(char const* name, std::size_t id, Type const& type) noexcept
{
	return getPimpl()->addParameter(name, id, type, this);
}

bool FunctionBase::hasSamePrototype(FunctionBase const& other) const noexcept
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

Type const& FunctionBase::getReturnType() const noexcept
{
	return getPimpl()->getReturnType();
}

FunctionParameter const& FunctionBase::getParameterAt(std::size_t index) const noexcept
{
	return getPimpl()->getParameters()[index];
}

std::size_t FunctionBase::getParametersCount() const noexcept
{
	return getPimpl()->getParameters().size();
}

void FunctionBase::setParametersCapacity(std::size_t capacity) noexcept
{
	return getPimpl()->setParametersCapacity(capacity);
}

ICallable* FunctionBase::getInternalFunction() const noexcept
{
	return getPimpl()->getInternalFunction();
}

void FunctionBase::throwArgCountMismatchException(std::size_t received) const
{
	throw ArgCountMismatch("Tried to call " + std::string(getName()) + " with " + std::to_string(received) + " arguments but " + std::to_string(getParametersCount()) + " were expected.");
}

void FunctionBase::throwArgTypeMismatchException(std::size_t paramIndex) const
{
	throw ArgTypeMismatch("Tried to call " + std::string(getName()) + " but argument " + std::to_string(paramIndex) + " (" + getParameterAt(paramIndex).getName() + ") type doesn't match.");
}

void FunctionBase::throwReturnTypeMismatchException() const
{
	throw ReturnTypeMismatch("Tried to call " + std::string(getName()) + " but the specified return type is incorrect.");
}