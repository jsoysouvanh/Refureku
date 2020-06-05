#include "TypeInfo/Methods/Exceptions/ReturnTypeMismatchException.h"

using namespace rfk;

ReturnTypeMismatchException::ReturnTypeMismatchException(std::string const& errorMessage):
	std::exception(errorMessage.c_str())
{
}