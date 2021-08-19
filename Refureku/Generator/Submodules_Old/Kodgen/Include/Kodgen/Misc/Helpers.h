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

			/**
			*	@brief Convert a clang string to a std::string.
			*	
			*	@param clangString The clang string.
			*	
			*	@return The converted string.
			*/
			static std::string			getString(CXString&& clangString)		noexcept;

			/**
			*	@brief Get debug info about the provided cursor as string.
			*	
			*	@param cursor The cursor to debug.
			*	
			*	@return A string containing debug info.
			*/
			static std::string			getDebugInfo(CXCursor const& cursor)	noexcept;

			/**
			*	@brief Convert a boolean to a string value.
			*	
			*	@param value The boolean to convert.
			*	
			*	@return "true" if the boolean is true, else "false".
			*/
			static inline std::string	toString(bool value)					noexcept;
	};

	#include "Kodgen/Misc/Helpers.inl"
}