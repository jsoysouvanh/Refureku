#pragma once

#include <CodeGen/FileGenerator.h>

namespace rfk
{
	class FileGenerator : public kodgen::FileGenerator
	{
		private:
			

		protected:
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