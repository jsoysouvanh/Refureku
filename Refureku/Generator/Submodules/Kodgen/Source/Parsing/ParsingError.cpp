#include "Parsing/ParsingError.h"

#include "Misc/Helpers.h"

using namespace kodgen;

ParsingError::ParsingError(EParsingError parsingError, CXSourceLocation errorSourceLocation) noexcept:
	_line{0},
	_column{0},
	_filename{""},
	_propertyParsingError{parsingError}
{
	if (!clang_equalLocations(errorSourceLocation, clang_getNullLocation()))
	{
		CXFile file;

		clang_getExpansionLocation(errorSourceLocation, &file, &_line, &_column, nullptr);

		_filename = Helpers::getString(clang_getFileName(file));
	}
}

std::string const& ParsingError::getFilename() const noexcept
{
	return _filename;
}

unsigned ParsingError::getLine() const noexcept
{
	return _line;
}

unsigned ParsingError::getColumn() const noexcept
{
	return _column;
}

EParsingError ParsingError::getErrorValue() const noexcept
{
	return _propertyParsingError;
}

std::string ParsingError::toString() const noexcept
{
	return kodgen::toString(getErrorValue()) + ", " + getFilename() + ": " + std::to_string(getLine()) + ":" + std::to_string(getColumn());
}

std::ostream& kodgen::operator<<(std::ostream& out_stream, ParsingError const& parsingError) noexcept
{
	out_stream << parsingError.toString();

	return out_stream;
}