#pragma once

#include <exception>
#include <string>

namespace rfk
{
	class ArgTypeMismatchException : public std::exception
	{
		public:
			explicit ArgTypeMismatchException(std::string const& errorMessage);
			ArgTypeMismatchException(ArgTypeMismatchException const&)				= default;
			ArgTypeMismatchException(ArgTypeMismatchException&&)					= default;
			~ArgTypeMismatchException()												= default;
	};
}