#include "TypeInfo/Methods/MethodParameter.h"

using namespace rfk;

MethodParameter::MethodParameter(std::string&& name, Type&& type) noexcept:
	name{std::forward<std::string>(name)},
	type{std::forward<Type>(type)}
{
}