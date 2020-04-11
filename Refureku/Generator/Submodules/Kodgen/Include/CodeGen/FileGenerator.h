#pragma once

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <type_traits>

#include "Misc/Filesystem.h"
#include "CodeGen/GeneratedCodeTemplate.h"
#include "CodeGen/FileGenerationResult.h"
#include "CodeGen/GeneratedFile.h"
#include "Parsing/FileParser.h"

namespace kodgen
{
	class FileGenerator
	{
		private:
			static inline std::string								_entityMacrosDefFilename	= "EntityMacros.h";

			std::unordered_map<std::string,	GeneratedCodeTemplate*>	_generatedCodeTemplates;
			GeneratedCodeTemplate*									_defaultClassTemplate		= nullptr;
			GeneratedCodeTemplate*									_defaultStructTemplate		= nullptr;
			GeneratedCodeTemplate*									_defaultEnumTemplate		= nullptr;
			std::string												_supportedCodeTemplateRegex = "";

			void					updateSupportedCodeTemplateRegex()																								noexcept;
			void					generateEntityFile(FileGenerationResult& genResult, fs::path const& filePath, ParsingResult const& parsingResult)				noexcept;
			GeneratedCodeTemplate*	getEntityGeneratedCodeTemplate(EntityInfo& entityInfo, EFileGenerationError& out_error)									const	noexcept;
			void					writeEntityToFile(GeneratedFile& generatedFile, EntityInfo& entityInfo, FileGenerationResult& genResult)						noexcept;
			bool					shouldRegenerateFile(fs::path const& filePath)																			const	noexcept;
			fs::path				makePathToGeneratedFile(fs::path const& sourceFilePath)																	const	noexcept;
			void					processFile(FileParser& parser, FileGenerationResult& genResult, fs::path const& pathToFile)									noexcept;
			void					processIncludedFiles(FileParser& parser, FileGenerationResult& genResult, bool forceRegenerateAll)								noexcept;
			void					processIncludedDirectories(FileParser& parser, FileGenerationResult& genResult, bool forceRegenerateAll)						noexcept;
			void					refreshPropertyRules(ParsingSettings& parsingSettings)																	const	noexcept;
			void					generateMacrosFile(FileParser& parser)																					const	noexcept;

		protected:
			/**
			*	@brief Write a header for any generated file
			*
			*	@param file Object which allows to write into the generated file
			*	@param parsingResult Structure containing info about the parsed file
			*/
			virtual void	writeHeader(GeneratedFile& file, ParsingResult const& parsingResult)	const	noexcept;

			/**
			*	@brief Write a footer for any generated file
			*
			*	@param file Object which allows to write into the generated file
			*	@param parsingResult Structure containing info about the parsed file
			*/
			virtual void	writeFooter(GeneratedFile& file, ParsingResult const& parsingResult)	const	noexcept;

		public:
			/**
			*	@brief Main (complex) property name used to specify code generator in source code
			*/
			std::string						codeTemplateMainComplexPropertyName = "GenTemplate";

			/**
			*	@brief Extension used for generated files
			*/
			std::string						generatedFilesExtension = ".kodgen.h";

			/**
			*	@brief Path to the directory all files should be generated (and where existing ones are)
			*	If the existed directory doesn't exist, it will be created if possible
			*/
			fs::path						outputDirectory;

			/**
			*	Collection of files to parse.
			*	These files will be parsed without any further check if they exist.
			*/
			std::unordered_set<std::string>	toParseFiles;

			/**
			*	Collection of directories containing files to parse.
			*	All directories contained in the given directories will be recursively inspected, except if they are ignored
			*	All files contained in any parsed directory will be parsed, except if they are ignored or if their extension is not contained in the supportedExtensions.
			*/
			std::unordered_set<std::string>	toParseDirectories;

			/**
			*	Collection of ignored files.
			*	These files will never be parsed (except if they are also part of the includedFiles collection)
			*/
			std::unordered_set<std::string>	ignoredFiles;

			/**
			*	Collection of ignored directories.
			*	All directories contained in the given directories will be ignored, except if they are included
			*	All files contained in any ignored directory will be ignored, except if they are included
			*/
			std::unordered_set<std::string>	ignoredDirectories;

			/**
			*	Extensions of files which should be considered for parsing.
			*/
			std::unordered_set<std::string>	supportedExtensions;

			FileGenerator()		noexcept;
			~FileGenerator()	noexcept;

			/**
			*	@brief Add a new template to the list of generated code templates
			*	@brief This will override any template having the same templateName
			*
			*	@param templateName Name of the code template which will be specified in the source code
			*	@param codeTemplate Pointer to a GeneratedCodeTemplate instance (must be newed).
			*			The instance will be deleted by the FileGenerator when destroyed
			*	@param setAsDefaultClassTemplate Should this CodeTemplate be used as the default one when none is
			*			explicitly specified in source code
			*/
			void addGeneratedCodeTemplate(std::string const& templateName, GeneratedCodeTemplate* codeTemplate, bool setAsDefaultClassTemplate = false)	noexcept;

			/**
			*	@brief Setup the generated code template to use when no template is specified in a parsed source code class
			*
			*	@param templateName The name of the default generated code template.
			*						It must have been setup using the addGeneratedCodeTemplate(...) method before
			*
			*	@return true if the new default class template was setup successfully, else false
			*/
			bool setDefaultClassTemplate(std::string const& templateName)									noexcept;

			/**
			*	@brief Setup the generated code template to use when no template is specified in a parsed source code struct
			*
			*	@param templateName The name of the default generated code template.
			*						It must have been setup using the addGeneratedCodeTemplate(...) method before call
			*
			*	@return true if the new default struct template was setup successfully, else false
			*/
			bool setDefaultStructTemplate(std::string const& templateName)									noexcept;

			/**
			*	@brief Setup the generated code template to use when no template is specified in a parsed source code enum
			*
			*	@param codeTemplate The name of the default generated code template.
			*						It must have been setup using the addGeneratedCodeTemplate(...) method before
			*
			*	@return true if the new default enum template was setup successfully, else false
			*/
			bool setDefaultEnumTemplate(std::string const& templateName)									noexcept;

			/**
			*	@brief Parse registered files if they were changes since last generation
			*			and try to generate corresponding files using code templates
			*
			*	@param parser The parser to use for the parsing
			*	@param forceRegenerateAll Ignore the last write time check and reparse / regenerate all files
			*
			*	@return Structure containing result report
			*/
			FileGenerationResult generateFiles(FileParser& parser, bool forceRegenerateAll = false)			noexcept;
	};
}