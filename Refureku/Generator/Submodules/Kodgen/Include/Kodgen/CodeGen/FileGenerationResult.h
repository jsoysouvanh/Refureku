/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <vector>

#include "Kodgen/CodeGen/FileGenerationError.h"
#include "Kodgen/Parsing/ParsingError.h"

namespace kodgen
{
	class FileGenerationResult
	{
		public:
			/**
			*	This boolean is false if the output directory path is not defined, if the directory could not be created
			*	or if the path is valid but doesn't point to a directory (i.e. points to a file, a link...), in which case
			*	the file generation aborts immediately without performing any further operation.
			*	In any other case, the boolean will be true.
			*
			*	Even if completed is true, errors might have happened during parsing and/or file generation.
			*	Make sure to check parsingErrors and fileGenerationErrors.
			*/
			bool								completed	= false;

			/** Time elapsed to discover files to parse, parse, generate and collect results of all files. */
			float								duration	= 0.0f;

			/** List of errors which occured during files parsing. If a file has parsing error, no code is generated. */
			std::vector<ParsingError>			parsingErrors;

			/** List of errors which occured when attempting to generate code. */
			std::vector<FileGenerationError>	fileGenerationErrors;

			/** List of paths to files that have been parsed and got their metadata regenerated. */
			std::vector<fs::path>				parsedFiles;

			/** List of paths to files which metadata are up-to-date. */
			std::vector<fs::path>				upToDateFiles;

			FileGenerationResult()								= default;
			FileGenerationResult(FileGenerationResult const&)	= default;
			FileGenerationResult(FileGenerationResult&&)		= default;
			~FileGenerationResult()								= default;

			/**
			*	@brief Merge a result to this result.
			*	
			*	@param otherResult	The result to merge with this result.
			*						After the call, otherResult state is UB.
			*/
			void mergeResult(FileGenerationResult&& otherResult)		noexcept;

			/**
			*	@brief Merge a result errors to this result errors.
			*	
			*	@param otherResult	The result to merge with this result.
			*						After the call, otherResult state is UB.
			*/
			void mergeResultErrors(FileGenerationResult&& otherResult)	noexcept;

			FileGenerationResult& operator=(FileGenerationResult const&)	= default;
			FileGenerationResult& operator=(FileGenerationResult&&)			= default;
	};
}