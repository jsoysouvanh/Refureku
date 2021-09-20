#include "Refureku/TypeInfo/Functions/FunctionBase.h"

using namespace rfk;

FunctionBase::FunctionBase(std::string&& name, uint64 id, EEntityKind kind, Type const& returnType, std::unique_ptr<ICallable>&& internalMethod, Entity const* outerEntity) noexcept:
	Entity(std::forward<std::string>(name), id, kind, outerEntity),
	_returnType{returnType},
	internalMethod{std::forward<std::unique_ptr<ICallable>>(internalMethod)}
{
}

bool FunctionBase::hasSamePrototype(FunctionBase const* other) const noexcept
{
	//Compare return type
	if (_returnType != other->_returnType)
	{
		return false;
	}

	//Compare parameters
	if (parameters.size() != other->parameters.size())
	{
		return false;
	}

	for (size_t i = 0u; i < parameters.size(); i++)
	{
		if (parameters[i].type != other->parameters[i].type)
		{
			return false;
		}
	}

	return true;
}

FunctionBase* FunctionBase::addParameter(std::string parameterName, Type const& parameterType) noexcept
{
	parameters.emplace_back(std::move(parameterName), parameterType);

	return this;
}

ICallable const* FunctionBase::getInternalFunction() const noexcept
{
	return internalMethod.get();
}

Type const& FunctionBase::getReturnType() const noexcept
{
	return _returnType;
}