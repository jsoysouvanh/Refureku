/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <unordered_map>

#include "Kodgen/CodeGen/FileGenerationSettings.h"
#include "Kodgen/CodeGen/GeneratedCodeTemplate.h"
#include "Kodgen/CodeGen/FileGenerationResult.h"
#include "Kodgen/Parsing/FileParser.h"
#include "Kodgen/CodeGen/GeneratedFile.h"
#include "Kodgen/Misc/ILogger.h"

namespace kodgen
{
	class FileGenerationUnit
	{
		//FileGenerator can access FileGenerationUnit class to forward logger and settings
		friend class FileGenerator;

		private:
			/** Generation settings. */
			FileGenerationSettings const*	_settings = nullptr;

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

		protected:
			/** Logger used to issue logs from the FileGenerationUnit. */
			ILogger*	logger = nullptr;

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
			*	@brief Generate code for a variable in generatedFile.
			*
			*	@param generatedFile	Generated file to write in.
			*	@param variableInfo		Variable we generate the code from.
			*	@param genResult		Reference to the generation result to fill during file generation.
			*/
			virtual void	writeVariableToFile(GeneratedFile&			generatedFile,
												EntityInfo const&		variableInfo,
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
			*	@brief Generate code for a (non-member) function in generatedFile.
			*
			*	@param generatedFile	Generated file to write in.
			*	@param functionInfo		Function we generate the code from.
			*	@param genResult		Reference to the generation result to fill during file generation.
			*/
			virtual void	writeFunctionToFile(GeneratedFile&			generatedFile,
												EntityInfo const&		functionInfo,
												FileGenerationResult&	genResult)							noexcept;

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
			FileGenerationUnit()							= default;
			FileGenerationUnit(FileGenerationUnit const&)	= default;
			FileGenerationUnit(FileGenerationUnit&&)		= default;
			virtual ~FileGenerationUnit()					= default;

			/**
			*	@brief Generate a file based on the @param genResult.
			*
			*	@param out_genResult	Reference to the generation result to fill during file generation.
			*	@param parsingResult	Result of a file parsing used to generate the new file.
			*/
			void							generateFile(FileGenerationResult&		out_genResult,
														 FileParsingResult const&	parsingResult)	noexcept;
	};
}