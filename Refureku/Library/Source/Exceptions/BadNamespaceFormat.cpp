#include "Refureku/Exceptions/BadNamespaceFormat.h"

using namespace rfk;

BadNamespaceFormat::BadNamespaceFormat(std::string const& errorMessage) noexcept:
	std::invalid_argument(errorMessage)
{
}