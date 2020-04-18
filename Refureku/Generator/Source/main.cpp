#include <iostream>

#include <Misc/Filesystem.h>

#include "FileParser.h"
#include "FileGenerator.h"

void printGenerationSetup(rfk::FileParser const& /*fileParser*/, rfk::FileGenerator const& fileGenerator)
{
	//Output dir
	std::cout << "Output directory: " << fileGenerator.outputDirectory << std::endl;

	//ToParseDirs
	std::cout << "Parsed directories:" << std::endl;
	for (fs::path const& path : fileGenerator.toParseDirectories)
	{
		std::cout << "\t" << path << std::endl;
	}

	//IgnoredDirs
	std::cout << "Ignored directories:" << std::endl;
	for (fs::path const& path : fileGenerator.ignoredDirectories)
	{
		std::cout << "\t" << path << std::endl;
	}
}

void printGenerationResult(kodgen::FileGenerationResult const& genResult)
{
	if (genResult.completed)
	{
		std::cout << "[LOG] (Re)generated metadata for " << genResult.parsedFiles.size() << " file(s)." << std::endl;
		std::cout << "[LOG] Metadata of " << genResult.upToDateFiles.size() << " file(s) up-to-date." << std::endl;

		//Errors
		for (kodgen::ParsingError parsingError : genResult.parsingErrors)
		{
			std::cerr << parsingError << std::endl;
		}

		for (kodgen::FileGenerationError fileGenError : genResult.fileGenerationErrors)
		{
			std::cerr << fileGenError << std::endl;
		}
	}
	else
	{
		std::cerr << "Generation failed to complete successfully." << std::endl;
	}
}

void parseAndGenerate(fs::path&& exePath)
{
	rfk::FileParser		fileParser;
	rfk::FileGenerator	fileGenerator;

	fs::path pathToSettingsFile = exePath.make_preferred() / "RefurekuSettings.toml";

	//Load settings
	if (fileGenerator.loadSettings(pathToSettingsFile) && fileParser.loadSettings(pathToSettingsFile))
	{
		std::cout << "[LOADED] FileGenerator settings." << std::endl;
		std::cout << "[LOADED] FileParser settings." << std::endl;

		#if RFK_DEV

		// This part is for travis only
		fs::path includeDir		= fs::current_path() / "Include";
		fs::path generatedDir	= includeDir / "Generated";

		fileGenerator.outputDirectory = generatedDir;
		fileGenerator.toParseDirectories.emplace(includeDir);
		fileGenerator.ignoredDirectories.emplace(generatedDir);

		#endif

		printGenerationSetup(fileParser, fileGenerator);

		//Parse
		kodgen::FileGenerationResult genResult = fileGenerator.generateFiles(fileParser, false);

		//Result
		printGenerationResult(genResult);
	}
	else
	{
		std::cerr << "[ERROR] Failed to load the RefurekuSettings file at " << pathToSettingsFile.string() << std::endl;
	}
}

int main(int /*argc*/, char** argv)
{
	std::cout << "[WORKING DIRECTORY] " << fs::current_path() << std::endl;

	fs::path exeDirectory = fs::path(argv[0]).parent_path();

	parseAndGenerate(std::move(exeDirectory));

	return EXIT_SUCCESS;
}