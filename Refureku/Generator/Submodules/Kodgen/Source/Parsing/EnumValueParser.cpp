#include "Parsing/EnumValueParser.h"

#include "Misc/Helpers.h"

using namespace kodgen;

CXChildVisitResult EnumValueParser::parse(CXCursor const& currentCursor) noexcept
{
	if (_shouldCheckValidity)
	{
		_shouldCheckValidity = false;

		switch (clang_getCursorKind(currentCursor))
		{
			case CXCursorKind::CXCursor_AnnotateAttr:
				return setAsCurrentEntityIfValid(currentCursor);

			default:
				return CXChildVisitResult::CXChildVisit_Break;
		}
	}

	return CXChildVisitResult::CXChildVisit_Break;
}

opt::optional<PropertyGroup> EnumValueParser::isEntityValid(CXCursor const& currentCursor) noexcept
{
	_parsingInfo->propertyParser.clean();

	if (clang_getCursorKind(currentCursor) == CXCursorKind::CXCursor_AnnotateAttr)
	{
		return _parsingInfo->propertyParser.getEnumValueProperties(Helpers::getString(clang_getCursorSpelling(currentCursor)));
	}

	return opt::nullopt;
}

CXChildVisitResult EnumValueParser::setAsCurrentEntityIfValid(CXCursor const& annotationCursor) noexcept
{
	if (opt::optional<PropertyGroup> propertyGroup = isEntityValid(annotationCursor))
	{
		if (_parsingInfo->currentEnum.has_value())
		{
			_parsingInfo->currentEnum->enumValues.back().properties = std::move(*propertyGroup);
		}
	}
	else if (_parsingInfo->propertyParser.getParsingError() != EParsingError::Count)
	{
		//Fatal parsing error occured
		_parsingInfo->parsingResult.parsingErrors.emplace_back(ParsingError(_parsingInfo->propertyParser.getParsingError(), clang_getCursorLocation(annotationCursor)));
	}

	return CXChildVisitResult::CXChildVisit_Break;
}