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

void parseAndGenerate(fs::path&& exePath, fs::path&& settingsFilePath)
{
	rfk::FileParserFactory<rfk::FileParser>	fileParserFactory;
	rfk::FileGenerationUnit					fileGenerationUnit;
	rfk::FileGenerator						fileGenerator;
	
	//Set logger
	kodgen::DefaultLogger logger;

	fileParserFactory.logger	= &logger;
	fileGenerator.logger		= &logger;

	logger.log("Working Directory: " + fs::current_path().string(), kodgen::ILogger::ELogSeverity::Info);
	
	if (!settingsFilePath.empty())
	{
		//Load settings from settings file
		if (!(fileGenerator.loadSettings(settingsFilePath) && fileParserFactory.loadSettings(settingsFilePath)))
		{
			return;
		}
	}

#if RFK_DEV
		//Specify used compiler
#if defined(__GNUC__)
		fileParserFactory.parsingSettings.setCompilerExeName("g++");
#elif defined(__clang__)
		fileParserFactory.parsingSettings.setCompilerExeName("clang++");
#elif defined(_MSC_VER)
		fileParserFactory.parsingSettings.setCompilerExeName("msvc");
#endif

		printGenerationSetup(logger, fileGenerator, fileParserFactory);
#endif

	//Parse
	kodgen::FileGenerationResult genResult = fileGenerator.generateFiles(fileParserFactory, fileGenerationUnit, false);

	//Result
	printGenerationResult(logger, genResult);
}

/** Can provide the path to the settings file as 1st parameter */
int main(int argc, char** argv)
{
	parseAndGenerate(fs::path(argv[0]).parent_path(), (argc > 1) ? fs::path(argv[1]) : fs::path());

	return EXIT_SUCCESS;
}