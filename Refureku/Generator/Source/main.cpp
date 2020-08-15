#include <iostream>

#include <Kodgen/Misc/Filesystem.h>
#include <Kodgen/Misc/DefaultLogger.h>

#include "RefurekuGenerator/CodeGen/FileParser.h"
#include "RefurekuGenerator/CodeGen/FileGenerator.h"

void printGenerationSetup(kodgen::ILogger& logger, rfk::FileParser const& /*fileParser*/, rfk::FileGenerator const& fileGenerator)
{
	//Output dir
	logger.log("Output directory: " + fileGenerator.outputDirectory.string(), kodgen::ILogger::ELogSeverity::Info);

	//ToParseDirs
	logger.log("Parsed directories:", kodgen::ILogger::ELogSeverity::Info);
	for (fs::path const& path : fileGenerator.toParseDirectories)
	{
		logger.log("\t" + path.string(), kodgen::ILogger::ELogSeverity::Info);
	}

	//IgnoredDirs
	logger.log("Ignored directories:", kodgen::ILogger::ELogSeverity::Info);
	for (fs::path const& path : fileGenerator.ignoredDirectories)
	{
		logger.log("\t" + path.string(), kodgen::ILogger::ELogSeverity::Info);
	}
}

void printGenerationResult(kodgen::ILogger& logger, kodgen::FileGenerationResult const& genResult)
{
	if (genResult.completed)
	{
		logger.log("(Re)generated metadata for " + std::to_string(genResult.parsedFiles.size()) + " file(s).", kodgen::ILogger::ELogSeverity::Info);
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
	rfk::FileParser		fileParser;
	rfk::FileGenerator	fileGenerator;

	//Set logger
	kodgen::DefaultLogger logger;

	fileParser.logger		= &logger;
	fileGenerator.logger	= &logger;

	fs::path pathToSettingsFile = exePath.make_preferred() / "RefurekuSettings.toml";

	logger.log("Working Directory: " + fs::current_path().string(), kodgen::ILogger::ELogSeverity::Info);

	//Load settings
	if (fileGenerator.loadSettings(pathToSettingsFile) && fileParser.loadSettings(pathToSettingsFile))
	{
		logger.log("Loaded FileGenerator settings.", kodgen::ILogger::ELogSeverity::Info);
		logger.log("Loaded FileParser settings.", kodgen::ILogger::ELogSeverity::Info);

		#if RFK_DEV

		// This part is for travis only
		fs::path includeDir		= fs::current_path() / "Include";
		fs::path generatedDir	= includeDir / "Generated";

		fileGenerator.outputDirectory = generatedDir;
		fileGenerator.toParseDirectories.emplace(includeDir);
		fileGenerator.ignoredDirectories.emplace(generatedDir);

		#endif

		printGenerationSetup(logger, fileParser, fileGenerator);

		//Parse
		kodgen::FileGenerationResult genResult = fileGenerator.generateFiles(fileParser, false);

		//Result
		printGenerationResult(logger, genResult);
	}
	else
	{
		logger.log("Failed to load the RefurekuSettings file at " + pathToSettingsFile.string(), kodgen::ILogger::ELogSeverity::Error);
	}
}

int main(int /*argc*/, char** argv)
{
	fs::path exeDirectory = fs::path(argv[0]).parent_path();

	parseAndGenerate(std::move(exeDirectory));

	return EXIT_SUCCESS;
}