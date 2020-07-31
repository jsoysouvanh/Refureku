#include "Exceptions/ArgTypeMismatch.h"

using namespace rfk;

ArgTypeMismatch::ArgTypeMismatch(std::string const& errorMessage) noexcept:
	TypeMismatch(errorMessage)
{
}