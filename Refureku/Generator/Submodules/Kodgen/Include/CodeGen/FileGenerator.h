#pragma once

#include <unordered_map>
#include <unordered_set>
#include <string>

#include "Misc/Filesystem.h"
#include "Misc/ILogger.h"
#include "CodeGen/GeneratedCodeTemplate.h"
#include "CodeGen/FileGenerationResult.h"
#include "CodeGen/GeneratedFile.h"
#include "Parsing/FileParser.h"

namespace kodgen
{
	class FileGenerator
	{
		private:
			/** Name of the internally generated header containing empty definitions for entity macros. */
			static inline std::string										_entityMacrosDefFilename		= "EntityMacros.h";

			/** All generated code templates usable by this generator. */
			std::unordered_map<std::string,	GeneratedCodeTemplate*>			_generatedCodeTemplates;
			
			/** Default generated code templates to use when none is specified in entity property parameters. */
			std::unordered_map<EntityInfo::EType, GeneratedCodeTemplate*>	_defaultGeneratedCodeTemplates;
			
			/** Regex used internally to determine either a generated code template name is valid or not. */
			std::string														_supportedCodeTemplateRegex		= "";

			/**
			*	@brief Update the _supportedCodeTemplateRegex string using the existing generated code templates contained in _generatedCodeTemplates.
			*/
			void					updateSupportedCodeTemplateRegex()												noexcept;
			
			/**
			*	@brief Parse a file and generate its paired file.
			*
			*	@param parser		The file parser to use.
			*	@param genResult	Reference to the generation result to fill during file generation.
			*	@param pathToFile	Path to the source file to parse.
			*/
			void					processFile(FileParser&				parser,
												FileGenerationResult&	genResult,
												fs::path const&			pathToFile)									noexcept;

			/**
			*	@brief Generate a file based on the @param genResult.
			*
			*	@param genResult		Reference to the generation result to fill during file generation.
			*	@param parsingResult	Result of a file parsing used to generate the new file.
			*/
			void					generateFile(FileGenerationResult&		genResult,
												 FileParsingResult const&	parsingResult)							noexcept;
			
			/**
			*	@brief Retrieve the appropriate generated code template to use for a given entity.
			*
			*	@param entityInfo	Information on a parsed entity.
			*	@param out_error	Reference to a file generation error. It is filled with an error if something wrong happen, else remains unchanged.
			*
			*	@return The appropriate generated code template if found, else nullptr.
			*/
			GeneratedCodeTemplate*	getEntityGeneratedCodeTemplate(EntityInfo const&		entityInfo,
																   EFileGenerationError&	out_error)		const	noexcept;

			/**
			*	@brief Provide information on whether the generated code for @param filePath should be regenerated or not.
			*
			*	@param filePath Path to the file we want to check the status.
			*
			*	@return true if the corresponding generated file should be regenerated, else false.
			*/
			bool					shouldRegenerateFile(fs::path const& filePath)							const	noexcept;
			
			/**
			*	@brief Build the generated file path from a source file.
			*	
			*	@param sourceFilePath	Path to the source file to parse & generate code from.
			*	
			*	@return The path to the generated file.
			*/
			fs::path				makePathToGeneratedFile(fs::path const& sourceFilePath)					const	noexcept;
			
			/**
			*	@brief Parse and generate all included individual files.
			*
			*	@param parser				File parser to use.
			*	@param genResult			Reference to the generation result to fill during file generation.
			*	@param forceRegenerateAll	Should all files be regenerated or not (regardless of FileGenerator::shouldRegenerateFile() returned value).
			*/
			void					processIncludedFiles(FileParser&			parser,
														 FileGenerationResult&	genResult,
														 bool					forceRegenerateAll)					noexcept;
			
			/**
			*	@brief Parse and generate files contained in all included directories.
			*	
			*	@param parser				File parser to use.
			*	@param genResult			Reference to the generation result to fill during file generation.
			*	@param forceRegenerateAll	Should all files be regenerated or not (regardless of FileGenerator::shouldRegenerateFile() returned value).
			*/
			void					processIncludedDirectories(FileParser&				parser,
															   FileGenerationResult&	genResult,
															   bool						forceRegenerateAll)			noexcept;
			
			/**
			*	@brief Refresh the property rules to allow generated code template names.
			*	
			*	@param parsingSettings Parsing settings of the file parser.
			*/
			void					refreshPropertyRules(ParsingSettings& parsingSettings)					const	noexcept;
			
			/**
			*	@brief Generate / update the entity macros file.
			*	
			*	@param parser The file parser.
			*/
			void					generateMacrosFile(FileParser& parser)									const	noexcept;

		protected:
			/**
			*	@brief Called just before generating a file. Can be used to perform any pre-generation initialization.
			*/
			virtual void	preGenerateFile()																noexcept;

			/**
			*	@brief Called just after generating a file. Can be used to perform any post-generation cleanup.
			*/
			virtual void	postGenerateFile()																noexcept;

			/**
			*	@brief Write a header into the provided file.
			*
			*	@param file Reference to the generated file.
			*	@param parsingResult Structure containing info about the parsed file.
			*/
			virtual void	writeHeader(GeneratedFile&				file,
										FileParsingResult const&	parsingResult)					const	noexcept;

			/**
			*	@brief Write a footer into the provided file.
			*
			*	@param file Reference to the generated file.
			*	@param parsingResult Structure containing info about the parsed file.
			*/
			virtual void	writeFooter(GeneratedFile&				file,
										FileParsingResult const&	parsingResult)					const	noexcept;

			/**
			*	@brief Generate code for entityInfo in generatedFile.
			*
			*	@param generatedFile	Generated file to write in.
			*	@param entityInfo		Entity we generate the code from.
			*	@param genResult		Reference to the generation result to fill during file generation.
			*/
			virtual void	writeEntityToFile(GeneratedFile&		generatedFile,
											  EntityInfo const&		entityInfo,
											  FileGenerationResult&	genResult)								noexcept;

			/**
			*	@brief Generate code for namespaceInfo in generatedFile.
			*
			*	@param generatedFile	Generated file to write in.
			*	@param namespaceInfo	Namespace we generate the code from.
			*	@param genResult		Reference to the generation result to fill during file generation.
			*/
			virtual void	writeNamespaceToFile(GeneratedFile&			generatedFile,
												 EntityInfo const&		namespaceInfo,
												 FileGenerationResult&	genResult)							noexcept;

			/**
			*	@brief Generate code for structClassInfo in generatedFile.
			*
			*	@param generatedFile	Generated file to write in.
			*	@param structClassInfo	Struct/class we generate the code from.
			*	@param genResult		Reference to the generation result to fill during file generation.
			*/
			virtual void	writeStructOrClassToFile(GeneratedFile&			generatedFile,
													 EntityInfo const&		structClassInfo,
													 FileGenerationResult&	genResult)						noexcept;

			/**
			*	@brief Generate code for nestedStructClassInfo in generatedFile.
			*
			*	@param generatedFile			Generated file to write in.
			*	@param nestedStructClassInfo	Nested struct/class we generate the code from.
			*	@param genResult				Reference to the generation result to fill during file generation.
			*/
			virtual void	writeNestedStructOrClassToFile(GeneratedFile&			generatedFile,
														   EntityInfo const&		nestedStructClassInfo,
														   FileGenerationResult&	genResult)				noexcept;

			/**
			*	@brief Generate code for enumInfo in generatedFile.
			*
			*	@param generatedFile	Generated file to write in.
			*	@param enumInfo			Enum we generate the code from.
			*	@param genResult		Reference to the generation result to fill during file generation.
			*/
			virtual void	writeEnumToFile(GeneratedFile&			generatedFile,
											EntityInfo const&		enumInfo,
											FileGenerationResult&	genResult)								noexcept;

			/**
			*	@brief Generate code for enumValueInfo in generatedFile.
			*
			*	@param generatedFile	Generated file to write in.
			*	@param enumValueInfo	Enum we generate the code from.
			*	@param genResult		Reference to the generation result to fill during file generation.
			*/
			virtual void	writeEnumValueToFile(GeneratedFile&			generatedFile,
												 EntityInfo const&		enumValueInfo,
												 FileGenerationResult&	genResult)							noexcept;

			/**
			*	@brief Generate code for fieldInfo in generatedFile.
			*
			*	@param generatedFile	Generated file to write in.
			*	@param fieldInfo		Field we generate the code from.
			*	@param genResult		Reference to the generation result to fill during file generation.
			*/
			virtual void	writeFieldToFile(GeneratedFile&			generatedFile,
											 EntityInfo const&		fieldInfo,
											 FileGenerationResult&	genResult)								noexcept;

			/**
			*	@brief Generate code for methodInfo in generatedFile.
			*
			*	@param generatedFile	Generated file to write in.
			*	@param methodInfo		Method we generate the code from.
			*	@param genResult		Reference to the generation result to fill during file generation.
			*/
			virtual void	writeMethodToFile(GeneratedFile&		generatedFile,
											  EntityInfo const&		methodInfo,
											  FileGenerationResult&	genResult)								noexcept;

		public:
			/** Logger used to issue logs from the FileGenerator. */
			ILogger*								logger								= nullptr;

			/** Main (complex) property name used to specify code generator in source code. */
			std::string								codeTemplateMainComplexPropertyName	= "GenTemplate";

			/** Extension used for generated files. */
			std::string								generatedFilesExtension				= ".kodgen.h";

			/**
			*	Path to the directory all files should be generated (and where existing ones are).
			*	If the existed directory doesn't exist, it will be created if possible.
			*/
			fs::path								outputDirectory;

			/**
			*	Collection of files to parse.
			*	These files will be parsed without any further check if they exist.
			*	/!\ Make sure all added paths use the os preferred syntax (you should call path.make_preferred() before).
			*/
			std::unordered_set<fs::path, PathHash>	toParseFiles;

			/**
			*	Collection of directories containing files to parse.
			*	All directories contained in the given directories will be recursively inspected, except if they are ignored.
			*	All files contained in any parsed directory will be parsed, except if they are ignored or if their extension is not contained in the supportedExtensions.
			*	/!\ Make sure all added paths use the os preferred syntax (you should call path.make_preferred() before).
			*/
			std::unordered_set<fs::path, PathHash>	toParseDirectories;

			/**
			*	Collection of ignored files.
			*	These files will never be parsed (except if they are also part of the includedFiles collection).
			*	/!\ Make sure all added paths use the os preferred syntax (you should call path.make_preferred() before).
			*/
			std::unordered_set<fs::path, PathHash>	ignoredFiles;

			/**
			*	Collection of ignored directories.
			*	All directories contained in the given directories will be ignored, except if they are included.
			*	All files contained in any ignored directory will be ignored, except if they are included.
			*	/!\ Make sure all added paths use the os preferred syntax (you should call path.make_preferred() before).
			*/
			std::unordered_set<fs::path, PathHash>	ignoredDirectories;

			/** Extensions of files which should be considered for parsing. */
			std::unordered_set<std::string>			supportedExtensions;

			FileGenerator()						noexcept;
			FileGenerator(FileGenerator const&)	= delete;
			FileGenerator(FileGenerator&&)		= delete;
			virtual ~FileGenerator()			noexcept;

			/**
			*	@brief Add a new template to the list of generated code templates.
			*		   if @param templateName is already defined in the generator, replace it.
			*
			*	@param templateName Name of the code template which will be specified in the source code
			*	@param codeTemplate Pointer to a GeneratedCodeTemplate instance (must be newed).
			*			The instance will be deleted by the FileGenerator when destroyed
			*/
			void addGeneratedCodeTemplate(std::string const&		templateName,
										  GeneratedCodeTemplate*	codeTemplate)			noexcept;

			/**
			*	@brief Set the default generated code template to use with the specified entity type when no template is specified in the entity properties.
			*
			*	@brief entityType	Type of the entity we set the default generated code template for.
			*						It can only be one of the following: Namespace, Class, Struct, Enum.
			*	@brief template		Name of the default generated code template.
			*						It must have been setup using the addGeneratedCodeTemplate(...) method before.
			*
			*	@return true if the new default generated code template was setup successfully, else false.
			*/
			bool setDefaultGeneratedCodeTemplate(EntityInfo::EType	entityType,
												 std::string const&	templateName)		noexcept;

			/**
			*	@brief Parse registered files if they were changes since last generation.
			*			and try to generate corresponding files using code templates.
			*
			*	@param parser The file parser to use for file parsing.
			*	@param forceRegenerateAll Ignore the last write time check and reparse / regenerate all files.
			*
			*	@return Structure containing file generation report.
			*/
			FileGenerationResult generateFiles(FileParser&	parser,
											   bool			forceRegenerateAll = false)	noexcept;

			/**
			*	@brief Setup this object's parameters with the provided toml file. Unset settings remain unchanged.
			*
			*	@param pathToSettingsFile Path to the toml file.
			*
			*	@return true if a file could be loaded, else false.
			*/
			bool				loadSettings(fs::path const& pathToSettingsFile)		noexcept;
	};
}