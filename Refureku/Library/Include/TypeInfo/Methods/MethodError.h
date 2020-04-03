#pragma once

#include <stdexcept>

namespace rfk
{
	class MethodError : public std::runtime_error
	{
		public:
			explicit MethodError(std::string const& what_arg);
			MethodError(MethodError const&)						= default;
			MethodError(MethodError&&)							= default;
			~MethodError()										= default;
	};
}