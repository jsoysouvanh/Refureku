/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <variant>
#include <string>

#include <clang-c/Index.h>

#include "Kodgen/Parsing/EntityParser.h"
#include "Kodgen/Parsing/EnumParser.h"
#include "Kodgen/Parsing/FieldParser.h"
#include "Kodgen/Parsing/MethodParser.h"
#include "Kodgen/Parsing/ParsingResults/ClassParsingResult.h"
#include "Kodgen/Parsing/ParsingResults/EnumParsingResult.h"
#include "Kodgen/Parsing/ParsingResults/FieldParsingResult.h"
#include "Kodgen/Parsing/ParsingResults/MethodParsingResult.h"
#include "Kodgen/Misc/Optional.h"

namespace kodgen
{
	class ClassParser : public EntityParser
	{
		private:
			/** Parser used to parse enums. */
			EnumParser		_enumParser;	

			/** Parser used to parse fields. */
			FieldParser		_fieldParser;

			/** Parser used to parse methods. */
			MethodParser	_methodParser;

			/**
			*	@brief This method is called at each node (cursor) of the parsing.
			*
			*	@param cursor		Current cursor to parse.
			*	@param parentCursor	Parent of the current cursor.
			*	@param clientData	Pointer to a data provided by the client. Must contain a ClassParser*.
			*
			*	@return An enum which indicates how to choose the next cursor to parse in the AST.
			*/
			static CXChildVisitResult		parseNestedEntity(CXCursor		cursor,
															  CXCursor		parentCursor,
															  CXClientData	clientData)								noexcept;

			/**
			*	@brief Update the context structClassTree recursively.
			* 
			*	@param childType			type of the child struct/class.
			*	@param baseOfCursor			AST cursor to the base class.
			*	@param out_structClassTree	StructClassTree to update.
			*/
			static void						updateStructClassTreeRecursion(CXType			childType,
																		   CXCursor			baseOfCursor,
																		   StructClassTree& out_structClassTree)	noexcept;

			/**
			*	@brief Push a new clean context to prepare struct/class parsing.
			*
			*	@param classCursor		Root cursor of the struct/class to parse.
			*	@param parentContext	Context the new context will inherit from.
			*	@param out_result		Result to fill during parsing.
			*
			*	@return The new context.
			*/
			ParsingContext&					pushContext(CXCursor const&			classCursor,
														ParsingContext const&	parentContext,
														ClassParsingResult&		out_result)				noexcept;

			/**
			*	@brief Retrieve the properties from the provided cursor if possible.
			*
			*	@param cursor Property cursor we retrieve information from.
			*
			*	@return A filled PropertyGroup if valid, else nullopt.
			*/
			opt::optional<PropertyGroup>	getProperties(CXCursor const& cursor)						noexcept;
			
			/**
			*	@brief Set the parsed struct/class if it is a valid one.
			*
			*	@param annotationCursor The cursor used to check struct/class validity.
			*
			*	@return An enum which indicates how to choose the next cursor to parse in the AST.
			*/
			CXChildVisitResult				setParsedEntity(CXCursor const& annotationCursor)			noexcept;

			/**
			*	@brief Update the access specifier in the parsing context.
			*
			*	@param cursor AST cursor to the new access specifier.
			*/
			void							updateAccessSpecifier(CXCursor const& cursor)				noexcept;
			
			/**
			*	@brief Update the context structClassTree according to the provided inheritance cursor.
			* 
			*	@param cursor AST cursor to the base class.
			*/
			void							updateStructClassTree(CXCursor cursor)						noexcept;

			/**
			*	@brief Add a base class (parent class) to the currently parsed struct/class info.
			*
			*	@param cursor AST cursor to the base class.
			*/
			void							addBaseClass(CXCursor cursor)								noexcept;

			/**
			*	@brief Add the provided struct/class result to the current class context result.
			*
			*	@param result ClassParsingResult to add.
			*/
			void							addClassResult(ClassParsingResult&& result)					noexcept;

			/**
			*	@brief Add the provided enum result to the current class context result.
			*
			*	@param result ClassParsingResult to add.
			*/
			void							addEnumResult(EnumParsingResult&& result)					noexcept;

			/**
			*	@brief Add the provided field result to the current class context result.
			*
			*	@param result FieldParsingResult to add.
			*/
			void							addFieldResult(FieldParsingResult&& result)					noexcept;

			/**
			*	@brief Add the provided method result to the current class context result.
			*
			*	@param result MethodParsingResult to add.
			*/
			void							addMethodResult(MethodParsingResult&& result)				noexcept;

			/**
			*	@brief Helper to get the ParsingResult contained in the context as a ClassParsingResult.
			*
			*	@return The cast ClassParsingResult.
			*/
			inline ClassParsingResult*		getParsingResult()											noexcept;

		protected:
			/**
			*	@brief Parse a struct or class.
			*
			*	@param classCursor		AST cursor to the struct/class to parse.
			*	@param out_visitResult	An enum which indicates how to choose the next cursor to parse in the AST.
			*
			*	@return A structure containing information about the parsed struct/class.
			*/
			ClassParsingResult	parseClass(CXCursor const&		classCursor,
										   CXChildVisitResult&	out_visitResult)	noexcept;

			/**
			*	@brief Parse an enum.
			*
			*	@param enumCursor		AST cursor to the enum to parse.
			*	@param out_visitResult	An enum which indicates how to choose the next cursor to parse in the AST.
			*
			*	@return A structure containing information about the parsed enum.
			*/
			EnumParsingResult	parseEnum(CXCursor const&		enumCursor,
										  CXChildVisitResult&	out_visitResult)	noexcept;

			/**
			*	@brief Parse a field.
			*
			*	@param fieldCursor		AST cursor to the field to parse.
			*	@param out_visitResult	An enum which indicates how to choose the next cursor to parse in the AST.
			*
			*	@return A structure containing information about the parsed field.
			*/
			FieldParsingResult	parseField(CXCursor const&		fieldCursor,
										   CXChildVisitResult&	out_visitResult)	noexcept;

			/**
			*	@brief Parse a function or method.
			*
			*	@param methodCursor		AST cursor to the function/method to parse.
			*	@param out_visitResult	An enum which indicates how to choose the next cursor to parse in the AST.
			*
			*	@return A structure containing information about the parsed function/method.
			*/
			MethodParsingResult	parseMethod(CXCursor const&		methodCursor,
											CXChildVisitResult&	out_visitResult)	noexcept;

		public:
			ClassParser()					= default;
			ClassParser(ClassParser const&)	= default;
			ClassParser(ClassParser&&)		= default;
			~ClassParser()					= default;

			/**
			*	@brief Parse the struct/class starting at the provided AST cursor.
			*
			*	@param classCursor		AST cursor to the struct/class to parse.
			*	@param parentContext	Context the new context will inherit from.
			*	@param out_result		Result filled while parsing the struct/class.
			*
			*	@return An enum which indicates how to choose the next cursor to parse in the AST.
			*/
			CXChildVisitResult	parse(CXCursor const&			classCursor,
									  ParsingContext const&		parentContext,
									  ClassParsingResult&		out_result)		noexcept;
	};

	#include "Kodgen/Parsing/ClassParser.inl"
}