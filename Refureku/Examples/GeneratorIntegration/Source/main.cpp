#include <iostream>

#include <Kodgen/Misc/Filesystem.h>
#include <Kodgen/Misc/DefaultLogger.h>

#include <RefurekuGenerator/FileParser.h>
#include <RefurekuGenerator/FileGenerator.h>

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

int main()
{
	rfk::FileParser		fileParser;
	rfk::FileGenerator	fileGenerator;

	//Set logger
	kodgen::DefaultLogger logger;

	fileParser.logger = &logger;
	fileGenerator.logger = &logger;

	//current_path() is the working directory
	//It is set to Refureku/Examples/GeneratorIntegration in VS project settings, but not set from CMake,
	//so search in parent directories until we are in GeneratorIntegration
	fs::path generatorIntegrationPath = fs::current_path().make_preferred();

	while (generatorIntegrationPath.stem().string() != "GeneratorIntegration" && !generatorIntegrationPath.empty())
	{
		generatorIntegrationPath = generatorIntegrationPath.parent_path();
	}

	logger.log("Working Directory: " + generatorIntegrationPath.string(), kodgen::ILogger::ELogSeverity::Info);
		
	//Setup generator and parser. Can also load from .toml settings file,
	//but keep in mind that paths must be either absolute, either relative to the WORKING DIRECTORY
	//When launching from the executable, they must be relative to the executable path.
	//In any case, it's much safer to always provide absolute paths.
	fileGenerator.outputDirectory = generatorIntegrationPath / "Include" / "Generated";
	fileGenerator.toParseDirectories.emplace(generatorIntegrationPath / "Include");
	fileGenerator.ignoredDirectories.emplace(generatorIntegrationPath / "Include" / "Generated");

	fileParser.parsingSettings.projectIncludeDirectories.emplace(generatorIntegrationPath.parent_path().parent_path() / "Library" / "Include");

	//User needs to press G to generate headers
	std::string userInput;
		
	logger.log("Press G to (re)generate metadata.", kodgen::ILogger::ELogSeverity::Info);

	while (userInput != "G")
	{
		std::cin >> userInput;
	}

	//Parse
	kodgen::FileGenerationResult genResult = fileGenerator.generateFiles(fileParser, false);

	//Result
	printGenerationResult(logger, genResult);

	return EXIT_SUCCESS;
}