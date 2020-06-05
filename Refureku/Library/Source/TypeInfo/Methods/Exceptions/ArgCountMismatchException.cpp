#include "TypeInfo/Methods/Exceptions/ArgCountMismatchException.h"

using namespace rfk;

ArgCountMismatchException::ArgCountMismatchException(std::string const& errorMessage):
	std::logic_error(errorMessage)
{
}