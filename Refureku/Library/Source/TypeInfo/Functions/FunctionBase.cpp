#include "Refureku/TypeInfo/Functions/FunctionBase.h"

using namespace rfk;

FunctionBase::FunctionBase(std::string&& name, std::size_t id, EEntityKind kind, Type const& returnType, std::unique_ptr<ICallable>&& internalFunction, Entity const* outerEntity) noexcept:
	Entity(std::forward<std::string>(name), id, kind, outerEntity),
	_returnType{returnType},
	_internalFunction{std::forward<std::unique_ptr<ICallable>>(internalFunction)}
{
}

bool FunctionBase::hasSamePrototype(FunctionBase const& other) const noexcept
{
	//Compare return type
	if (_returnType != other._returnType)
	{
		return false;
	}

	//Compare parameters
	if (_parameters.size() != other._parameters.size())
	{
		return false;
	}

	for (std::size_t i = 0u; i < _parameters.size(); i++)
	{
		if (_parameters[i].getType() != other._parameters[i].getType())
		{
			return false;
		}
	}

	return true;
}

FunctionBase* FunctionBase::addParameter(std::string parameterName, Type const& parameterType) noexcept
{
	_parameters.emplace_back(std::move(parameterName), parameterType);

	return this;
}

std::size_t FunctionBase::getParameterCount() const noexcept
{
	return _parameters.size();
}

FunctionParameter const& FunctionBase::getParameter(std::size_t paramIndex) const
{
	return _parameters.at(paramIndex);
}

ICallable* FunctionBase::getInternalFunction() const noexcept
{
	return _internalFunction.get();
}

void FunctionBase::setParametersCapacity(std::size_t paramCapacity) noexcept
{
	_parameters.reserve(paramCapacity);
}