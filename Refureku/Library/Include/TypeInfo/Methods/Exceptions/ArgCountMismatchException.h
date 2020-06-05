#pragma once

#include <exception>
#include <string>

namespace rfk
{
	class ArgCountMismatchException : public std::exception
	{
		public:
			explicit ArgCountMismatchException(std::string const& errorMessage);
			ArgCountMismatchException(ArgCountMismatchException const&)				= default;
			ArgCountMismatchException(ArgCountMismatchException&&)					= default;
			~ArgCountMismatchException()											= default;
	};
}