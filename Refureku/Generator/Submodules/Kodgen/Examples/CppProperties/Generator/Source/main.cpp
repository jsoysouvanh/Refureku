#include <iostream>

#include <Misc/Filesystem.h>
#include <CodeGen/FileGenerator.h>

#include "CppPropsParser.h"
#include "CppPropsCodeTemplate.h"

int main(int argc, char** argv)
{
	int result = EXIT_SUCCESS;

	if (argc > 1)
	{
		fs::path workingDirectory = argv[1];

		if (fs::is_directory(workingDirectory))
		{
			std::cout << "WORKING DIRECTORY IS: " << workingDirectory.string() << std::endl;

			fs::path includeDirectory	= workingDirectory / "Include";
			fs::path generatedDirectory	= includeDirectory / "Generated";

			CppPropsParser parser;
			kodgen::FileGenerator fileGenerator;

			//Parse WorkingDir/...
			fileGenerator.includedDirectories.emplace(includeDirectory.string());

			//Ignore generated files...
			fileGenerator.ignoredDirectories.emplace(generatedDirectory.string());
			
			//Only parse .h files
			fileGenerator.supportedExtensions.emplace(".h");

			//All generated files will be located in WorkingDir/Include/Generated
			fileGenerator.outputDirectory = generatedDirectory;

			//Generated files will use .myCustomExtension.h extension
			fileGenerator.generatedFilesExtension = ".myCustomExtension.h";

			//Bind the PropertyCodeTemplate name to the CppPropsCodeTemplate class
			fileGenerator.addGeneratedCodeTemplate("PropertyCodeTemplate", new CppPropsCodeTemplate());

			/**
			*	Can specify code template to use by using the MyCustomCodeTemplatePropertyName main property
			*
			*	For example:
			*		class KGClass(MyCustomCodeTemplatePropertyName[PropertyCodeTemplate]) MyClass {};
			*/
			fileGenerator.codeTemplateMainComplexPropertyName = "MyCustomCodeTemplatePropertyName";

			/**
			*	Set a default class template so that we don't have to specify it manually
			*
			*	Now we can simply write:
			*		class KGClass() MyClass {};
			*/
			fileGenerator.setDefaultClassTemplate("PropertyCodeTemplate"); 

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

	return result;
}