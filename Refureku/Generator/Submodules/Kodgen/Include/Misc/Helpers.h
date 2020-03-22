#pragma once

#include <clang-c/Index.h>
#include <string>

namespace kodgen
{
	class Helpers
	{
		public:
			Helpers()				= delete;
			Helpers(Helpers const&) = delete;
			Helpers(Helpers&&)		= delete;
			~Helpers()				= delete;

			static std::string getString(CXString&& clangString) noexcept;
	};
}