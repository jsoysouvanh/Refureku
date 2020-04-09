#include "Parsing/EnumParser.h"

#include <cassert>

#include "Misc/Helpers.h"

using namespace kodgen;

void EnumParser::reset() noexcept
{
	EntityParser::reset();

	_enumValueParser.reset();
}

void EnumParser::setParsingInfo(ParsingInfo* info) noexcept
{
	EntityParser::setParsingInfo(info);

	_enumValueParser.setParsingInfo(info);
}

CXChildVisitResult EnumParser::parse(CXCursor const& currentCursor) noexcept
{
	if (_shouldCheckValidity)	//Check for any annotation if the flag is raised
	{
		_shouldCheckValidity = false;

		return setAsCurrentEntityIfValid(currentCursor);
	}

	switch (currentCursor.kind)
	{
		case CXCursorKind::CXCursor_EnumConstantDecl:
			return parseEnumValue(currentCursor);

		default:
			break;
	}

	return CXChildVisitResult::CXChildVisit_Continue;
}

CXChildVisitResult EnumParser::parseEnumValue(CXCursor enumValueCursor) noexcept
{
	assert(enumValueCursor.kind == CXCursorKind::CXCursor_EnumConstantDecl);

	_enumValueParser.startParsing(enumValueCursor);

	//Always add an enum value, eventhough is doesn't have the macro
	_parsingInfo->currentEnum->enumValues.emplace_back(EnumValueInfo(enumValueCursor));

	clang_visitChildren(enumValueCursor, [](CXCursor c, CXCursor, CXClientData clientData)
						{
							return reinterpret_cast<EnumValueParser*>(clientData)->parse(c);

						}, &_enumValueParser);

	return _enumValueParser.endParsing();
}

CXChildVisitResult EnumParser::endParsing() noexcept
{
	_parsingInfo->flushCurrentEnum();

	return EntityParser::endParsing();
}

opt::optional<PropertyGroup> EnumParser::isEntityValid(CXCursor const& currentCursor) noexcept
{
	_parsingInfo->propertyParser.clean();

	if (clang_getCursorKind(currentCursor) == CXCursorKind::CXCursor_AnnotateAttr)
	{
		return _parsingInfo->propertyParser.getEnumProperties(Helpers::getString(clang_getCursorSpelling(currentCursor)));
	}

	return opt::nullopt;
}

CXChildVisitResult EnumParser::setAsCurrentEntityIfValid(CXCursor const& classAnnotationCursor) noexcept
{
	if (opt::optional<PropertyGroup> propertyGroup = isEntityValid(classAnnotationCursor))
	{
		EnumInfo& enumInfo = _parsingInfo->currentEnum.emplace(EnumInfo(getCurrentCursor(), std::move(*propertyGroup)));

		enumInfo.type			= clang_getCursorType(getCurrentCursor());
		enumInfo.underlyingType	= clang_getEnumDeclIntegerType(getCurrentCursor());

		return CXChildVisitResult::CXChildVisit_Recurse;
	}
	else
	{
		if (_parsingInfo->propertyParser.getParsingError() != EParsingError::Count)
		{
			//Fatal parsing error occured
			_parsingInfo->parsingResult.parsingErrors.emplace_back(ParsingError(_parsingInfo->propertyParser.getParsingError(), clang_getCursorLocation(classAnnotationCursor)));
		}

		return CXChildVisitResult::CXChildVisit_Break;
	}
}