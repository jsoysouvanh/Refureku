#include "Exceptions/BadNamespaceFormat.h"

using namespace rfk;

BadNamespaceFormat::BadNamespaceFormat(std::string const& errorMessage) noexcept:
	std::logic_error(errorMessage)
{
}