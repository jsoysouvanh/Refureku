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
			std::string				_filename		= "";
			std::string				_entityName		= "";
			EFileGenerationError	_fileGenError	= EFileGenerationError::Count;

		public:
			FileGenerationError()							= delete;
			FileGenerationError(fs::path const& filepath, std::string const& entityName, EFileGenerationError fileGenError) noexcept;
			FileGenerationError(FileGenerationError const&) = default;
			FileGenerationError(FileGenerationError&&)		= default;

			std::string const&		getFilename()				const	noexcept;
			std::string const&		getEntityName()				const	noexcept;
			EFileGenerationError	getFileGenerationError()	const	noexcept;

			FileGenerationError& operator=(FileGenerationError const&)	= default;
			FileGenerationError& operator=(FileGenerationError&&)		= default;
	};

	std::ostream& operator<<(std::ostream& out_stream, FileGenerationError const& fileGenerationError) noexcept;
}