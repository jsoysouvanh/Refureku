#include "Exceptions/ArgCountMismatchException.h"

using namespace rfk;

ArgCountMismatchException::ArgCountMismatchException(std::string const& errorMessage) noexcept:
	std::logic_error(errorMessage)
{
}