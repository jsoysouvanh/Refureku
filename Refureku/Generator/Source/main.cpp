#include <iostream>

#include <Kodgen/Misc/Filesystem.h>
#include <Kodgen/Misc/DefaultLogger.h>

#include "RefurekuGenerator/Parsing/FileParserFactory.h"
#include "RefurekuGenerator/CodeGen/FileGenerator.h"
#include "RefurekuGenerator/CodeGen/FileGenerationUnit.h"

void printGenerationSetup(kodgen::ILogger& logger, rfk::FileGenerator const& fileGenerator, rfk::FileParserFactory const& fileParserFactory)
{
	//Output dir
	logger.log("Output directory: " + fileGenerator.settings.outputDirectory.string(), kodgen::ILogger::ELogSeverity::Info);

	//ToParseDirs
	logger.log("Parsed directories:", kodgen::ILogger::ELogSeverity::Info);
	for (fs::path const& path : fileGenerator.settings.toParseDirectories)
	{
		logger.log("\t" + path.string(), kodgen::ILogger::ELogSeverity::Info);
	}

	//IgnoredDirs
	logger.log("Ignored directories:", kodgen::ILogger::ELogSeverity::Info);
	for (fs::path const& path : fileGenerator.settings.ignoredDirectories)
	{
		logger.log("\t" + path.string(), kodgen::ILogger::ELogSeverity::Info);
	}

	logger.log("Project include directories:", kodgen::ILogger::ELogSeverity::Info);
	for (fs::path const& path : fileParserFactory.parsingSettings.projectIncludeDirectories)
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
	rfk::FileParserFactory	fileParserFactory;
	rfk::FileGenerationUnit fileGenerationUnit;
	rfk::FileGenerator		fileGenerator;
	
	//Set logger
	kodgen::DefaultLogger logger;

	fileParserFactory.logger	= &logger;
	fileGenerator.logger		= &logger;

	fs::path pathToSettingsFile = exePath.make_preferred() / "RefurekuSettings.toml";

	logger.log("Working Directory: " + fs::current_path().string(), kodgen::ILogger::ELogSeverity::Info);

	//Load settings
	if (fileGenerator.loadSettings(pathToSettingsFile) && fileParserFactory.loadSettings(pathToSettingsFile))
	{
		logger.log("Loaded FileGenerator settings.", kodgen::ILogger::ELogSeverity::Info);
		logger.log("Loaded FileParser settings.", kodgen::ILogger::ELogSeverity::Info);
		
#if RFK_DEV
		// This part is for travis only
		fs::path includeDir			= fs::current_path() / "Include";
		fs::path generatedDir		= includeDir / "Generated";
		fs::path refurekuIncludeDir	= fs::current_path().parent_path() / "Include";

		//Specify used compiler
#if defined(__GNUC__)
		fileParserFactory.parsingSettings.compilerExeName = "g++";
#elif defined(__clang__)
		fileParserFactory.parsingSettings.compilerExeName = "clang++";
#elif defined(_MSC_VER)
		fileParserFactory.parsingSettings.compilerExeName = "msvc";
#endif

		fileGenerator.settings.outputDirectory = generatedDir;
		fileGenerator.settings.toParseDirectories.emplace(includeDir);
		fileGenerator.settings.ignoredDirectories.emplace(generatedDir);
		fileParserFactory.parsingSettings.projectIncludeDirectories.emplace(refurekuIncludeDir);
#endif

		printGenerationSetup(logger, fileGenerator, fileParserFactory);

		//Parse
		kodgen::FileGenerationResult genResult = fileGenerator.generateFiles(fileParserFactory, fileGenerationUnit, false);

		//Result
		printGenerationResult(logger, genResult);
	}
	else
	{
		logger.log("Failed to load the RefurekuSettings file at " + pathToSettingsFile.string(), kodgen::ILogger::ELogSeverity::Error);
	}
}

int main(int /* argc */, char** argv)
{
	parseAndGenerate(fs::path(argv[0]).parent_path());

	return EXIT_SUCCESS;
}