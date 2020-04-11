#pragma once

#include <clang-c/Index.h>

#include "Misc/Filesystem.h"
#include "Misc/Optional.h"
#include "InfoStructures/ParsingInfo.h"
#include "Parsing/ClassParser.h"
#include "Parsing/EnumParser.h"
#include "Parsing/ParsingResult.h"
#include "Parsing/ParsingSettings.h"
#include "Parsing/PropertyParser.h"

namespace kodgen
{
	class FileParser
	{
		private:
			static inline std::string const	_parsingMacro		= "KODGEN_PARSING";
			
			CXIndex							_clangIndex;
			
			ClassParser						_classParser;
			EnumParser						_enumParser;
			ParsingInfo						_parsingInfo;

			//Variables used to build command line
			std::string						_kodgenParsingMacro	= "-D" + _parsingMacro;
			std::vector<std::string>		_projectIncludeDirs;
			std::string						_classPropertyMacro;
			std::string						_structPropertyMacro;
			std::string						_fieldPropertyMacro;
			std::string						_methodPropertyMacro;
			std::string						_enumPropertyMacro;
			std::string						_enumValuePropertyMacro;

			static CXChildVisitResult	staticParseCursor(CXCursor c, CXCursor parent, CXClientData clientData)			noexcept;
			
			void						refreshBuildCommandStrings()													noexcept;
			std::vector<char const*>	makeParseArguments()															noexcept;

			void						setupForParsing()																noexcept;

			CXChildVisitResult			parseCursor(CXCursor currentCursor)												noexcept;
			CXChildVisitResult			parseClass(CXCursor classCursor, bool isStruct)									noexcept;
			CXChildVisitResult			parseEnum(CXCursor enumCursor)													noexcept;

			/**
			*	Remove all previously parsed information from the class
			*/
			void	reset()																								noexcept;

		protected:
			/**
			*	@brief Overridable method called just before starting the parsing process of a file
			*
			*	@param parseFile Path to the file which is about to be parsed
			*/
			virtual void preParse(fs::path const& parseFile)								noexcept;

			/**
			*	@brief Overridable method called just after the parsing process has been finished
			*	@brief Even if the parsing process ended prematurely, this method is called
			*
			*	@param parseFile Path to the file which has been parsed
			*	@param result Result of the parsing
			*/
			virtual void postParse(fs::path const& parseFile, ParsingResult const& result)	noexcept;

		public:
			FileParser()					noexcept;
			FileParser(FileParser const&)	= default;
			FileParser(FileParser&&)		= default;
			virtual ~FileParser()			noexcept;

			/**
			*	Get the name of the macro which is set when parsing the source code
			*/
			static std::string const&	getParsingMacro()												noexcept;

			/**
			*	Get the parsing settings of the parser to setup it
			*/
			ParsingSettings&			getParsingSettings()											noexcept;

			/**
			*	Parse a file
			*
			*	@param parseFile Path to the file to parse
			*	@param out_result Result filled with the collected information
			*
			*	@return true if the parsing process finished without error, else false
			*/
			bool						parse(fs::path const& parseFile, ParsingResult& out_result)		noexcept;
	};
}