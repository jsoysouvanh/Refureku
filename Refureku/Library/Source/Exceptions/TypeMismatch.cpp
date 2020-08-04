#include "Refureku/Exceptions/TypeMismatch.h"

using namespace rfk;

TypeMismatch::TypeMismatch(std::string const& errorMessage) noexcept:
	std::logic_error(errorMessage)
{
}