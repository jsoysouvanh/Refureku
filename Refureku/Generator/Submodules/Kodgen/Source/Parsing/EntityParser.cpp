#include "Parsing/EntityParser.h"

using namespace kodgen;

void EntityParser::startParsing(CXCursor const& currentCursor) noexcept
{
	_parsingLevel++;
	_currentCursor			= currentCursor;
	_shouldCheckValidity	= true;
}

void EntityParser::endParsing(ParsingInfo& parsingInfo) noexcept
{
	//Fake use to remove warning
	static_cast<void>(parsingInfo);

	_parsingLevel--;
	_currentCursor			= clang_getNullCursor();
	_shouldCheckValidity	= false;
}

void EntityParser::reset() noexcept
{
	_parsingLevel			= 0u;
	_currentCursor			= clang_getNullCursor();
	_shouldCheckValidity	= false;
}

CXCursor const& EntityParser::getCurrentCursor() const noexcept
{
	return _currentCursor;
}

uint8 EntityParser::getParsingLevel() const noexcept
{
	return _parsingLevel;
}