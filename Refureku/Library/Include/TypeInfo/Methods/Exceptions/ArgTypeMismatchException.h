#pragma once

#include <stdexcept>
#include <string>

namespace rfk
{
	class ArgTypeMismatchException : public std::logic_error
	{
		public:
			explicit ArgTypeMismatchException(std::string const& errorMessage);
			ArgTypeMismatchException(ArgTypeMismatchException const&)				= default;
			ArgTypeMismatchException(ArgTypeMismatchException&&)					= default;
			~ArgTypeMismatchException()												= default;
	};
}