#include "Refureku/Exceptions/ArgCountMismatch.h"

using namespace rfk;

ArgCountMismatch::ArgCountMismatch(std::string const& errorMessage) noexcept:
	std::logic_error(errorMessage)
{
}