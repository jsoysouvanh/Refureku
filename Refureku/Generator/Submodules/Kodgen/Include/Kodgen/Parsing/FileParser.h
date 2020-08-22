/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <string>
#include <vector>

#include <clang-c/Index.h>

#include "Kodgen/Parsing/NamespaceParser.h"
#include "Kodgen/Parsing/ParsingResults/FileParsingResult.h"
#include "Kodgen/Parsing/ParsingSettings.h"
#include "Kodgen/Parsing/PropertyParser.h"
#include "Kodgen/Misc/Filesystem.h"
#include "Kodgen/Misc/ILogger.h"

namespace kodgen
{
	class FileParser : public NamespaceParser
	{
		private:
			/** Index used internally by libclang to process a translation unit. */
			CXIndex			_clangIndex;

			/** Property parser used to parse properties of all entities. */
			PropertyParser	_propertyParser;		

			/**
			*	@brief This method is called at each node (cursor) of the parsing.
			*
			*	@param cursor		Current cursor to parse.
			*	@param parentCursor	Parent of the current cursor.
			*	@param clientData	Pointer to a data provided by the client. Must contain a FileParser*.
			*
			*	@return An enum which indicates how to choose the next cursor to parse in the AST.
			*/
			static CXChildVisitResult	parseNestedEntity(CXCursor		cursor,
														  CXCursor		parentCursor,
														  CXClientData	clientData)						noexcept;

			/**
			*	@brief Push a new clean context to prepare translation unit parsing.
			*
			*	@param translationUnit	The translation unit to parse.
			*	@param out_result		Result to fill during parsing.
			*
			*	@return The new context.
			*/
			ParsingContext&				pushContext(CXTranslationUnit const&	translationUnit,
													FileParsingResult&			out_result)				noexcept;

			/**
			*	@brief Add the provided namespace result to the current file context result.
			*
			*	@param result NamespaceParsingResult to add.
			*/
			void						addNamespaceResult(NamespaceParsingResult&& result)				noexcept;

			/**
			*	@brief Add the provided struct/class result to the current file context result.
			*
			*	@param result ClassParsingResult to add.
			*/
			void						addClassResult(ClassParsingResult&& result)						noexcept;

			/**
			*	@brief Add the provided enum result to the current file context result.
			*
			*	@param result EnumParsingResult to add.
			*/
			void						addEnumResult(EnumParsingResult&& result)						noexcept;

			/**
			*	@brief Add the provided variable result to the current file context result.
			*
			*	@param result VariableParsingResult to add.
			*/
			void						addVariableResult(VariableParsingResult&& result)				noexcept;

			/**
			*	@brief Add the provided function result to the current file context result.
			*
			*	@param result FunctionParsingResult to add.
			*/
			void						addFunctionResult(FunctionParsingResult&& result)				noexcept;
			
			/**
			*	@brief Refresh outer entities of the passed FileParsingResult.
			*
			*	@param out_result Result to refresh.
			*/
			void						refreshOuterEntity(FileParsingResult& out_result)		const	noexcept;

			/**
			*	@brief Log the diagnostic of the provided translation units.
			*
			*	@param translationUnit Translation unit we want to log the diagnostic of.
			*/
			void						logDiagnostic(CXTranslationUnit const& translationUnit)	const	noexcept;

			/**
			*	@brief Helper to get the ParsingResult contained in the context as a FileParsingResult.
			*
			*	@return The cast FileParsingResult.
			*/
			inline FileParsingResult*	getParsingResult()												noexcept;

		protected:
			/**
			*	@brief Overridable method called just before starting the parsing process of a file
			*
			*	@param parseFile Path to the file which is about to be parsed
			*/
			virtual void preParse(fs::path const& parseFile)									noexcept;

			/**
			*	@brief Overridable method called just after the parsing process has been finished
			*	@brief Even if the parsing process ended prematurely, this method is called
			*
			*	@param parseFile Path to the file which has been parsed
			*	@param result Result of the parsing
			*/
			virtual void postParse(fs::path const& parseFile, FileParsingResult const& result)	noexcept;

		public:
			/** Settings to use when parsing. */
			ParsingSettings const*	parsingSettings;

			/** Logger used to issue logs from the FileParser. */
			ILogger*				logger			= nullptr;

			FileParser()					noexcept;
			FileParser(FileParser const&)	noexcept;
			FileParser(FileParser&&)		noexcept;
			virtual ~FileParser()			noexcept;

			/**
			*	@brief Parse the file and fill the FileParsingResult.
			*
			*	@param toParseFile	Path to the file to parse.
			*	@param compilArgs	Arguments to use to generate the provided file AST.
			*	@param out_result	Result filled while parsing the file.
			*
			*	@return true if the parsing process finished without error, else false
			*/
			bool	parse(fs::path const&					toParseFile,
						  std::vector<char const*> const&	compilArgs,
						  FileParsingResult&				out_result)		noexcept;
	};

	#include "Kodgen/Parsing/FileParser.inl"
}