#include <iostream>

#include <Misc/Filesystem.h>

#include "FileParser.h"
#include "FileGenerator.h"

void parseAndGenerate(fs::path workingDirectory)
{
	rfk::FileParser		fileParser;
	rfk::FileGenerator	fileGenerator;

	std::cout << "[WORKING DIRECTORY] " << workingDirectory.string() << std::endl;

	#if KODGEN_DEV

	fs::path includeDir		= (workingDirectory / "Include").make_preferred();
	fs::path generatedDir	= includeDir / "Generated";

	std::cout << "IncludeDir: " << includeDir << std::endl;
	std::cout << "generatedDir: " << generatedDir << std::endl;

	fileGenerator.outputDirectory = generatedDir;
	fileGenerator.toParseDirectories.emplace(includeDir);
	fileGenerator.ignoredDirectories.emplace(generatedDir);

	#endif

	//Load settings
	if (fileGenerator.loadSettings("RefurekuSettings.toml"))
	{
		std::cout << "[LOADED] FileGenerator settings." << std::endl;
	}
	
	if (fileParser.loadSettings("RefurekuSettings.toml"))
	{
		std::cout << "[LOADED] FileParser settings." << std::endl;
	}

	std::cout << "Output directory: " << fileGenerator.outputDirectory << std::endl;

	//Parse
	kodgen::FileGenerationResult genResult = fileGenerator.generateFiles(fileParser, false);

	//Result
	if (genResult.completed)
	{
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
		std::cerr << "Invalid FileGenerator::outputDirectory" << std::endl;
	}
}

int main(int argc, char** argv)
{
	int result = EXIT_SUCCESS;

	fs::path somePath;

	//Use the first argument as working directory if any
	if (argc > 1)
	{
		fs::path workingDirectory = argv[1];

		if (fs::is_directory(workingDirectory))
		{
			parseAndGenerate(std::move(workingDirectory));
		}
		else
		{
			std::cerr << "Provided working directory is not a directory or doesn't exist" << std::endl;
			result = EXIT_FAILURE;
		}
	}
	//Use the current working directory if no argument specified
	else
	{
		parseAndGenerate(fs::current_path());
	}

	return result;
}