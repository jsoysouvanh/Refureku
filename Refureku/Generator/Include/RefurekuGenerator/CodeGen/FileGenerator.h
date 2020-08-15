/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <string>
#include <vector>

#include <Kodgen/CodeGen/FileGenerator.h>

#include "RefurekuGenerator/CodeGen/GeneratedNamespaceCodeTemplate.h"
#include "RefurekuGenerator/CodeGen/GeneratedClassCodeTemplate.h"
#include "RefurekuGenerator/CodeGen/GeneratedEnumCodeTemplate.h"
#include "RefurekuGenerator/CodeGen/GeneratedVariableCodeTemplate.h"
#include "RefurekuGenerator/CodeGen/GeneratedFunctionCodeTemplate.h"

namespace rfk
{
	class FileGenerator : public kodgen::FileGenerator
	{
		private:
			/** Prefix used to build internal macros. Must match with GeneratedEntityCodeTemplate::internalPrefix. */
			static constexpr char const* const	_internalPrefix		= "__RFK";

			/** Name of the end file macro. */
			static std::string const			_endFileMacroName;

			/** Class global string hasher. */
			static std::hash<std::string> const	_stringHasher;

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

			/** Code templates used by this generator. */
			GeneratedNamespaceCodeTemplate	_namespaceCodeTemplate;
			GeneratedClassCodeTemplate		_classCodeTemplate;
			GeneratedEnumCodeTemplate		_enumCodeTemplate;
			GeneratedVariableCodeTemplate	_variableCodeTemplate;
			GeneratedFunctionCodeTemplate	_functionCodeTemplate;

			/**
			*	@brief Write the end file macro
			*
			*	@param file File to write to.
			*/
			void generateEndFileMacro(kodgen::GeneratedFile& file)	const	noexcept;

		protected:
			virtual void postGenerateFile()																	noexcept override;

			virtual void writeHeader(kodgen::GeneratedFile&				file,
									 kodgen::FileParsingResult const&	parsingResult)				const	noexcept override;
			
			virtual void writeFooter(kodgen::GeneratedFile&				file,
									 kodgen::FileParsingResult const&	parsingResult)				const	noexcept override;

			virtual void writeNamespaceToFile(kodgen::GeneratedFile&		generatedFile,
											  kodgen::EntityInfo const&		namespaceInfo,
											  kodgen::FileGenerationResult&	genResult)						noexcept override;

			virtual void writeStructOrClassToFile(kodgen::GeneratedFile&		generatedFile,
												  kodgen::EntityInfo const&		structClassInfo,
												  kodgen::FileGenerationResult&	genResult)					noexcept override;

			virtual void writeEnumToFile(kodgen::GeneratedFile&			generatedFile,
										 kodgen::EntityInfo const&		enumInfo,
										 kodgen::FileGenerationResult&	genResult)							noexcept override;

			virtual void writeVariableToFile(kodgen::GeneratedFile&			generatedFile,
											 kodgen::EntityInfo const&		variableInfo,
											 kodgen::FileGenerationResult&	genResult)						noexcept override;

			virtual void writeFunctionToFile(kodgen::GeneratedFile&			generatedFile,
											 kodgen::EntityInfo const&		functionInfo,
											 kodgen::FileGenerationResult&	genResult)						noexcept override;

		public:
			FileGenerator()						noexcept;
			FileGenerator(FileGenerator const&)	= default;
			FileGenerator(FileGenerator&&)		= default;
			virtual ~FileGenerator()			= default;
	};
}