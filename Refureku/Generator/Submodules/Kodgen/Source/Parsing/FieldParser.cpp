#include "Parsing/FieldParser.h"

#include <cassert>

#include "Parsing/ParsingSettings.h"
#include "Parsing/PropertyParser.h"
#include "Misc/Helpers.h"

using namespace kodgen;

CXChildVisitResult FieldParser::parse(CXCursor const& fieldCursor, ParsingContext const& parentContext, FieldParsingResult& out_result) noexcept
{
	//Make sure the cursor is compatible for the field parser
	assert(fieldCursor.kind == CXCursorKind::CXCursor_VarDecl || fieldCursor.kind == CXCursorKind::CXCursor_FieldDecl);

	//Init context
	ParsingContext& context = pushContext(fieldCursor, parentContext, out_result);

	if (!clang_visitChildren(fieldCursor, &FieldParser::parseNestedEntity, this) && context.shouldCheckProperties)
	{
		//If we reach this point, the cursor had no child (no annotation)
		//Check if the parent has the shouldParseAllNested flag set
		if (shouldParseCurrentEntity())
		{
			getParsingResult()->parsedField.emplace(fieldCursor, PropertyGroup());
		}
	}

	//Check properties validy one last time
	if (out_result.parsedField.has_value())
	{
		performFinalPropertiesCheck(*out_result.parsedField);
	}

	popContext();

	DISABLE_WARNING_PUSH
	DISABLE_WARNING_UNSCOPED_ENUM

	return (parentContext.parsingSettings->shouldAbortParsingOnFirstError && !out_result.errors.empty()) ? CXChildVisitResult::CXChildVisit_Break : CXChildVisitResult::CXChildVisit_Continue;

	DISABLE_WARNING_POP
}

CXChildVisitResult FieldParser::parseNestedEntity(CXCursor cursor, CXCursor /* parentCursor */, CXClientData clientData) noexcept
{
	FieldParser*	parser	= reinterpret_cast<FieldParser*>(clientData);
	ParsingContext&	context	= parser->getContext();

	if (context.shouldCheckProperties)
	{
		context.shouldCheckProperties = false;

		if (parser->shouldParseCurrentEntity() && cursor.kind != CXCursorKind::CXCursor_AnnotateAttr)
		{
			//Make it valid right away so init the result
			parser->getParsingResult()->parsedField.emplace(context.rootCursor, PropertyGroup());
		}
		else
		{
			//Set parsed field in result if it is valid
			return parser->setParsedEntity(cursor);
		}
	}

	return CXChildVisitResult::CXChildVisit_Continue;
}

CXChildVisitResult FieldParser::setParsedEntity(CXCursor const& annotationCursor) noexcept
{
	FieldParsingResult* result	= getParsingResult();
	ParsingContext&		context	= getContext();

	if (opt::optional<PropertyGroup> propertyGroup = getProperties(annotationCursor))
	{
		result->parsedField.emplace(context.rootCursor, std::move(*propertyGroup));
	}
	else if (!context.propertyParser->getParsingErrorDescription().empty())
	{
		//Fatal parsing error occured
		result->errors.emplace_back(ParsingError(context.propertyParser->getParsingErrorDescription(), clang_getCursorLocation(annotationCursor)));
	}

	return CXChildVisitResult::CXChildVisit_Break;
}

opt::optional<PropertyGroup> FieldParser::getProperties(CXCursor const& cursor) noexcept
{
	ParsingContext& context = getContext();

	context.propertyParser->clean();

	return (clang_getCursorKind(cursor) == CXCursorKind::CXCursor_AnnotateAttr) ?
				context.propertyParser->getFieldProperties(Helpers::getString(clang_getCursorSpelling(cursor))) :
				opt::nullopt;
}

ParsingContext& FieldParser::pushContext(CXCursor const& fieldCursor, ParsingContext const& parentContext, FieldParsingResult& out_result) noexcept
{
	ParsingContext newContext;

	newContext.parentContext			= &parentContext;
	newContext.rootCursor				= fieldCursor;
	newContext.shouldCheckProperties	= true;
	newContext.propertyParser			= parentContext.propertyParser;
	newContext.parsingSettings			= parentContext.parsingSettings;
	newContext.parsingResult			= &out_result;

	contextsStack.push(std::move(newContext));

	return contextsStack.top();
}