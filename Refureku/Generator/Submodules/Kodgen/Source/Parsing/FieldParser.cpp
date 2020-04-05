#include "Parsing/FieldParser.h"

#include <cassert>

#include "Misc/Helpers.h"

using namespace kodgen;

CXChildVisitResult FieldParser::parse(CXCursor const& cursor) noexcept
{
	//Check for any annotation attribute if the flag is raised
	if (_shouldCheckValidity)
	{
		return setAsCurrentEntityIfValid(cursor);
	}

	return CXChildVisitResult::CXChildVisit_Break;
}

CXChildVisitResult FieldParser::setAsCurrentEntityIfValid(CXCursor const& fieldAnnotationCursor) noexcept
{
	if (opt::optional<PropertyGroup> propertyGroup = isEntityValid(fieldAnnotationCursor))
	{
		if (_parsingInfo->currentStructOrClass.has_value())
		{
			FieldInfo& field = _parsingInfo->currentStructOrClass->fields.emplace_back(FieldInfo(getCurrentCursor(), std::move(*propertyGroup)));
			
			field.accessSpecifier = _parsingInfo->accessSpecifier;
			field.type = TypeInfo(clang_getCursorType(getCurrentCursor()));
			field.qualifiers.isStatic = (clang_getCursorKind(getCurrentCursor()) == CXCursorKind::CXCursor_VarDecl);

			if (!field.qualifiers.isStatic)
			{
				field.qualifiers.isMutable = clang_CXXField_isMutable(getCurrentCursor());

				field.memoryOffset = clang_Cursor_getOffsetOfField(getCurrentCursor());

				// assert(field.memoryOffset != CXTypeLayoutError::CXTypeLayoutError_Invalid);	<- Assert here on travis for some reasons...
				assert(field.memoryOffset != CXTypeLayoutError::CXTypeLayoutError_Incomplete);
				assert(field.memoryOffset != CXTypeLayoutError::CXTypeLayoutError_Dependent);
				assert(field.memoryOffset != CXTypeLayoutError::CXTypeLayoutError_InvalidFieldName);

				field.memoryOffset /= 8;	//From bits to bytes
			}
		}
	}
	else if (_parsingInfo->propertyParser.getParsingError() != EParsingError::Count)
	{
		//Fatal parsing error occured
		_parsingInfo->parsingResult.parsingErrors.emplace_back(ParsingError(_parsingInfo->propertyParser.getParsingError(), clang_getCursorLocation(fieldAnnotationCursor)));
	}

	return CXChildVisitResult::CXChildVisit_Break;
}

opt::optional<PropertyGroup> FieldParser::isEntityValid(CXCursor const& currentCursor) noexcept
{
	_shouldCheckValidity = false;
	_parsingInfo->propertyParser.clean();

	if (clang_getCursorKind(currentCursor) == CXCursorKind::CXCursor_AnnotateAttr)
	{
		return _parsingInfo->propertyParser.getFieldProperties(Helpers::getString(clang_getCursorSpelling(currentCursor)));
	}

	return opt::nullopt;
}