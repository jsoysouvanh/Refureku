/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <clang-c/Index.h>

#include "Parsing/EntityParser.h"
#include "Parsing/ParsingResults/FieldParsingResult.h"
#include "Misc/Optional.h"

namespace kodgen
{
	class FieldParser : public EntityParser
	{
		private:
			/**
			*	@brief This method is called at each node (cursor) of the parsing.
			*
			*	@param cursor		Current cursor to parse.
			*	@param parentCursor	Parent of the current cursor.
			*	@param clientData	Pointer to a data provided by the client. Must contain a FieldParser*.
			*
			*	@return An enum which indicates how to choose the next cursor to parse in the AST.
			*/
			static CXChildVisitResult		parseNestedEntity(CXCursor		cursor,
															  CXCursor		parentCursor,
															  CXClientData	clientData)				noexcept;

			/**
			*	@brief Retrieve the properties from the provided cursor if possible.
			*
			*	@param cursor Property cursor we retrieve information from.
			*
			*	@return A filled PropertyGroup if valid, else nullopt.
			*/
			opt::optional<PropertyGroup>	getProperties(CXCursor const& cursor)					noexcept;

			/**
			*	@brief Set the parsed field if it is a valid one.
			*
			*	@param annotationCursor The cursor used to check field validity.
			*
			*	@return An enum which indicates how to choose the next cursor to parse in the AST.
			*/
			CXChildVisitResult				setParsedEntity(CXCursor const& annotationCursor)		noexcept;

			/**
			*	@brief Push a new clean context to prepare field parsing.
			*
			*	@param fieldCursor		Root cursor of the field to parse.
			*	@param parentContext	Context the new context will inherit from.
			*	@param out_result		Result to fill during parsing.
			*
			*	@return The new context.
			*/
			ParsingContext&					pushContext(CXCursor const&				fieldCursor,
														ParsingContext const&		parentContext,
														FieldParsingResult&			out_result)		noexcept;

			/**
			*	@brief Helper to get the ParsingResult contained in the context as a FieldParsingResult.
			*
			*	@return The cast FieldParsingResult.
			*/
			inline FieldParsingResult*		getParsingResult()										noexcept;

		public:
			FieldParser()					= default;
			FieldParser(FieldParser const&)	= default;
			FieldParser(FieldParser&&)		= default;
			~FieldParser()					= default;

			/**
			*	@brief Parse the field starting at the provided AST cursor.
			*
			*	@param fieldCursor		AST cursor to the field to parse.
			*	@param parentContext	Context the new context will inherit from.
			*	@param out_result		Result filled while parsing the field.
			*
			*	@return An enum which indicates how to choose the next cursor to parse in the AST.
			*/
			CXChildVisitResult	parse(CXCursor const&			fieldCursor,
									  ParsingContext const&		parentContext,
									  FieldParsingResult&		out_result)			noexcept;
	};

	#include "Parsing/FieldParser.inl"
}