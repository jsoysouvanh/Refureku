#include <iostream>

#include <Misc/Filesystem.h>

#include "FileParser.h"
#include "GeneratedClassCodeTemplate.h"
#include "GeneratedEnumCodeTemplate.h"
#include "FileGenerator.h"

void parseAndGenerate(fs::path workingDirectory)
{
	std::cout << "[WORKING DIRECTORY] " << workingDirectory.string() << std::endl;

	fs::path includeDirectory	= workingDirectory / "Include";
	fs::path generatedDirectory	= includeDirectory / "Generated";

	rfk::FileParser		parser;
	rfk::FileGenerator	fileGenerator;

	//Parse WorkingDir/...
	fileGenerator.includedDirectories.emplace(includeDirectory.string());

	//Ignore generated files...
	fileGenerator.ignoredDirectories.emplace(generatedDirectory.string());

	//All generated files will be located in WorkingDir/Include/Generated
	fileGenerator.outputDirectory = generatedDirectory;

	//Bind name -> templates
	fileGenerator.addGeneratedCodeTemplate("RefurekuClass", new rfk::GeneratedClassCodeTemplate());
	fileGenerator.addGeneratedCodeTemplate("RefurekuEnum", new rfk::GeneratedEnumCodeTemplate());

	/**	class RFKClass() MyClass {}; enum [class] RFKEnum() {}; */
	fileGenerator.setDefaultClassTemplate("RefurekuClass"); 
	fileGenerator.setDefaultEnumTemplate("RefurekuEnum");

	kodgen::FileGenerationResult genResult = fileGenerator.generateFiles(parser, false);

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