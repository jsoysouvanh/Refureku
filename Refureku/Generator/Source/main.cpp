#include <iostream>

#include <Kodgen/Misc/Filesystem.h>
#include <Kodgen/Misc/DefaultLogger.h>
#include <Kodgen/Parsing/FileParser.h>
#include <Kodgen/CodeGen/Macro/MacroCodeGenUnit.h>

#include "RefurekuGenerator/CodeGen/CodeGenManager.h"
#include "RefurekuGenerator/CodeGen/MacroCodeGenUnitSettings.h"

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

void parseAndGenerate(fs::path&& exePath, fs::path&& settingsFilePath)
{
	kodgen::DefaultLogger logger;

	kodgen::FileParser fileParser;
	fileParser.logger = &logger;

	rfk::CodeGenManager codeGenMgr;
	codeGenMgr.logger = &logger;

	rfk::MacroCodeGenUnitSettings codeGenUnitSettings;
	kodgen::MacroCodeGenUnit codeGenUnit;
	codeGenUnit.logger = &logger;
	codeGenUnit.setSettings(codeGenUnitSettings);

	//Load settings
	logger.log("Working Directory: " + fs::current_path().string(), kodgen::ILogger::ELogSeverity::Info);
	
	if (!settingsFilePath.empty())
	{
		//Load settings from settings file
		//All settings are localized in a single file for ease of use
		if (!fileParser.getSettings().loadFromFile(settingsFilePath) || !codeGenMgr.settings.loadFromFile(settingsFilePath) || !codeGenUnitSettings.loadFromFile(settingsFilePath))
		{
			return;
		}
	}
	
#if RFK_DEV
		//Specify used compiler
#if defined(__GNUC__)
		fileParser.getSettings().setCompilerExeName("g++");
#elif defined(__clang__)
		fileParser.getSettings().setCompilerExeName("clang++");
#elif defined(_MSC_VER)
		fileParser.getSettings().setCompilerExeName("msvc");
#endif

		printGenerationSetup(logger, codeGenMgr.settings, fileParser.getSettings(), codeGenUnitSettings);
#endif

	//Parse
	kodgen::CodeGenResult genResult = codeGenMgr.run(fileParser, codeGenUnit, false);

	//Result
	printGenerationResult(logger, genResult);
}

/** Can provide the path to the settings file as 1st parameter */
int main(int argc, char** argv)
{
	parseAndGenerate(fs::path(argv[0]).parent_path(), (argc > 1) ? fs::path(argv[1]) : fs::path());

	return EXIT_SUCCESS;
}