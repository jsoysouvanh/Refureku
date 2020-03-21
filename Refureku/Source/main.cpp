#include <iostream>

#include <Misc/Filesystem.h>
#include <CodeGen/FileGenerator.h>

#include "FileParser.h"
#include "GeneratedCodeTemplate.h"

int main(int argc, char** argv)
{
	int result = EXIT_SUCCESS;

	fs::path somePath;

	if (argc > 1)
	{
		fs::path workingDirectory = argv[1];

		if (fs::is_directory(workingDirectory))
		{
			std::cout << "WORKING DIRECTORY IS: " << workingDirectory.string() << std::endl;

			fs::path includeDirectory	= workingDirectory / "Include";
			fs::path generatedDirectory	= includeDirectory / "Generated";

			refureku::FileParser	parser;
			kodgen::FileGenerator	fileGenerator;

			//Parse WorkingDir/...
			fileGenerator.includedDirectories.emplace(includeDirectory.string());

			//Ignore generated files...
			fileGenerator.ignoredDirectories.emplace(generatedDirectory.string());

			//Only parse .h files
			fileGenerator.supportedExtensions.emplace(".h");

			//All generated files will be located in WorkingDir/Include/Generated
			fileGenerator.outputDirectory = generatedDirectory;

			//Generated files will use .myCustomExtension.h extension
			fileGenerator.generatedFilesExtension = ".refureku.h";

			//Bind "Refureku" to the GeneratedCodeTemplate class
			fileGenerator.addGeneratedCodeTemplate("Refureku", new refureku::GeneratedCodeTemplate());

			/** class Class(CodeTemplate[Refureku]) MyClass {}; */
			fileGenerator.codeTemplateMainComplexPropertyName = "CodeTemplate";

			/**
			*	class Class() MyClass {};
			*/
			fileGenerator.setDefaultClassTemplate("Refureku"); 

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
		else
		{
			std::cerr << "Provided working directory is not a directory or doesn't exist" << std::endl;
			result = EXIT_FAILURE;
		}
	}
	else
	{
		std::cerr << "No working directory provided as first program argument" << std::endl;
		result = EXIT_FAILURE;
	}
}