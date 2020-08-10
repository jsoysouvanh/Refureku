#include "Kodgen/Parsing/FunctionParser.h"

#include <assert.h>

#include "Kodgen/Parsing/PropertyParser.h"
#include "Kodgen/Misc/Helpers.h"
#include "Kodgen/Misc/DisableWarningMacros.h"

using namespace kodgen;

CXChildVisitResult FunctionParser::parse(CXCursor const& functionCursor, ParsingContext const& parentContext, FunctionParsingResult& out_result) noexcept
{
	//Make sure the cursor is compatible for the method parser
	assert(functionCursor.kind == CXCursorKind::CXCursor_FunctionDecl);	// /!\ might have to add CXCursor_FunctionTemplate

	//Init context
	ParsingContext& context = pushContext(functionCursor, parentContext, out_result);

	if (!clang_visitChildren(functionCursor, &FunctionParser::parseNestedEntity, this) && context.shouldCheckProperties)
	{
		//If we reach this point, the cursor had no child (no annotation)
		//Check if the parent has the shouldParseAllNested flag set
		if (shouldParseCurrentEntity())
		{
			getParsingResult()->parsedFunction.emplace(functionCursor, PropertyGroup());
		}
	}

	//Check properties validy one last time
	if (out_result.parsedFunction.has_value())
	{
		performFinalPropertiesCheck(*out_result.parsedFunction);
	}

	popContext();

	DISABLE_WARNING_PUSH
	DISABLE_WARNING_UNSCOPED_ENUM

	return (parentContext.parsingSettings->shouldAbortParsingOnFirstError && !out_result.errors.empty()) ? CXChildVisitResult::CXChildVisit_Break : CXChildVisitResult::CXChildVisit_Continue;

	DISABLE_WARNING_POP
}

CXChildVisitResult FunctionParser::parseNestedEntity(CXCursor cursor, CXCursor /* parentCursor */, CXClientData clientData) noexcept
{
	FunctionParser*	parser	= reinterpret_cast<FunctionParser*>(clientData);
	ParsingContext&	context = parser->getContext();

	if (context.shouldCheckProperties)
	{
		context.shouldCheckProperties = false;

		if (parser->shouldParseCurrentEntity() && cursor.kind != CXCursorKind::CXCursor_AnnotateAttr)
		{
			//Make it valid right away so init the result
			parser->getParsingResult()->parsedFunction.emplace(context.rootCursor, PropertyGroup());
		}
		else
		{
			//Set parsed method in result if it is valid
			return parser->setParsedEntity(cursor);
		}
	}

	switch (clang_getCursorKind(cursor))
	{
		case CXCursorKind::CXCursor_ParmDecl:
			if (parser->getParsingResult()->parsedFunction.has_value())
			{
				parser->getParsingResult()->parsedFunction->parameters.emplace_back(FunctionParamInfo{TypeInfo(clang_getCursorType(cursor)), Helpers::getString(clang_getCursorDisplayName(cursor))});
			}
			break;

		default:
			//std::cout << "Unknown method sub cursor: " << Helpers::getString(clang_getCursorKindSpelling(clang_getCursorKind(cursor))) << std::endl;
			break;
	}

	return CXChildVisitResult::CXChildVisit_Recurse;
}

CXChildVisitResult FunctionParser::setParsedEntity(CXCursor const& annotationCursor) noexcept
{
	FunctionParsingResult*	result	= getParsingResult();
	ParsingContext&			context	= getContext();

	if (opt::optional<PropertyGroup> propertyGroup = getProperties(annotationCursor))
	{
		//Set the parsed entity in the result & initialize its information from the method cursor
		result->parsedFunction.emplace(context.rootCursor, std::move(*propertyGroup));

		return CXChildVisitResult::CXChildVisit_Recurse;
	}
	else if (!context.propertyParser->getParsingErrorDescription().empty())
	{
		//Fatal parsing error occured
		result->errors.emplace_back(ParsingError(context.propertyParser->getParsingErrorDescription(), clang_getCursorLocation(context.rootCursor)));
	}

	return CXChildVisitResult::CXChildVisit_Break;
}

opt::optional<PropertyGroup> FunctionParser::getProperties(CXCursor const& cursor) noexcept
{
	ParsingContext& context	= getContext();

	context.propertyParser->clean();
	
	return (clang_getCursorKind(cursor) == CXCursorKind::CXCursor_AnnotateAttr) ?
		context.propertyParser->getFunctionProperties(Helpers::getString(clang_getCursorSpelling(cursor))) :
		opt::nullopt;
}

ParsingContext& FunctionParser::pushContext(CXCursor const& methodCursor, ParsingContext const&	parentContext, FunctionParsingResult& out_result) noexcept
{
	ParsingContext newContext;

	newContext.parentContext			= &parentContext;
	newContext.rootCursor				= methodCursor;
	newContext.shouldCheckProperties	= true;
	newContext.propertyParser			= parentContext.propertyParser;
	newContext.parsingSettings			= parentContext.parsingSettings;
	newContext.parsingResult			= &out_result;

	contextsStack.push(std::move(newContext));

	return contextsStack.top();
}