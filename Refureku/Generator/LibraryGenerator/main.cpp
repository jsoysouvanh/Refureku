#include <iostream>

#include "Kodgen/Misc/Filesystem.h"
#include "RefurekuGenerator/Parsing/FileParser.h"
#include "RefurekuGenerator/Parsing/FileParserFactory.h"
#include "RefurekuGenerator/CodeGen/FileGenerator.h"
#include "RefurekuGenerator/CodeGen/FileGenerationUnit.h"
#include "Kodgen/Misc/DefaultLogger.h"

int main()
{
	fs::path path = fs::current_path();

	//Rewind until /Refureku directory
	while (path.has_stem() && path.stem() != "Refureku")
	{
		path = path.parent_path();
	}

	path = path / "Refureku" / "Generator" / "LibraryGenerator";

	//----------------------------------------
	rfk::FileParserFactory<rfk::FileParser>	fileParserFactory;
	rfk::FileGenerator						fileGenerator;
	rfk::FileGenerationUnit					fileGenerationUnit;

	kodgen::DefaultLogger logger;
	
	fileParserFactory.logger	= &logger;
	fileGenerator.logger		= &logger;

	if (fileParserFactory.loadSettings(path / "LibraryGenerationSettings.toml") && fileGenerator.loadSettings(path / "LibraryGenerationSettings.toml"))
	{
		kodgen::FileGenerationResult result = fileGenerator.generateFiles(fileParserFactory, fileGenerationUnit, true);

		for (kodgen::ParsingError const& error : result.parsingErrors)
		{
			logger.log(error.toString(), kodgen::ILogger::ELogSeverity::Error);
		}

		for (kodgen::FileGenerationError const& error : result.fileGenerationErrors)
		{
			logger.log(error.toString(), kodgen::ILogger::ELogSeverity::Error);
		}
	}

	return EXIT_SUCCESS;
}