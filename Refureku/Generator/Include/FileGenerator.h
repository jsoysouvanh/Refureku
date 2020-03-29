#pragma once

#include "CodeGen/FileGenerator.h"

namespace rfk
{
	class FileGenerator : public kodgen::FileGenerator
	{
		protected:
			virtual void writeHeader(kodgen::GeneratedFile& file, kodgen::ParsingResult const& parsingResult) const noexcept override;
			virtual void writeFooter(kodgen::GeneratedFile& file, kodgen::ParsingResult const& parsingResult) const noexcept override;
	};
}