/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <clang-c/Index.h>

#include "Kodgen/Parsing/EntityParser.h"
#include "Kodgen/Parsing/EnumValueParser.h"
#include "Kodgen/Parsing/ParsingResults/EnumParsingResult.h"

namespace kodgen
{
	class EnumParser final : public EntityParser
	{
		private:
			/** Parser used to parse enum values. */
			EnumValueParser	_enumValueParser;

			/**
			*	@brief This method is called at each node (cursor) of the parsing.
			*
			*	@param cursor		Current cursor to parse.
			*	@param parentCursor	Parent of the current cursor.
			*	@param clientData	Pointer to a data provided by the client. Must contain an EnumParser*.
			*
			*	@return An enum which indicates how to choose the next cursor to parse in the AST.
			*/
			static CXChildVisitResult		parseNestedEntity(CXCursor		cursor,
															  CXCursor		parentCursor,
															  CXClientData	clientData)			noexcept;

			/**
			*	@brief Retrieve the properties from the provided cursor if possible.
			*
			*	@param cursor Property cursor we retrieve information from.
			*
			*	@return A filled PropertyGroup if valid, else nullopt.
			*/
			opt::optional<PropertyGroup>	getProperties(CXCursor const& cursor)				noexcept;

			/**
			*	@brief Set the parsed enum into the context result if it is a valid one.
			*
			*	@param annotationCursor The cursor used to check enum validity.
			*
			*	@return An enum which indicates how to choose the next cursor to parse in the AST.
			*/
			CXChildVisitResult				setParsedEntity(CXCursor const& annotationCursor)	noexcept;

			/**
			*	@brief Add the provided enum value result to the current enum context result.
			*
			*	@param result ClassParsingResult to add.
			*/
			void							addEnumValueResult(EnumValueParsingResult&& result)	noexcept;

			/**
			*	@brief Push a new clean context to prepare enum parsing.
			*
			*	@param enumCursor		Root cursor of the enum to parse.
			*	@param parentContext	Context the new context will inherit from.
			*	@param out_result		Result to fill during parsing.
			*
			*	@param The new context.
			*/
			ParsingContext&					pushContext(CXCursor const&			enumCursor,
														ParsingContext const&	parentContext,
														EnumParsingResult&		out_result)		noexcept;

			/**
			*	@brief Helper to get the ParsingResult contained in the context as a ClassParsingResult.
			*
			*	@return The cast ClassParsingResult.
			*/
			inline EnumParsingResult*		getParsingResult()									noexcept;

		protected:
			/**
			*	@brief Parse an enum value.
			*
			*	@param enumValueCursor	AST cursor to the enum value to parse.
			*	@param out_visitResult	An enum which indicates how to choose the next cursor to parse in the AST.
			*
			*	@return A structure containing information about the parsed enum value.
			*/
			EnumValueParsingResult	parseEnumValue(CXCursor const&		enumValueCursor,
												   CXChildVisitResult&	out_visitResult)	noexcept;

		public:
			EnumParser()					= default;
			EnumParser(EnumParser const&)	= default;
			EnumParser(EnumParser&&)		= default;
			~EnumParser()					= default;

			/**
			*	@brief Parse the enum starting at the provided AST cursor.
			*
			*	@param enumCursor		AST cursor to the enum to parse.
			*	@param parentContext	Context the new context will inherit from.
			*	@param out_result		Result filled while parsing the enum.
			*
			*	@return An enum which indicates how to choose the next cursor to parse in the AST.
			*/
			CXChildVisitResult	parse(CXCursor const&			enumCursor,
									  ParsingContext const&		parentContext,
									  EnumParsingResult&		out_result)		noexcept;
	};

	#include "Kodgen/Parsing/EnumParser.inl"
}