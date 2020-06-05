#pragma once

#include <exception>
#include <string>

namespace rfk
{
	class ReturnTypeMismatchException : public std::exception
	{
		public:
		explicit ReturnTypeMismatchException(std::string const& errorMessage);
		ReturnTypeMismatchException(ReturnTypeMismatchException const&)			= default;
		ReturnTypeMismatchException(ReturnTypeMismatchException&&)				= default;
		~ReturnTypeMismatchException()											= default;
	};
}