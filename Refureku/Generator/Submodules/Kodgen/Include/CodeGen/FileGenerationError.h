/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <string>
#include <iostream>

#include "Misc/Filesystem.h"
#include "CodeGen/EFileGenerationError.h"

namespace kodgen
{
	class FileGenerationError
	{
		private:
			/** Name of the file in which the error occured. */
			std::string				_filename		= "";

			/** Name of the entity involved in the error. Can be left empty if no entity. */
			std::string				_entityName		= "";

			/** Type of error which happened. */
			EFileGenerationError	_fileGenError	= EFileGenerationError::Count;

		public:
			FileGenerationError()										= delete;
			FileGenerationError(fs::path const&			filepath,
								std::string const&		entityName,
								EFileGenerationError	fileGenError)	noexcept;
			FileGenerationError(FileGenerationError const&)				= default;
			FileGenerationError(FileGenerationError&&)					= default;

			/**
			*	@return The name of the file in which the error occured.
			*/
			std::string const&		getFilename()				const	noexcept;

			/**
			*	@return The name of the entity involved in the error.
			*/
			std::string const&		getEntityName()				const	noexcept;

			/**
			*	@return The type of error.
			*/
			EFileGenerationError	getFileGenerationError()	const	noexcept;

			/**
			*	@return A string containing all information about this error.
			*/
			std::string				toString()					const	noexcept;

			FileGenerationError& operator=(FileGenerationError const&)	= default;
			FileGenerationError& operator=(FileGenerationError&&)		= default;
	};

	std::ostream& operator<<(std::ostream& out_stream, FileGenerationError const& fileGenerationError) noexcept;
}