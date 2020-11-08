#include "Refureku/TypeInfo/Functions/FunctionBase.h"

using namespace rfk;

FunctionBase::FunctionBase(std::string&& name, uint64 id, EEntityKind kind, Type const& returnType, std::unique_ptr<ICallable>&& internalMethod) noexcept:
	Entity(std::forward<std::string>(name), id, kind),
	internalMethod{std::forward<std::unique_ptr<ICallable>>(internalMethod)},
	returnType{returnType}
{
}

bool FunctionBase::hasSamePrototype(FunctionBase const* other) const noexcept
{
	//Compare return type
	if (returnType != other->returnType)
	{
		return false;
	}

	//Compare parameters
	if (parameters.size() != other->parameters.size())
	{
		return false;
	}

	for (int i = 0; i < parameters.size(); i++)
	{
		if (parameters[i].type != other->parameters[i].type)
		{
			return false;
		}
	}

	return true;
}