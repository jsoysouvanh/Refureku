#include "TypeInfo/Methods/Exceptions/ArgTypeMismatchException.h"

using namespace rfk;

ArgTypeMismatchException::ArgTypeMismatchException(std::string const& errorMessage):
	std::logic_error(errorMessage)
{
}