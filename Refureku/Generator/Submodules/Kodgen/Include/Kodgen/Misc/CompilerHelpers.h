/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <vector>
#include <string>
#include <array>
#include <string_view>

#include "Kodgen/Misc/Filesystem.h"

namespace kodgen
{
	class CompilerHelpers
	{
		private:
			/** All supported compiler names (a version can also be appended) checked internally */
			static constexpr std::string_view msvcCompilerName	= "msvc";
			static constexpr std::string_view clangCompilerName	= "clang";
			static constexpr std::string_view gccCompilerName	= "gcc";
			static constexpr std::string_view gccCompilerName2	= "g++";

			/**
			*	@brief Retrieve all clang native include directories on the executing computer.
			*
			*	@param clangExeName Clang executable name (version might be specified in there).
			*	
			*	@return A vector containing all clang native include directories.
			*
			*	@exception std::runtime_error is thrown if the clang executable could not be launched.
			*/
			static std::vector<fs::path> getClangNativeIncludeDirectories(std::string const& clangExeName);

			/**
			*	@brief Retrieve all GCC native include directories on the executing computer.
			*
			*	@param gccExeName GCC executable name (version might be specified in there).
			*	
			*	@return A vector containing all GCC native include directories.
			*
			*	@exception std::runtime_error is thrown if the gcc executable could not be launched.
			*/
			static std::vector<fs::path> getGCCNativeIncludeDirectories(std::string const& gccExeName);

#if _WIN32
			/**
			*	@brief Retrieve all MSVC native include directories on the executing computer.
			*
			*	@return A vector containing all MSVC native include directories.
			*
			*	@exception std::runtime_error is thrown if vswhere could not be located.
			*/
			static std::vector<fs::path> getMSVCNativeIncludeDirectories();

			/**
			*	@brief Retrieve the path of the vswhere executable, which should be at the same level as the executable.
			*
			*	@return The vswhere.exe path, if found next to the executable, else an empty path.
			*/
			static fs::path					getvswherePath()	noexcept;
#endif

		public:
			CompilerHelpers()						= delete;
			CompilerHelpers(CompilerHelpers const&)	= delete;
			CompilerHelpers(CompilerHelpers&&)		= delete;
			~CompilerHelpers()						= delete;

			/**
			*	@brief Retrieve all native include directories of a given compiler on the executing computer.
			*
			*	@param compiler Compiler we are looking the include directories of.
			*	
			*	@return A vector containing all native include directories for the provided compiler.
			*
			*	@exception std::runtime_error is thrown if the compiler has a valid name but include directories could not be queried on the executing computer.
			*/
			static std::vector<fs::path> getCompilerNativeIncludeDirectories(std::string compiler);
	};
}