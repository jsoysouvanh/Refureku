#include "Kodgen/CodeGen/FileGenerationError.h"

#include <utility>	//std::move

using namespace kodgen;

FileGenerationError::FileGenerationError(fs::path filepath, std::string entityName, std::string description) noexcept:
	_filename{filepath.string()},
	_entityName{std::move(entityName)},
	_description{std::move(description)}
{
}

std::ostream& kodgen::operator<<(std::ostream& out_stream, FileGenerationError const& fileGenerationError) noexcept
{
	out_stream << fileGenerationError.toString();

	return out_stream;
}