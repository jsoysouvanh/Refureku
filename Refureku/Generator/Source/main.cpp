#include <utility>	//std::forward

#include <Kodgen/Misc/DefaultLogger.h>
#include <Kodgen/CodeGen/Macro/MacroCodeGenUnit.h>
#include <Kodgen/CodeGen/CodeGenManager.h>
#include <Kodgen/CodeGen/Macro/MacroCodeGenUnitSettings.h>

#include "RefurekuGenerator/Parsing/FileParser.h"
#include "RefurekuGenerator/CodeGen/ReflectionCodeGenModule.h"

void printGenerationSetup(kodgen::ILogger& logger, kodgen::CodeGenManagerSettings const& codeGenMgrSettings, kodgen::ParsingSettings const& parsingSettings,
						  kodgen::MacroCodeGenUnitSettings const& codeGenUnitSettings)
{
	//Output dir
	logger.log("Output directory: " + kodgen::FilesystemHelpers::sanitizePath(codeGenUnitSettings.getOutputDirectory()).string());

	//ToParseDirs
	logger.log("Parsed directories:");
	for (fs::path const& path : codeGenMgrSettings.getToProcessDirectories())
	{
		logger.log("\t" + path.string());
	}

	//IgnoredDirs
	logger.log("Ignored directories:");
	for (fs::path const& path : codeGenMgrSettings.getIgnoredDirectories())
	{
		logger.log("\t" + path.string());
	}

	//Project include dirs
	logger.log("Project include directories:");
	for (fs::path const& path : parsingSettings.getProjectIncludeDirectories())
	{
		logger.log("\t" + path.string());
	}
}

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
	if (parsingSettings.setCompilerExeName("g++"))
	{
		logger.log("Set compiler: g++");
	}
	else
	{
		logger.log("Failed to set compiler: g++");
	}
#elif defined(__clang__)
	if (parsingSettings.setCompilerExeName("clang++"))
	{
		logger.log("Set compiler: clang++");
	}
	else
	{
		logger.log("Failed to set compiler: clang++");
	}
#elif defined(_MSC_VER)
	if (parsingSettings.setCompilerExeName("msvc"))
	{
		logger.log("Set compiler: msvc");
	}
	else
	{
		logger.log("Failed to set compiler: msvc");
	}
#endif

#endif

	printGenerationSetup(logger, codeGenMgrSettings, parsingSettings, codeGenUnitSettings);

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

bool parseAndGenerate(fs::path&& settingsFilePath)
{
	kodgen::DefaultLogger logger;

	rfk::FileParser fileParser;
	fileParser.logger = &logger;

	kodgen::CodeGenManager codeGenMgr;
	codeGenMgr.logger = &logger;

	kodgen::MacroCodeGenUnitSettings codeGenUnitSettings;
	kodgen::MacroCodeGenUnit codeGenUnit;
	codeGenUnit.logger = &logger;
	codeGenUnit.setSettings(codeGenUnitSettings);
	
	rfk::ReflectionCodeGenModule reflectionCodeGenModule;	
	codeGenUnit.addModule(reflectionCodeGenModule);

	//Load settings
	logger.log("Working Directory: " + fs::current_path().string(), kodgen::ILogger::ELogSeverity::Info);
	
	//loadSettings(logger, codeGenMgr.settings, fileParser.getSettings(), codeGenUnitSettings, "RefurekuTestsSettings.toml"); //For tests
	loadSettings(logger, codeGenMgr.settings, fileParser.getSettings(), codeGenUnitSettings, std::forward<fs::path>(settingsFilePath));

	//Parse
	kodgen::CodeGenResult genResult = codeGenMgr.run(fileParser, codeGenUnit, false);

	//Result
	printGenerationResult(logger, genResult);

	return genResult.completed;
}

/** Can provide the path to the settings file as 1st parameter */
int main(int argc, char** argv)
{
	return !parseAndGenerate((argc > 1) ? fs::path(argv[1]) : fs::path());
}