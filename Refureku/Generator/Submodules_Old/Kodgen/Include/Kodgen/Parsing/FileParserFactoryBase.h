/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <string>
#include <vector>

#include <Kodgen/Parsing/FileParser.h>

#include "Kodgen/Parsing/ParsingSettings.h"
#include "Kodgen/Misc/ILogger.h"
#include "Kodgen/Misc/Filesystem.h"

namespace kodgen
{
	class FileParserFactoryBase
	{
		private:
			/** Section name used in the toml file for FileParserFactory settings. */
			static constexpr char const*	_tomlSettingsSectionName	= "FileParsingSettings";

			/** Variables used to build compilation command line. */
			std::string						_kodgenParsingMacro			= "-D" + parsingMacro;
			std::vector<std::string>		_projectIncludeDirs;

			std::string						_namespacePropertyMacro;
			std::string						_classPropertyMacro;
			std::string						_structPropertyMacro;
			std::string						_variablePropertyMacro;
			std::string						_fieldPropertyMacro;
			std::string						_functionPropertyMacro;
			std::string						_methodPropertyMacro;
			std::string						_enumPropertyMacro;
			std::string						_enumValuePropertyMacro;

			std::vector<char const*>		_compilationArguments;

			/**
			*	@brief Refresh all internal compilation macros to pass to the compiler.
			*/
			void	refreshBuildCommandStrings()							noexcept;

			/**
			*	@brief Make a list of all arguments to pass to the compilation command and store it in _compilationArguments.
			*/
			void	refreshCompilationArguments()							noexcept;

			/**
			*	@brief Log currently stored compilation command arguments.
			*/
			void	logCompilationArguments()								noexcept;


			/**
			*	@brief Load the shouldParseAllEntities setting from toml.
			*
			*	@param table Toml content.
			*/
			void	loadShouldParseAllEntities(toml::value const& table)			noexcept;

			/**
			*	@brief Load the shouldLogDiagnostic setting from toml.
			*
			*	@param table Toml content.
			*/
			void	loadShouldLogDiagnostic(toml::value const& table)				noexcept;

			/**
			*	@brief Load the shouldAbortParsingOnFirstError setting from toml.
			*
			*	@param table Toml content.
			*/
			void	loadShouldAbortParsingOnFirstError(toml::value const& table)	noexcept;

			/**
			*	@brief Load project include directories paths from toml.
			*	
			*	@param table Toml content.
			*/
			void	loadProjectIncludeDirectories(toml::value const& table)			noexcept;

			/**
			*	@brief Load the compilerExeName from toml.
			*
			*	@param table Toml content.
			*/
			void	loadCompilerExeName(toml::value const& table)					noexcept;

		protected:
			FileParserFactoryBase()								= default;
			FileParserFactoryBase(FileParserFactoryBase const&)	= default;
			FileParserFactoryBase(FileParserFactoryBase&&)		= default;
			~FileParserFactoryBase()							= default;

			/**
			*	@brief	Setup a generated parser for parsing, forwarding any necessary data/settings.
			*			FileParserFactory::setupParser(fileParser) **MUST** be called in any override implementation.
			*
			*	@param fileParser The generated file parser to setup. It can safely be downcasted to the type of generated FileParser.
			*/
			virtual void setupFileParser(kodgen::FileParser& fileParser)	const noexcept;

		public:
			/** Macro defined internally when kodgen processes a translation unit. */
			static inline std::string const	parsingMacro	= "KODGEN_PARSING";

			/** Settings used by generated FileParsers. */
			ParsingSettings					parsingSettings;

			/** Logger used to issue logs from generated FileParser. */
			ILogger*						logger			= nullptr;

			/**
			*	@brief	Build compilation arguments for generated parsers. This method must be called
			*			**AFTER** settings have been setup and
			*			**BEFORE** generating new FileParsers with the loaded settings.
			*			If the settings ever change, this method must be called again before generating new FileParsers.
			*			
			*			Internal use only.
			*/
			void							_init()														noexcept;

			/**
			*	@brief Load parsing settings from the provided toml file. Unset settings remain unchanged.
			*
			*	@param pathToSettingsFile Path to the toml file.
			*
			*	@return true if a file could be loaded, else false.
			*/
			bool							loadSettings(fs::path const& pathToSettingsFile)			noexcept;

			/**
			*	@brief Getter for _compilationArguments.
			*	
			*	@return _compilationArguments;
			*/
			std::vector<char const*> const&	getCompilationArguments()							const	noexcept;
	};
}