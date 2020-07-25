#pragma once

#include <string>
#include <vector>

#include <CodeGen/FileGenerator.h>

namespace rfk
{
	class FileGenerator : public kodgen::FileGenerator
	{
		private:
			/** Name of the end file macro. */
			inline static std::string		_endFileMacroName	= "File_GENERATED";
			static constexpr char const*	_internalPrefix		= "__RFK";

			/** List of all namespaces we have generated metadata for. */
			std::vector<kodgen::NamespaceInfo const*>	_generatedNamespaces;

			/** List of all structs/classes we have generated metadata for. */
			std::vector<kodgen::StructClassInfo const*>	_generatedClasses;

			/** List of all enums we have generated metadata for. */
			std::vector<kodgen::EnumInfo const*>		_generatedEnums;

			/**
			*	@brief Write the end file macro
			*
			*	@param file File to write to.
			*/
			void generateEndFileMacro(kodgen::GeneratedFile& file)	const	noexcept;

		protected:
			virtual void postGenerateFile()														noexcept override;

			virtual void writeHeader(kodgen::GeneratedFile&				file,
									 kodgen::FileParsingResult const&	parsingResult) const	noexcept override;
			
			virtual void writeFooter(kodgen::GeneratedFile&				file,
									 kodgen::FileParsingResult const&	parsingResult) const	noexcept override;

			virtual void writeNamespaceToFile(kodgen::GeneratedFile&		generatedFile,
											  kodgen::EntityInfo const&		namespaceInfo,
											  kodgen::FileGenerationResult&	genResult)			noexcept;

			virtual void writeStructOrClassToFile(kodgen::GeneratedFile&		generatedFile,
												  kodgen::EntityInfo const&		structClassInfo,
												  kodgen::FileGenerationResult&	genResult)		noexcept;

			virtual void writeEnumToFile(kodgen::GeneratedFile&			generatedFile,
										 kodgen::EntityInfo const&		enumInfo,
										 kodgen::FileGenerationResult&	genResult)				noexcept;

		public:
			FileGenerator()						noexcept;
			FileGenerator(FileGenerator const&)	= default;
			FileGenerator(FileGenerator&&)		= default;
			virtual ~FileGenerator()			= default;
	};
}