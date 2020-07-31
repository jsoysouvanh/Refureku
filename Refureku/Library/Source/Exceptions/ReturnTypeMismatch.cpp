#include "Exceptions/ReturnTypeMismatch.h"

using namespace rfk;

ReturnTypeMismatch::ReturnTypeMismatch(std::string const& errorMessage) noexcept:
	TypeMismatch(errorMessage)
{
}