/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <string>
#include <iostream>

#include "Kodgen/Misc/Filesystem.h"

namespace kodgen
{
	class FileGenerationError
	{
		private:
			/** Name of the file in which the error occured. */
			std::string	_filename		= "";

			/** Name of the entity involved in the error. Can be left empty if no entity. */
			std::string	_entityName		= "";

			/** Description of the error. */
			std::string	_description	= "";

		public:
			FileGenerationError()							= delete;
			FileGenerationError(fs::path	filepath,
								std::string	entityName,
								std::string	description)	noexcept;
			FileGenerationError(FileGenerationError const&)	= default;
			FileGenerationError(FileGenerationError&&)	   	= default;
			~FileGenerationError()							= default;

			/**
			*	@brief Getter for _filename;
			*
			*	@return _filename.
			*/
			inline std::string const&	getFilename()		const	noexcept;

			/**
			*	@brief Getter for _entityName;
			*
			*	@return _entityName.
			*/
			inline std::string const&	getEntityName()		const	noexcept;

			/**
			*	@brief Getter for _description;
			*
			*	@return _description.
			*/
			inline std::string const&	getDescription()	const	noexcept;

			/**
			*	@return A string containing all information about this error.
			*/
			inline std::string			toString()			const	noexcept;

			FileGenerationError&	operator=(FileGenerationError const&)	= default;
			FileGenerationError&	operator=(FileGenerationError&&)		= default;
	};

	std::ostream& operator<<(std::ostream& out_stream, FileGenerationError const& fileGenerationError) noexcept;

	#include "Kodgen/CodeGen/FileGenerationError.inl"
}