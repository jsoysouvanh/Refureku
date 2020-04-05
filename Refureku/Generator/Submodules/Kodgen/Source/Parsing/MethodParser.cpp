#include "Parsing/MethodParser.h"

#include <assert.h>

#include "Misc/Helpers.h"
#include "InfoStructures/MethodParamInfo.h"

using namespace kodgen;

CXChildVisitResult MethodParser::parse(CXCursor const& cursor) noexcept
{
	//Check for any annotation attribute if the flag is raised
	if (_shouldCheckValidity)
	{
		return setAsCurrentEntityIfValid(cursor);
	}

	if (!_parsingInfo->currentStructOrClass.has_value())
	{
		return CXChildVisitResult::CXChildVisit_Break;
	}

	switch (clang_getCursorKind(cursor))
	{
		case CXCursorKind::CXCursor_CXXFinalAttr:
			_parsingInfo->currentStructOrClass->methods.back().qualifiers.isFinal = true;
			break;

		case CXCursorKind::CXCursor_CXXOverrideAttr:
			_parsingInfo->currentStructOrClass->methods.back().qualifiers.isOverride = true;
			break;

		case CXCursorKind::CXCursor_ParmDecl:
			_parsingInfo->currentStructOrClass->methods.back().parameters.emplace_back(MethodParamInfo{ TypeInfo(clang_getCursorType(cursor)), Helpers::getString(clang_getCursorDisplayName(cursor)) });
			break;

		default:
			std::cout << "Unknown method sub cursor: " << Helpers::getString(clang_getCursorKindSpelling(clang_getCursorKind(cursor))) << std::endl;
			break;
	}

	return CXChildVisitResult::CXChildVisit_Recurse;
}

CXChildVisitResult MethodParser::setAsCurrentEntityIfValid(CXCursor const& methodAnnotationCursor) noexcept
{
	if (opt::optional<PropertyGroup> propertyGroup = isEntityValid(methodAnnotationCursor))
	{
		if (_parsingInfo->currentStructOrClass.has_value())
		{

			MethodInfo& methodInfo = _parsingInfo->currentStructOrClass->methods.emplace_back(MethodInfo(getCurrentCursor(), std::move(*propertyGroup)));
			setupMethod(getCurrentCursor(), methodInfo);

			return CXChildVisitResult::CXChildVisit_Recurse;
		}
	}
	else if (_parsingInfo->propertyParser.getParsingError() != EParsingError::Count)
	{
		//Fatal parsing error occured
		_parsingInfo->parsingResult.parsingErrors.emplace_back(ParsingError(_parsingInfo->propertyParser.getParsingError(), clang_getCursorLocation(methodAnnotationCursor)));
	}

	return CXChildVisitResult::CXChildVisit_Break;
}

void MethodParser::setupMethod(CXCursor const& methodCursor, MethodInfo& methodInfo) noexcept
{
	CXType methodType = clang_getCursorType(methodCursor);

	assert(methodType.kind == CXTypeKind::CXType_FunctionProto);

	//Method access specifier
	methodInfo.accessSpecifier = _parsingInfo->accessSpecifier;

	//Define prototype
	methodInfo.prototype = Helpers::getString(clang_getTypeSpelling(methodType));

	//Define return type
	methodInfo.returnType =	TypeInfo(clang_getResultType(methodType));

	//Define method qualifiers
	if (clang_CXXMethod_isDefaulted(methodCursor))
	{
		methodInfo.qualifiers.isDefault = true;
	}
	if (clang_CXXMethod_isStatic(methodCursor))
	{
		methodInfo.qualifiers.isStatic = true;
	}
	if (clang_CXXMethod_isVirtual(methodCursor))
	{
		methodInfo.qualifiers.isVirtual = true;
	}
	if (clang_CXXMethod_isPureVirtual(methodCursor))
	{
		methodInfo.qualifiers.isPureVirtual = true;
	}
	if (clang_CXXMethod_isConst(methodCursor))
	{
		methodInfo.qualifiers.isConst = true;
	}
	if (clang_Cursor_isFunctionInlined(methodCursor))
	{
		methodInfo.qualifiers.isInline = true;
	}
}

opt::optional<PropertyGroup> MethodParser::isEntityValid(CXCursor const& currentCursor) noexcept
{
	_shouldCheckValidity = false;
	_parsingInfo->propertyParser.clean();

	if (clang_getCursorKind(currentCursor) == CXCursorKind::CXCursor_AnnotateAttr)
	{
		return _parsingInfo->propertyParser.getMethodProperties(Helpers::getString(clang_getCursorSpelling(currentCursor)));
	}

	return opt::nullopt;
}