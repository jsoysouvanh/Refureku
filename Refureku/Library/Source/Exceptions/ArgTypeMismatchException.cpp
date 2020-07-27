#include "Exceptions/ArgTypeMismatchException.h"

using namespace rfk;

ArgTypeMismatchException::ArgTypeMismatchException(std::string const& errorMessage) noexcept:
	std::logic_error(errorMessage)
{
}