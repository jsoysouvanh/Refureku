#include "Exceptions/OutOfRange.h"

using namespace rfk;

OutOfRange::OutOfRange(std::string const& errorMessage) noexcept:
	std::out_of_range(errorMessage)
{
}