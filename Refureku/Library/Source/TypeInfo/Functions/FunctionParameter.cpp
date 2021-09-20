#include "Refureku/TypeInfo/Functions/FunctionParameter.h"

using namespace rfk;

FunctionParameter::FunctionParameter(std::string&& name, Type const& type) noexcept:
	_name{std::forward<std::string>(name)},
	_type{type}
{
}

std::string const& FunctionParameter::getName() const noexcept
{
	return _name;
}