/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <clang-c/Index.h>

#include "Parsing/EntityParser.h"
#include "Parsing/ParsingResults/EnumValueParsingResult.h"

namespace kodgen
{
	class EnumValueParser final : public EntityParser
	{
		private:
			/**
			*	@brief This method is called at each node (cursor) of the parsing.
			*
			*	@param cursor		Current cursor to parse.
			*	@param parentCursor	Parent of the current cursor.
			*	@param clientData	Pointer to a data provided by the client. Must contain an EnumValueParser*.
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
			*	@brief Fill the enum value result properties.
			*
			*	@param annotationCursor The AST cursor to the enum value annotation.
			*/
			void							setProperties(CXCursor const& annotationCursor)		noexcept;

			/**
			*	@brief Push a new clean context to prepare enum value parsing.
			*
			*	@param enumCursor		Root cursor of the enum to parse.
			*	@param parentContext	Context the new context will inherit from.
			*	@param out_result		Result to fill during parsing.
			*/
			void							pushContext(CXCursor const&			enumCursor,
														ParsingContext const&	parentContext,
														EnumValueParsingResult&	out_result)		noexcept;

			/**
			*	@brief Helper to get the ParsingResult contained in the context as a ClassParsingResult.
			*
			*	@return The cast ClassParsingResult.
			*/
			inline EnumValueParsingResult*	getParsingResult()									noexcept;

		public:
			EnumValueParser()						= default;
			EnumValueParser(EnumValueParser const&)	= default;
			EnumValueParser(EnumValueParser&&)		= default;
			~EnumValueParser()						= default;

			/**
			*	@brief Parse the enum value starting at the provided AST cursor.
			*
			*	@param enumValueCursor	AST cursor to the enum value to parse.
			*	@param parentContext	Context the new context will inherit from.
			*	@param out_result		Result filled while parsing the enum value.
			*
			*	@return An enum which indicates how to choose the next cursor to parse in the AST.
			*/
			CXChildVisitResult	parse(CXCursor const&			enumValueCursor,
									  ParsingContext const&		parentContext,
									  EnumValueParsingResult&	out_result)		noexcept;
	};

	#include "Parsing/EnumValueParser.inl"
}