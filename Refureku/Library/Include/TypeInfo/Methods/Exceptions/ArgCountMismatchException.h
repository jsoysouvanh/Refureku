#pragma once

#include <stdexcept>
#include <string>

namespace rfk
{
	class ArgCountMismatchException : public std::logic_error
	{
		public:
			explicit ArgCountMismatchException(std::string const& errorMessage);
			ArgCountMismatchException(ArgCountMismatchException const&)				= default;
			ArgCountMismatchException(ArgCountMismatchException&&)					= default;
			~ArgCountMismatchException()											= default;
	};
}