#include "Parsing/EntityParser.h"

using namespace kodgen;

void EntityParser::startParsing(CXCursor const& currentCursor) noexcept
{
	_parsingLevel++;
	_currentCursor			= currentCursor;
	_shouldCheckValidity	= true;
}

CXChildVisitResult EntityParser::endParsing() noexcept
{
	_parsingLevel--;
	_currentCursor			= clang_getNullCursor();
	_shouldCheckValidity	= false;

	return (_parsingInfo->parsingSettings.shouldAbortParsingOnFirstError && _parsingInfo->hasErrorOccured()) ? CXChildVisitResult::CXChildVisit_Break : CXChildVisitResult::CXChildVisit_Continue;
}

void EntityParser::reset() noexcept
{
	_parsingLevel			= 0u;
	_currentCursor			= clang_getNullCursor();
	_shouldCheckValidity	= false;
}

void EntityParser::setParsingInfo(ParsingInfo* info) noexcept
{
	_parsingInfo = info;
}

CXCursor const& EntityParser::getCurrentCursor() const noexcept
{
	return _currentCursor;
}

uint8 EntityParser::getParsingLevel() const noexcept
{
	return _parsingLevel;
}