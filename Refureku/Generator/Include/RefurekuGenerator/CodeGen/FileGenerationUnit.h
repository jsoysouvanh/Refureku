/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <string>
#include <vector>
#include <functional>	//std::hash

#include <Kodgen/CodeGen/FileGenerationUnit.h>

namespace rfk
{
	class FileGenerationUnit : public kodgen::FileGenerationUnit
	{
		private:
			/** Prefix used to build internal macros. Must match with GeneratedEntityCodeTemplate::internalPrefix. */
			static constexpr char const* const			_internalPrefix		= "__RFK";

			/** Name of the end file macro. */
			static std::string const					_endFileMacroName;

			/** Name of the macro containing all native properties generated code. */
			static std::string const					_nativePropsMacroName;

			/** Class global string hasher. */
			static std::hash<std::string> const			_stringHasher;

			/** List of all namespaces we have generated metadata for. */
			std::vector<kodgen::NamespaceInfo const*>	_generatedNamespaces;

			/** List of all structs/classes we have generated metadata for. */
			std::vector<kodgen::StructClassInfo const*>	_generatedClasses;

			/** List of all enums we have generated metadata for. */
			std::vector<kodgen::EnumInfo const*>		_generatedEnums;

			/** List of all variables we have generated metadata for. */
			std::vector<kodgen::VariableInfo const*>	_generatedVariables;

			/** List of all functions we have generated metadata for. */
			std::vector<kodgen::FunctionInfo const*>	_generatedFunctions;

			/** List of all entities containing native properties. */
			std::vector<kodgen::EntityInfo const*>		_entitiesUsingNativeProperties;

			/**
			*	@brief Write the end file macro
			*
			*	@param file File to write to.
			*/
			void generateEndFileMacro(kodgen::GeneratedFile& file)								const	noexcept;

			/**
			*	@brief Save the entity to _entitiesUsingNativeProperties if it uses at least one native property.
			*	
			*	@param entityInfo Entity containing the properties to save.
			*/
			void saveEntityUsingNativeProperties(kodgen::EntityInfo const& entityInfo)					noexcept;

			/**
			*	@brief Generate code relative to attached native entities.
			*	
			*	@param file				File to write to.
			*	@param parsingResult	Structure containing info about the parsed file.
			*/
			void generateNativePropertiesCode(kodgen::GeneratedFile&			file,
											  kodgen::FileParsingResult const&	parsingResult)	const	noexcept;

		protected:
			virtual void postGenerateFile()																	noexcept override;

			virtual void writeHeader(kodgen::GeneratedFile&				file,
									 kodgen::FileParsingResult const&	parsingResult)				const	noexcept override;

			virtual void writeFooter(kodgen::GeneratedFile&				file,
									 kodgen::FileParsingResult const&	parsingResult)				const	noexcept override;

			virtual bool writeEntityToFile(kodgen::GeneratedFile&		generatedFile,
										   kodgen::EntityInfo const&		entityInfo,
										   kodgen::FileGenerationResult&	out_genResult)					noexcept override;

			virtual bool writeNamespaceToFile(kodgen::GeneratedFile&		generatedFile,
											  kodgen::EntityInfo const&		namespaceInfo,
											  kodgen::FileGenerationResult&	genResult)						noexcept override;

			virtual bool writeStructOrClassToFile(kodgen::GeneratedFile&		generatedFile,
												  kodgen::EntityInfo const&		structClassInfo,
												  kodgen::FileGenerationResult&	genResult)					noexcept override;

			virtual bool writeEnumToFile(kodgen::GeneratedFile&			generatedFile,
										 kodgen::EntityInfo const&		enumInfo,
										 kodgen::FileGenerationResult&	genResult)							noexcept override;

			virtual bool writeVariableToFile(kodgen::GeneratedFile&			generatedFile,
											 kodgen::EntityInfo const&		variableInfo,
											 kodgen::FileGenerationResult&	genResult)						noexcept override;

			virtual bool writeFunctionToFile(kodgen::GeneratedFile&			generatedFile,
											 kodgen::EntityInfo const&		functionInfo,
											 kodgen::FileGenerationResult&	genResult)						noexcept override;

		public:
			FileGenerationUnit()							= default;
			FileGenerationUnit(FileGenerationUnit const&)	= default;
			FileGenerationUnit(FileGenerationUnit&&)		= default;
			virtual ~FileGenerationUnit()					= default;
	};
}