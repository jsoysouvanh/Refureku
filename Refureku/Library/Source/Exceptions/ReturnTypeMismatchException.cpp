#include "Exceptions/ReturnTypeMismatchException.h"

using namespace rfk;

ReturnTypeMismatchException::ReturnTypeMismatchException(std::string const& errorMessage) noexcept:
	std::logic_error(errorMessage)
{
}