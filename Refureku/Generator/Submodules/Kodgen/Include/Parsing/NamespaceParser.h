/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <clang-c/Index.h>

#include "Parsing/ClassParser.h"
#include "Parsing/ParsingResults/NamespaceParsingResult.h"

namespace kodgen
{
	class NamespaceParser : public ClassParser
	{
		private:
			/**
			*	@brief This method is called at each node (cursor) of the parsing.
			*
			*	@param cursor		Current cursor to parse.
			*	@param parentCursor	Parent of the current cursor.
			*	@param clientData	Pointer to a data provided by the client. Must contain a NamespaceParser*.
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
			*	@brief Set the parsed namespace if it is a valid one.
			*
			*	@param annotationCursor The cursor used to check namespace validity.
			*
			*	@return An enum which indicates how to choose the next cursor to parse in the AST.
			*/
			CXChildVisitResult				setParsedEntity(CXCursor const& annotationCursor)		noexcept;

			/**
			*	@brief Push a new clean context to prepare namespace parsing.
			*
			*	@param namespaceCursor	Root cursor of the namespace to parse.
			*	@param parentContext	Context the new context will inherit from.
			*	@param out_result		Result to fill during parsing.
			*
			*	@return The new context.
			*/
			ParsingContext&					pushContext(CXCursor const&				namespaceCursor,
														ParsingContext const&		parentContext,
														NamespaceParsingResult&		out_result)		noexcept;

			/**
			*	@brief Add the provided namespace result to the namespace result.
			*
			*	@param result NamespaceParsingResult to add.
			*/
			void							addNamespaceResult(NamespaceParsingResult&& result)		noexcept;

			/**
			*	@brief Add the provided struct/class result to the namespace result.
			*
			*	@param result ClassParsingResult to add.
			*/
			void							addClassResult(ClassParsingResult&& result)				noexcept;

			/**
			*	@brief Add the provided enum result to the namespace result.
			*
			*	@param result EnumParsingResult to add.
			*/
			void							addEnumResult(EnumParsingResult&& result)				noexcept;

			/**
			*	@brief Helper to get the ParsingResult contained in the context as a NamespaceParsingResult.
			*
			*	@return The cast NamespaceParsingResult.
			*/
			inline NamespaceParsingResult*	getParsingResult()										noexcept;

		protected:
			/**
			*	@brief Parse a namespace.
			*
			*	@param namespaceCursor	AST cursor to the namespace to parse.
			*	@param out_visitResult	An enum which indicates how to choose the next cursor to parse in the AST.
			*
			*	@return A structure containing information about the parsed namespace.
			*/
			NamespaceParsingResult 	parseNamespace(CXCursor const&		namespaceCursor,
												   CXChildVisitResult&	out_visitResult)	noexcept;

		public:
			NamespaceParser()						= default;
			NamespaceParser(NamespaceParser const&)	= default;
			NamespaceParser(NamespaceParser&&)		= default;
			~NamespaceParser()						= default;

			/**
			*	@brief Parse the namespace starting at the provided AST cursor.
			*
			*	@param namespaceCursor	AST cursor to the namespace to parse.
			*	@param parentContext	Context the new context will inherit from.
			*	@param out_result		Result filled while parsing the namespace.
			*
			*	@return An enum which indicates how to choose the next cursor to parse in the AST.
			*/
			CXChildVisitResult	parse(CXCursor const&			namespaceCursor,
									  ParsingContext const&		parentContext,
									  NamespaceParsingResult&	out_result)		noexcept;
	};

	#include "Parsing/NamespaceParser.inl"
}