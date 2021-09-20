#include <utility>	//std::forward

#include <Kodgen/Misc/Filesystem.h>
#include <Kodgen/Misc/DefaultLogger.h>
#include <Kodgen/Parsing/FileParser.h>
#include <Kodgen/CodeGen/Macro/MacroCodeGenUnit.h>

#include "RefurekuGenerator/Parsing/FileParser.h"
#include "RefurekuGenerator/CodeGen/CodeGenManager.h"
#include "RefurekuGenerator/CodeGen/MacroCodeGenUnitSettings.h"
#include "RefurekuGenerator/CodeGen/ReflectionCodeGenModule.h"

bool loadSettings(kodgen::ILogger& logger, kodgen::CodeGenManagerSettings& codeGenMgrSettings, kodgen::ParsingSettings& parsingSettings,
				  kodgen::MacroCodeGenUnitSettings& codeGenUnitSettings, fs::path&& settingsFilePath)
{
	if (!settingsFilePath.empty())
	{
		//Load settings from settings file
		//All settings are localized in a single file for ease of use
		if (!parsingSettings.loadFromFile(settingsFilePath, &logger))
		{
			return false;
		}
		else if (!codeGenMgrSettings.loadFromFile(settingsFilePath, &logger))
		{
			return false;
		}
		else if (!codeGenUnitSettings.loadFromFile(settingsFilePath, &logger))
		{
			return false;
		}
	}

#if RFK_DEV
	//Specify used compiler
#if defined(__GNUC__)
	parsingSettings.setCompilerExeName("g++");
#elif defined(__clang__)
	parsingSettings.setCompilerExeName("clang++");
#elif defined(_MSC_VER)
	parsingSettings.setCompilerExeName("msvc");
#endif

#endif

	return true;
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
	fs::path path = fs::current_path();

	//Rewind until /Refureku directory
	while (path.has_stem() && path.stem() != "Refureku")
	{
		path = path.parent_path();
	}

	path = path / "Refureku" / "Generator" / "LibraryGenerator";

	//----------------------------------------
	kodgen::DefaultLogger logger;

	rfk::FileParser fileParser;
	fileParser.logger = &logger;

	rfk::CodeGenManager codeGenMgr;
	codeGenMgr.logger = &logger;

	kodgen::MacroCodeGenUnit codeGenUnit;
	rfk::MacroCodeGenUnitSettings codeGenUnitSettings;
	codeGenUnit.logger = &logger;
	codeGenUnit.setSettings(codeGenUnitSettings);
	
	rfk::ReflectionCodeGenModule reflectionCodeGenModule("REFUREKU_API", "REFUREKU_INTERNAL");
	codeGenUnit.addModule(reflectionCodeGenModule);

	//Load settings
	logger.log("Working Directory: " + fs::current_path().string(), kodgen::ILogger::ELogSeverity::Info);

	loadSettings(logger, codeGenMgr.settings, fileParser.getSettings(), codeGenUnitSettings, std::forward<fs::path>(path / "LibraryGenerationSettings.toml"));

	//Parse
	kodgen::CodeGenResult genResult = codeGenMgr.run(fileParser, codeGenUnit, true);

	//Result
	printGenerationResult(logger, genResult);

	return EXIT_SUCCESS;
}