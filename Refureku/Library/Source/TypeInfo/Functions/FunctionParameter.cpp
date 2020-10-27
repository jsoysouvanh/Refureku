#include "Refureku/TypeInfo/Functions/FunctionParameter.h"

using namespace rfk;

FunctionParameter::FunctionParameter(std::string&& name, Type const& type) noexcept:
	name{std::forward<std::string>(name)},
	type{type}
{
}