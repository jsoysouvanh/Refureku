#include "TypeInfo/Methods/MethodError.h"

using namespace rfk;

MethodError::MethodError(std::string const& what_arg):
	std::runtime_error(what_arg)
{
}