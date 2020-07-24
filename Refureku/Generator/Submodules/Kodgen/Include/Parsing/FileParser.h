#pragma once

#include <string>
#include <clang-c/Index.h>

#include "Misc/Filesystem.h"
#include "Misc/ILogger.h"
#include "Parsing/NamespaceParser.h"
#include "Parsing/ParsingResults/FileParsingResult.h"
#include "Parsing/ParsingSettings.h"
#include "Parsing/PropertyParser.h"

namespace kodgen
{
	class FileParser : public NamespaceParser
	{
		private:
			/** Index used internally by libclang to process a translation unit. */
			CXIndex							_clangIndex;

			/** Variables used to build compilation command line. */
			std::string						_kodgenParsingMacro		= "-D" + parsingMacro;
			std::vector<std::string>		_projectIncludeDirs;

			std::string						_namespacePropertyMacro;
			std::string						_classPropertyMacro;
			std::string						_structPropertyMacro;
			std::string						_fieldPropertyMacro;
			std::string						_methodPropertyMacro;
			std::string						_enumPropertyMacro;
			std::string						_enumValuePropertyMacro;

			/** Property parser used to parse properties of all entities. */
			PropertyParser					_propertyParser;		

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
			*	@brief Refresh all internal compilation macros to pass to the compiler.
			*/
			void						refreshBuildCommandStrings()									noexcept;

			/**
			*	@brief Make a list of all arguments to pass to the compilation command.
			*
			*	@return A vector of all compilation commands.
			*/
			std::vector<char const*>	makeCompilationArguments()										noexcept;

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
			*	@brief Log the compilation command arguments.
			*/
			void						logCompilationArguments()										noexcept;

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
			/** Macro defined internally when kodgen processes a translation unit. */
			static inline std::string const	parsingMacro	= "KODGEN_PARSING";

			/** Settings to use when parsing. */
			ParsingSettings					parsingSettings;

			/** Logger used to issue logs from the FileParser. */
			ILogger*						logger			= nullptr;

			FileParser()					noexcept;
			FileParser(FileParser const&)	= default;
			FileParser(FileParser&&)		= default;
			virtual ~FileParser()			noexcept;

			/**
			*	@brief Parse the file and fill the FileParsingResult.
			*
			*	@param toParseFile	Path to the file to parse.
			*	@param out_result	Result filled while parsing the file.
			*
			*	@return true if the parsing process finished without error, else false
			*/
			bool	parse(fs::path const&		toParseFile, 
						  FileParsingResult&	out_result)					noexcept;

			/**
			*	@brief Load parsing settings from the provided toml file. Unset settings remain unchanged.
			*
			*	@param pathToSettingsFile Path to the toml file.
			*
			*	@return true if a file could be loaded, else false.
			*/
			bool		loadSettings(fs::path const& pathToSettingsFile)	noexcept;
	};

	#include "Parsing/FileParser.inl"
}