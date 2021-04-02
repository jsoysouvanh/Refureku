#include <iostream>

#include <Kodgen/Misc/Filesystem.h>
#include <Kodgen/Misc/DefaultLogger.h>

#include "RefurekuGenerator/Parsing/FileParser.h"
#include "RefurekuGenerator/Parsing/FileParserFactory.h"
#include "RefurekuGenerator/CodeGen/FileGenerator.h"
#include "RefurekuGenerator/CodeGen/FileGenerationUnit.h"

void printGenerationSetup(kodgen::ILogger& logger, rfk::FileGenerator const& fileGenerator, kodgen::FileParserFactoryBase const& fileParserFactory)
{
	//Output dir
	logger.log("Output directory: " + kodgen::FilesystemHelpers::sanitizePath(fileGenerator.settings.getOutputDirectory()).string(), kodgen::ILogger::ELogSeverity::Info);

	//ToParseDirs
	logger.log("Parsed directories:", kodgen::ILogger::ELogSeverity::Info);
	for (fs::path const& path : fileGenerator.settings.getToParseDirectories())
	{
		logger.log("\t" + path.string(), kodgen::ILogger::ELogSeverity::Info);
	}

	//IgnoredDirs
	logger.log("Ignored directories:", kodgen::ILogger::ELogSeverity::Info);
	for (fs::path const& path : fileGenerator.settings.getIgnoredDirectories())
	{
		logger.log("\t" + path.string(), kodgen::ILogger::ELogSeverity::Info);
	}

	logger.log("Project include directories:", kodgen::ILogger::ELogSeverity::Info);
	for (fs::path const& path : fileParserFactory.parsingSettings.getProjectIncludeDirectories())
	{
		logger.log("\t" + path.string(), kodgen::ILogger::ELogSeverity::Info);
	}
}

void printGenerationResult(kodgen::ILogger& logger, kodgen::FileGenerationResult const& genResult)
{
	if (genResult.completed)
	{
		logger.log("(Re)generated metadata for " + std::to_string(genResult.parsedFiles.size()) + " file(s) in " + std::to_string(genResult.duration) + " seconds.", kodgen::ILogger::ELogSeverity::Info);
		logger.log("Metadata of " + std::to_string(genResult.upToDateFiles.size()) + " file(s) up-to-date.", kodgen::ILogger::ELogSeverity::Info);

		//Errors
		for (kodgen::ParsingError parsingError : genResult.parsingErrors)
		{
			logger.log(parsingError.toString(), kodgen::ILogger::ELogSeverity::Error);
		}

		for (kodgen::FileGenerationError fileGenError : genResult.fileGenerationErrors)
		{
			logger.log(fileGenError.toString(), kodgen::ILogger::ELogSeverity::Error);
		}
	}
	else
	{
		logger.log("Generation failed to complete successfully.", kodgen::ILogger::ELogSeverity::Error);
	}
}

void parseAndGenerate(fs::path&& exePath)
{
	rfk::FileParserFactory<rfk::FileParser>	fileParserFactory;
	rfk::FileGenerationUnit					fileGenerationUnit;
	rfk::FileGenerator						fileGenerator;
	
	//Set logger
	kodgen::DefaultLogger logger;

	fileParserFactory.logger	= &logger;
	fileGenerator.logger		= &logger;

	fs::path pathToSettingsFile = exePath.make_preferred() / "RefurekuSettings.toml";

	logger.log("Working Directory: " + fs::current_path().string(), kodgen::ILogger::ELogSeverity::Info);

	//Load settings
	if (fileGenerator.loadSettings(pathToSettingsFile) && fileParserFactory.loadSettings(pathToSettingsFile))
	{
#if RFK_DEV
		// This part is for continuous integration system only
		fs::path includeDir			= fs::current_path() / "Include";
		fs::path generatedDir		= includeDir / "Generated";
		fs::path refurekuIncludeDir	= fs::current_path().parent_path() / "Include";

		//Specify used compiler
#if defined(__GNUC__)
		fileParserFactory.parsingSettings.setCompilerExeName("g++");
#elif defined(__clang__)
		fileParserFactory.parsingSettings.setCompilerExeName("clang++");
#elif defined(_MSC_VER)
		fileParserFactory.parsingSettings.setCompilerExeName("msvc");
#endif

		fileGenerator.settings.setOutputDirectory(generatedDir);
		fileGenerator.settings.addToParseDirectory(includeDir);
		fileGenerator.settings.addIgnoredDirectory(generatedDir);
		fileParserFactory.parsingSettings.addProjectIncludeDirectory(refurekuIncludeDir);

		printGenerationSetup(logger, fileGenerator, fileParserFactory);
#endif

		//Parse
		kodgen::FileGenerationResult genResult = fileGenerator.generateFiles(fileParserFactory, fileGenerationUnit, false);

		//Result
		printGenerationResult(logger, genResult);
	}
}

int main(int /* argc */, char** argv)
{
	parseAndGenerate(fs::path(argv[0]).parent_path());

	return EXIT_SUCCESS;
}