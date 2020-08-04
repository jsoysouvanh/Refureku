/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <string>

#include <clang-c/Index.h>

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