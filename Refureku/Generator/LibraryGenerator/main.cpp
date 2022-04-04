#include <utility>	//std::forward
#include <vector>

#include <Kodgen/Misc/Filesystem.h>
#include <Kodgen/Misc/DefaultLogger.h>
#include <Kodgen/Parsing/FileParser.h>
#include <Kodgen/CodeGen/CodeGenManager.h>
#include <Kodgen/CodeGen/Macro/MacroCodeGenUnit.h>
#include <Kodgen/CodeGen/Macro/MacroCodeGenUnitSettings.h>

#include "RefurekuGenerator/Parsing/FileParser.h"

#include "RefurekuGenerator/CodeGen/ReflectionCodeGenModule.h"

fs::path getLibraryDirectoryPath()
{
	fs::path path = fs::current_path();

	//Rewind until /Refureku directory
	while (path.has_stem() && path.stem() != "Refureku")
	{
		path = path.parent_path();
	}

	return path / "Refureku" / "Library";
}

bool loadSettings(kodgen::CodeGenManagerSettings& codeGenMgrSettings, kodgen::ParsingSettings& parsingSettings,
				  kodgen::MacroCodeGenUnitSettings& codeGenUnitSettings, fs::path outputDirectory)
{
	bool result = true;

	fs::path libraryDirectoryPath = getLibraryDirectoryPath();

	result &= codeGenMgrSettings.addSupportedFileExtension(".h");
	result &= codeGenMgrSettings.addSupportedFileExtension(".hpp");
	codeGenMgrSettings.addToProcessDirectory(libraryDirectoryPath / "Include" / "Public" / "Refureku" / "Properties");
	codeGenMgrSettings.addIgnoredDirectory(outputDirectory);

	result &= codeGenUnitSettings.setOutputDirectory(outputDirectory);
	codeGenUnitSettings.setGeneratedHeaderFileNamePattern("##FILENAME##.rfkh.h");
	codeGenUnitSettings.setGeneratedSourceFileNamePattern("##FILENAME##.rfks.h");
	codeGenUnitSettings.setClassFooterMacroPattern("##CLASSFULLNAME##_GENERATED");
	codeGenUnitSettings.setHeaderFileFooterMacroPattern("File_##FILENAME##_GENERATED");
	codeGenUnitSettings.setExportSymbolMacroName("REFUREKU_API");
	//codeGenUnitSettings.setInternalSymbolMacroName("REFUREKU_INTERNAL");

	parsingSettings.cppVersion = kodgen::ECppVersion::Cpp17;
	parsingSettings.shouldAbortParsingOnFirstError = true;
	parsingSettings.shouldParseAllNamespaces = false;
	parsingSettings.shouldParseAllClasses = false;
	parsingSettings.shouldParseAllStructs = false;
	parsingSettings.shouldParseAllVariables = false;
	parsingSettings.shouldParseAllFields = false;
	parsingSettings.shouldParseAllFunctions = false;
	parsingSettings.shouldParseAllMethods = false;
	parsingSettings.shouldParseAllEnums = false;
	parsingSettings.shouldParseAllEnumValues = true;

	parsingSettings.addProjectIncludeDirectory(libraryDirectoryPath / "Include" / "Public");
	result &= parsingSettings.setCompilerExeName("clang++");

	parsingSettings.propertyParsingSettings.namespaceMacroName	= "RFKNamespace";
	parsingSettings.propertyParsingSettings.classMacroName		= "RFKClass";
	parsingSettings.propertyParsingSettings.structMacroName		= "RFKStruct";
	parsingSettings.propertyParsingSettings.variableMacroName	= "RFKVariable";
	parsingSettings.propertyParsingSettings.fieldMacroName		= "RFKField";
	parsingSettings.propertyParsingSettings.functionMacroName	= "RFKFunction";
	parsingSettings.propertyParsingSettings.methodMacroName		= "RFKMethod";
	parsingSettings.propertyParsingSettings.enumMacroName		= "RFKEnum";
	parsingSettings.propertyParsingSettings.enumValueMacroName	= "RFKEnumVal";

	return result;
}

void printGenerationResult(kodgen::ILogger& logger, kodgen::CodeGenResult const& genResult)
{
	if (genResult.completed)
	{
		logger.log("(Re)generated metadata for " + std::to_string(genResult.parsedFiles.size()) + " file(s) in " + std::to_string(genResult.duration) + " seconds.", kodgen::ILogger::ELogSeverity::Info);
		logger.log("Metadata of " + std::to_string(genResult.upToDateFiles.size()) + " file(s) up-to-date.", kodgen::ILogger::ELogSeverity::Info);
	}
	else
	{
		logger.log("Generation failed to complete successfully.", kodgen::ILogger::ELogSeverity::Error);
	}
}

void runForInternalDirectory(kodgen::ILogger& logger, kodgen::CodeGenManager& codeGenMgr, rfk::FileParser& fileParser,
							kodgen::MacroCodeGenUnit& codeGenUnit, kodgen::MacroCodeGenUnitSettings& codeGenUnitSettings)
{
	logger.log("Run for Internal directory.");
	if (loadSettings(codeGenMgr.settings, fileParser.getSettings(), codeGenUnitSettings, getLibraryDirectoryPath() / "Include" / "Internal" / "Refureku" / "Generated"))
	{
		//Parse
		kodgen::CodeGenResult genResult = codeGenMgr.run(fileParser, codeGenUnit, true);

		//Result
		printGenerationResult(logger, genResult);
	}
	else
	{
		logger.log("Settings loading failed.", kodgen::ILogger::ELogSeverity::Error);
	}
}

void runForPublicDirectory(kodgen::ILogger& logger, kodgen::CodeGenManager& codeGenMgr, rfk::FileParser& fileParser,
						   kodgen::MacroCodeGenUnit& codeGenUnit, kodgen::MacroCodeGenUnitSettings& codeGenUnitSettings)
{
	logger.log("Run for Public directory.");
	
	fs::path outputDirectory = getLibraryDirectoryPath() / "Include" / "Public" / "Refureku" / "Generated";
	if (loadSettings(codeGenMgr.settings, fileParser.getSettings(), codeGenUnitSettings, outputDirectory))
	{
		//Parse
		kodgen::CodeGenResult genResult = codeGenMgr.run(fileParser, codeGenUnit, true);

		//Result
		printGenerationResult(logger, genResult);
	}
	else
	{
		logger.log("Settings loading failed.", kodgen::ILogger::ELogSeverity::Error);
	}

	//Delete all generated source files from the output directory since they are only needed in the private one
	std::vector<fs::path> toDelete;
	for (fs::recursive_directory_iterator directoryIt = fs::recursive_directory_iterator(outputDirectory, fs::directory_options::follow_directory_symlink); directoryIt != fs::recursive_directory_iterator(); directoryIt++)
	{
		fs::directory_entry entry = *directoryIt;

		if (entry.is_regular_file())
		{
			fs::path filePath = entry.path();
			fs::path stem = filePath.stem();

			if (stem.has_extension() && stem.extension() == ".rfks")
			{
				fs::remove(filePath);
				logger.log("Remove file: " + filePath.string());
			}
		}
	}
}

int main()
{
	kodgen::DefaultLogger logger;

	rfk::FileParser fileParser;
	fileParser.logger = &logger;

	kodgen::CodeGenManager codeGenMgr;
	codeGenMgr.logger = &logger;

	kodgen::MacroCodeGenUnit codeGenUnit;
	kodgen::MacroCodeGenUnitSettings codeGenUnitSettings;
	codeGenUnit.logger = &logger;
	codeGenUnit.setSettings(codeGenUnitSettings);
	
	rfk::ReflectionCodeGenModule reflectionCodeGenModule;
	codeGenUnit.addModule(reflectionCodeGenModule);

	//Load settings
	logger.log("Working Directory: " + fs::current_path().string(), kodgen::ILogger::ELogSeverity::Info);

	runForInternalDirectory(logger, codeGenMgr, fileParser, codeGenUnit, codeGenUnitSettings);
	runForPublicDirectory(logger, codeGenMgr, fileParser, codeGenUnit, codeGenUnitSettings);

	return EXIT_SUCCESS;
}