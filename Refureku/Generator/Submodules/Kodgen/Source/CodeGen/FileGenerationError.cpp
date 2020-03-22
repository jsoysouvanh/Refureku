#include "CodeGen/FileGenerationError.h"

using namespace kodgen;

FileGenerationError::FileGenerationError(fs::path const& filepath, std::string const& entityName, EFileGenerationError fileGenError) noexcept:
	_filename{filepath.string()},
	_entityName{entityName},
	_fileGenError{fileGenError}
{
}

std::string const& FileGenerationError::getFilename() const noexcept
{
	return _filename;
}

std::string const& FileGenerationError::getEntityName() const noexcept
{
	return _entityName;
}

EFileGenerationError FileGenerationError::getFileGenerationError() const noexcept
{
	return _fileGenError;
}

std::ostream& kodgen::operator<<(std::ostream& out_stream, FileGenerationError const& fileGenerationError) noexcept
{
	out_stream << "Error: " << kodgen::toString(fileGenerationError.getFileGenerationError()) << ", " << fileGenerationError.getFilename() << ": " << fileGenerationError.getEntityName();

	return out_stream;
}