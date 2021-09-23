#include <utility>	//std::forward

#include <Kodgen/Misc/Filesystem.h>
#include <Kodgen/Misc/DefaultLogger.h>
#include <Kodgen/Parsing/FileParser.h>
#include <Kodgen/CodeGen/Macro/MacroCodeGenUnit.h>

#include "RefurekuGenerator/Parsing/FileParser.h"
#include "RefurekuGenerator/CodeGen/CodeGenManager.h"
#include "RefurekuGenerator/CodeGen/MacroCodeGenUnitSettings.h"
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

bool loadSettings(kodgen::ILogger& logger, kodgen::CodeGenManagerSettings& codeGenMgrSettings, kodgen::ParsingSettings& parsingSettings,
				  kodgen::MacroCodeGenUnitSettings& codeGenUnitSettings)
{
	bool result = true;

	fs::path libraryDirectoryPath = getLibraryDirectoryPath();
	fs::path outputDirectory = libraryDirectoryPath / "Include" / "Private" / "Refureku" / "Generated";

	result &= codeGenMgrSettings.addSupportedFileExtension(".h");
	result &= codeGenMgrSettings.addSupportedFileExtension(".hpp");
	result &= codeGenMgrSettings.addToProcessDirectory(libraryDirectoryPath / "Include" / "Private" / "Refureku" / "TypeInfo" / "Properties");
	result &= codeGenMgrSettings.addIgnoredDirectory(outputDirectory);

	result &= codeGenUnitSettings.setOutputDirectory(outputDirectory);
	codeGenUnitSettings.setExportSymbolMacroName("REFUREKU_API");
	codeGenUnitSettings.setInternalSymbolMacroName("REFUREKU_INTERNAL");

	parsingSettings.shouldAbortParsingOnFirstError = true;
	parsingSettings.shouldParseAllEntities = false;
	result &= parsingSettings.addProjectIncludeDirectory(libraryDirectoryPath / "Include" / "Public");
	result &= parsingSettings.addProjectIncludeDirectory(libraryDirectoryPath / "Include" / "Private"); //TODO: Delete this once public API is fully implemented
	result &= parsingSettings.setCompilerExeName("msvc");

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

int main()
{
	kodgen::DefaultLogger logger;

	rfk::FileParser fileParser;
	fileParser.logger = &logger;

	rfk::CodeGenManager codeGenMgr;
	codeGenMgr.logger = &logger;

	kodgen::MacroCodeGenUnit codeGenUnit;
	rfk::MacroCodeGenUnitSettings codeGenUnitSettings;
	codeGenUnit.logger = &logger;
	codeGenUnit.setSettings(codeGenUnitSettings);
	
	rfk::ReflectionCodeGenModule reflectionCodeGenModule;
	codeGenUnit.addModule(reflectionCodeGenModule);

	//Load settings
	logger.log("Working Directory: " + fs::current_path().string(), kodgen::ILogger::ELogSeverity::Info);

	if (loadSettings(logger, codeGenMgr.settings, fileParser.getSettings(), codeGenUnitSettings))
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

	return EXIT_SUCCESS;
}