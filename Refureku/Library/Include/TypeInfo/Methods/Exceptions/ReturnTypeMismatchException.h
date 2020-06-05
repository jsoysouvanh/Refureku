#pragma once

#include <stdexcept>
#include <string>

namespace rfk
{
	class ReturnTypeMismatchException : public std::logic_error
	{
		public:
		explicit ReturnTypeMismatchException(std::string const& errorMessage);
		ReturnTypeMismatchException(ReturnTypeMismatchException const&)			= default;
		ReturnTypeMismatchException(ReturnTypeMismatchException&&)				= default;
		~ReturnTypeMismatchException()											= default;
	};
}