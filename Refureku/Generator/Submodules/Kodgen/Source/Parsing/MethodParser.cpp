#include "Parsing/MethodParser.h"

#include <assert.h>

#include "Parsing/ParsingSettings.h"
#include "Parsing/PropertyParser.h"
#include "InfoStructures/MethodParamInfo.h"
#include "Misc/Helpers.h"
#include "Misc/DisableWarningMacros.h"

using namespace kodgen;

CXChildVisitResult MethodParser::parse(CXCursor const& methodCursor, ParsingContext const&	parentContext, MethodParsingResult& out_result) noexcept
{
	//Make sure the cursor is compatible for the method parser
	assert(methodCursor.kind == CXCursorKind::CXCursor_CXXMethod);	// /!\ might have to add CXCursor_FunctionDecl and CXCursor_FunctionTemplate

	//Init context
	pushContext(methodCursor, parentContext, out_result);

	clang_visitChildren(methodCursor, &MethodParser::parseNestedEntity, this);

	popContext();

	DISABLE_WARNING_PUSH
	DISABLE_WARNING_UNSCOPED_ENUM

	return (parentContext.parsingSettings->shouldAbortParsingOnFirstError && !out_result.errors.empty()) ? CXChildVisitResult::CXChildVisit_Break : CXChildVisitResult::CXChildVisit_Continue;

	DISABLE_WARNING_POP
}

CXChildVisitResult MethodParser::parseNestedEntity(CXCursor cursor, CXCursor /* parentCursor */, CXClientData clientData) noexcept
{
	MethodParser*	parser	= reinterpret_cast<MethodParser*>(clientData);
	ParsingContext&	context = parser->getContext();

	if (context.shouldCheckProperties)
	{
		context.shouldCheckProperties = false;

		//Set parsed method in result if it is valid
		return parser->setParsedEntity(cursor);
	}
	else
	{
		switch (clang_getCursorKind(cursor))
		{
			case CXCursorKind::CXCursor_CXXFinalAttr:
				if (parser->getParsingResult()->parsedMethod.has_value())
				{
					parser->getParsingResult()->parsedMethod->qualifiers.isFinal = true;
				}
				break;

			case CXCursorKind::CXCursor_CXXOverrideAttr:
				if (parser->getParsingResult()->parsedMethod.has_value())
				{
					parser->getParsingResult()->parsedMethod->qualifiers.isOverride = true;
				}
				break;

			case CXCursorKind::CXCursor_ParmDecl:
				if (parser->getParsingResult()->parsedMethod.has_value())
				{
					parser->getParsingResult()->parsedMethod->parameters.emplace_back(MethodParamInfo{TypeInfo(clang_getCursorType(cursor)), Helpers::getString(clang_getCursorDisplayName(cursor))});
				}
				break;

			default:
				//std::cout << "Unknown method sub cursor: " << Helpers::getString(clang_getCursorKindSpelling(clang_getCursorKind(cursor))) << std::endl;
				break;
		}

		return CXChildVisitResult::CXChildVisit_Recurse;
	}
}

CXChildVisitResult MethodParser::setParsedEntity(CXCursor const& annotationCursor) noexcept
{
	MethodParsingResult*	result	= getParsingResult();
	ParsingContext&			context	= getContext();

	if (opt::optional<PropertyGroup> propertyGroup = getProperties(annotationCursor))
	{
		//Set the parsed entity in the result & initialize its information from the method cursor
		initializeMethodInfo(result->parsedMethod.emplace(MethodInfo(context.rootCursor, std::move(*propertyGroup))));

		return CXChildVisitResult::CXChildVisit_Recurse;
	}
	else if (context.propertyParser->getParsingError() != EParsingError::Count)
	{
		//Fatal parsing error occured
		result->errors.emplace_back(ParsingError(context.propertyParser->getParsingError(), clang_getCursorLocation(context.rootCursor)));
	}

	return CXChildVisitResult::CXChildVisit_Break;
}

opt::optional<PropertyGroup> MethodParser::getProperties(CXCursor const& cursor) noexcept
{
	ParsingContext& context	= getContext();

	context.propertyParser->clean();

	return (clang_getCursorKind(cursor) == CXCursorKind::CXCursor_AnnotateAttr) ?
				context.propertyParser->getMethodProperties(Helpers::getString(clang_getCursorSpelling(cursor))) :
				opt::nullopt;
}

void MethodParser::initializeMethodInfo(MethodInfo& methodInfo) noexcept
{
	ParsingContext& context		= getContext();
	CXType			methodType	= clang_getCursorType(context.rootCursor);

	assert(methodType.kind == CXTypeKind::CXType_FunctionProto);

	//Define prototype
	methodInfo.prototype = Helpers::getString(clang_getTypeSpelling(methodType));

	//Define return type
	methodInfo.returnType =	TypeInfo(clang_getResultType(methodType));

	//Define method qualifiers
	if (clang_CXXMethod_isDefaulted(context.rootCursor))
	{
		methodInfo.qualifiers.isDefault = true;
	}
	if (clang_CXXMethod_isStatic(context.rootCursor))
	{
		methodInfo.qualifiers.isStatic = true;
	}
	if (clang_CXXMethod_isVirtual(context.rootCursor))
	{
		methodInfo.qualifiers.isVirtual = true;
	}
	if (clang_CXXMethod_isPureVirtual(context.rootCursor))
	{
		methodInfo.qualifiers.isPureVirtual = true;
	}
	if (clang_CXXMethod_isConst(context.rootCursor))
	{
		methodInfo.qualifiers.isConst = true;
	}
	if (clang_Cursor_isFunctionInlined(context.rootCursor))
	{
		methodInfo.qualifiers.isInline = true;
	}
}

void MethodParser::pushContext(CXCursor const& methodCursor, ParsingContext const&	parentContext, MethodParsingResult& out_result) noexcept
{
	ParsingContext newContext;

	newContext.parentContext			= &parentContext;
	newContext.rootCursor				= methodCursor;
	newContext.shouldCheckProperties	= true;
	newContext.propertyParser			= parentContext.propertyParser;
	newContext.parsingSettings			= parentContext.parsingSettings;
	newContext.parsingResult			= &out_result;

	contextsStack.push(std::move(newContext));
}