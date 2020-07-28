#include "Parsing/ClassParser.h"

#include <cassert>

#include "Parsing/ParsingSettings.h"
#include "Parsing/PropertyParser.h"
#include "Properties/NativeProperties.h"
#include "InfoStructures/NamespaceInfo.h"
#include "InfoStructures/StructClassInfo.h"
#include "InfoStructures/NestedStructClassInfo.h"
#include "InfoStructures/FieldInfo.h"
#include "InfoStructures/MethodInfo.h"
#include "InfoStructures/EntityInfo.h"
#include "InfoStructures/NestedEnumInfo.h"
#include "Misc/Helpers.h"
#include "Misc/DisableWarningMacros.h"

using namespace kodgen;

CXChildVisitResult ClassParser::parse(CXCursor const& classCursor, ParsingContext const& parentContext, ClassParsingResult& out_result) noexcept
{
	//Make sure the cursor is compatible for the class parser
	assert(classCursor.kind == CXCursorKind::CXCursor_ClassDecl || classCursor.kind == CXCursorKind::CXCursor_StructDecl);

	//Init context
	ParsingContext& context = pushContext(classCursor, parentContext, out_result);

	if (!clang_visitChildren(classCursor, &ClassParser::parseNestedEntity, this) && context.shouldCheckProperties)
	{
		//If we reach this point, the cursor had no child (no annotation)
		//Check if the parent has the shouldParseAllNested flag set
		if (shouldParseCurrentEntity())
		{
			getParsingResult()->parsedClass.emplace(classCursor, PropertyGroup(), (classCursor.kind == CXCursorKind::CXCursor_ClassDecl) ? EntityInfo::EType::Class : EntityInfo::EType::Struct);
		}
	}

	popContext();

	DISABLE_WARNING_PUSH
	DISABLE_WARNING_UNSCOPED_ENUM

	return (parentContext.parsingSettings->shouldAbortParsingOnFirstError && !out_result.errors.empty()) ? CXChildVisitResult::CXChildVisit_Break : CXChildVisitResult::CXChildVisit_Continue;

	DISABLE_WARNING_POP
}

CXChildVisitResult ClassParser::parseNestedEntity(CXCursor cursor, CXCursor /* parentCursor */, CXClientData clientData) noexcept
{
	ClassParser*	parser	= reinterpret_cast<ClassParser*>(clientData);
	ParsingContext&	context = parser->getContext();

	if (context.shouldCheckProperties)
	{
		context.shouldCheckProperties = false;

		if (parser->shouldParseCurrentEntity() && cursor.kind != CXCursorKind::CXCursor_AnnotateAttr)
		{
			//Make it valid right away so init the result
			parser->getParsingResult()->parsedClass.emplace(context.rootCursor, PropertyGroup(), (context.rootCursor.kind == CXCursorKind::CXCursor_ClassDecl) ? EntityInfo::EType::Class : EntityInfo::EType::Struct);
		}
		else
		{
			//Set parsed struct/class in result if it is valid
			return parser->setParsedEntity(cursor);
		}
	}

	CXChildVisitResult visitResult = CXChildVisitResult::CXChildVisit_Continue;

	switch (cursor.kind)
	{
		case CXCursorKind::CXCursor_CXXFinalAttr:
			if (parser->getParsingResult()->parsedClass.has_value())
			{
				parser->getParsingResult()->parsedClass->qualifiers.isFinal = true;
			}
			break;

		case CXCursorKind::CXCursor_CXXAccessSpecifier:
			parser->updateAccessSpecifier(cursor);
			break;

		case CXCursorKind::CXCursor_CXXBaseSpecifier:
			parser->addBaseClass(cursor);
			break;

		case CXCursorKind::CXCursor_Constructor:
			//TODO: Might handle this someday
			break;

		case CXCursorKind::CXCursor_StructDecl:
			[[fallthrough]];
		case CXCursorKind::CXCursor_ClassDecl:
			parser->addClassResult(parser->parseClass(cursor, visitResult));
			break;

		case CXCursorKind::CXCursor_EnumDecl:
			parser->addEnumResult(parser->parseEnum(cursor, visitResult));
			break;

		case CXCursorKind::CXCursor_VarDecl:	//For static fields
			[[fallthrough]];
		case CXCursorKind::CXCursor_FieldDecl:
			parser->addFieldResult(parser->parseField(cursor, visitResult));
			break;

		case CXCursorKind::CXCursor_CXXMethod:
			parser->addMethodResult(parser->parseMethod(cursor, visitResult));
			break;

		default:
			break;
	}

	return visitResult;
}

ClassParsingResult ClassParser::parseClass(CXCursor const& classCursor, CXChildVisitResult& out_visitResult) noexcept
{
	ClassParsingResult classResult;

	out_visitResult	= parse(classCursor, getContext(), classResult);

	return classResult;
}

EnumParsingResult ClassParser::parseEnum(CXCursor const& enumCursor, CXChildVisitResult& out_visitResult) noexcept
{
	EnumParsingResult enumResult;

	out_visitResult = _enumParser.parse(enumCursor, getContext(), enumResult);

	return enumResult;
}

FieldParsingResult ClassParser::parseField(CXCursor const& fieldCursor, CXChildVisitResult& out_visitResult) noexcept
{
	FieldParsingResult fieldResult;

	out_visitResult = _fieldParser.parse(fieldCursor, getContext(), fieldResult);

	return fieldResult;
}

MethodParsingResult	ClassParser::parseMethod(CXCursor const& methodCursor, CXChildVisitResult& out_visitResult) noexcept
{
	MethodParsingResult methodResult;

	out_visitResult = _methodParser.parse(methodCursor, getContext(), methodResult);

	return methodResult;
}

ParsingContext& ClassParser::pushContext(CXCursor const& classCursor, ParsingContext const& parentContext, ClassParsingResult& out_result) noexcept
{
	ParsingContext newContext;

	newContext.parentContext			= &parentContext;
	newContext.rootCursor				= classCursor;
	newContext.shouldCheckProperties	= true;
	newContext.propertyParser			= parentContext.propertyParser;
	newContext.parsingSettings			= parentContext.parsingSettings;
	newContext.parsingResult			= &out_result;
	newContext.currentAccessSpecifier	= (classCursor.kind == CXCursorKind::CXCursor_ClassDecl) ? EAccessSpecifier::Private : EAccessSpecifier::Public;

	contextsStack.push(std::move(newContext));

	return contextsStack.top();
}

CXChildVisitResult ClassParser::setParsedEntity(CXCursor const& annotationCursor) noexcept
{
	ParsingContext& context = getContext();

	if (opt::optional<PropertyGroup> propertyGroup = getProperties(annotationCursor))
	{
		//Set the parsing entity in the result and update the shouldParseAllNested flag in the context
		updateShouldParseAllNested(getParsingResult()->parsedClass.emplace(context.rootCursor, std::move(*propertyGroup), (context.rootCursor.kind == CXCursorKind::CXCursor_ClassDecl) ? EntityInfo::EType::Class : EntityInfo::EType::Struct));

		return CXChildVisitResult::CXChildVisit_Recurse;
	}
	else
	{
		if (context.propertyParser->getParsingError() != EParsingError::Count)
		{
			context.parsingResult->errors.emplace_back(ParsingError(context.propertyParser->getParsingError(), clang_getCursorLocation(annotationCursor)));
		}

		return CXChildVisitResult::CXChildVisit_Break;
	}
}

opt::optional<PropertyGroup> ClassParser::getProperties(CXCursor const& cursor) noexcept
{
	ParsingContext& context = getContext();

	context.propertyParser->clean();

	if (clang_getCursorKind(cursor) == CXCursorKind::CXCursor_AnnotateAttr)
	{
		switch (context.rootCursor.kind)
		{
			case CXCursorKind::CXCursor_ClassDecl:
				return context.propertyParser->getClassProperties(Helpers::getString(clang_getCursorSpelling(cursor)));
				break;

			case CXCursorKind::CXCursor_StructDecl:
				return context.propertyParser->getStructProperties(Helpers::getString(clang_getCursorSpelling(cursor)));
				break;

			default:
				break;
		}
	}

	return opt::nullopt;
}

void ClassParser::updateAccessSpecifier(CXCursor const& cursor) noexcept
{
	assert(cursor.kind == CXCursorKind::CXCursor_CXXAccessSpecifier);

	getContext().currentAccessSpecifier = static_cast<EAccessSpecifier>(clang_getCXXAccessSpecifier(cursor));
}

void ClassParser::addBaseClass(CXCursor cursor) noexcept
{
	assert(clang_getCursorKind(cursor) == CXCursorKind::CXCursor_CXXBaseSpecifier);

	if (getParsingResult()->parsedClass.has_value())
	{
		getParsingResult()->parsedClass->parents.emplace_back(StructClassInfo::ParentInfo{ static_cast<EAccessSpecifier>(clang_getCXXAccessSpecifier(cursor)), TypeInfo(clang_getCursorType(cursor)) });
	}
}

void ClassParser::addFieldResult(FieldParsingResult&& result) noexcept
{
	ParsingContext& context = getContext();

	if (result.parsedField.has_value() && getParsingResult()->parsedClass.has_value())
	{
		//Update field access specifier
		result.parsedField->accessSpecifier = context.currentAccessSpecifier;

		getParsingResult()->parsedClass->fields.emplace_back(std::move(result.parsedField).value());
	}

	//Append errors if any
	if (!result.errors.empty())
	{
		context.parsingResult->errors.insert(getParsingResult()->errors.cend(), std::make_move_iterator(result.errors.cbegin()), std::make_move_iterator(result.errors.cend()));
	}
}

void ClassParser::addMethodResult(MethodParsingResult&& result) noexcept
{
	ParsingContext& context = getContext();

	if (result.parsedMethod.has_value() && getParsingResult()->parsedClass.has_value())
	{
		//Update method access specifier
		result.parsedMethod->accessSpecifier = context.currentAccessSpecifier;

		getParsingResult()->parsedClass->methods.emplace_back(std::move(result.parsedMethod).value());
	}

	//Append errors if any
	if (!result.errors.empty())
	{
		context.parsingResult->errors.insert(getParsingResult()->errors.cend(), std::make_move_iterator(result.errors.cbegin()), std::make_move_iterator(result.errors.cend()));
	}
}

void ClassParser::addClassResult(ClassParsingResult&& result) noexcept
{
	ParsingContext& context = getContext();

	if (result.parsedClass.has_value() && getParsingResult()->parsedClass.has_value())
	{
		switch (result.parsedClass->entityType)
		{
			case EntityInfo::EType::Struct:
				getParsingResult()->parsedClass->nestedStructs.emplace_back(std::make_shared<NestedStructClassInfo>(std::move(result.parsedClass).value(), context.currentAccessSpecifier));
				break;

			case EntityInfo::EType::Class:
				getParsingResult()->parsedClass->nestedClasses.emplace_back(std::make_shared<NestedStructClassInfo>(std::move(result.parsedClass).value(), context.currentAccessSpecifier));
				break;

			default:
				assert(false);	//Should never reach this point
				break;
		}
	}

	//Append errors if any
	if (!result.errors.empty())
	{
		context.parsingResult->errors.insert(getParsingResult()->errors.cend(), std::make_move_iterator(result.errors.cbegin()), std::make_move_iterator(result.errors.cend()));
	}
}

void ClassParser::addEnumResult(EnumParsingResult&& result) noexcept
{
	ParsingContext& context = getContext();

	if (result.parsedEnum.has_value() && getParsingResult()->parsedClass.has_value())
	{
		getParsingResult()->parsedClass->nestedEnums.emplace_back(NestedEnumInfo(std::move(result.parsedEnum).value(), context.currentAccessSpecifier));
	}

	//Append errors if any
	if (!result.errors.empty())
	{
		context.parsingResult->errors.insert(getParsingResult()->errors.cend(), std::make_move_iterator(result.errors.cbegin()), std::make_move_iterator(result.errors.cend()));
	}
}