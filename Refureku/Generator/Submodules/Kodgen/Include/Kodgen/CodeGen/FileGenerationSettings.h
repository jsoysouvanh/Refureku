#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>

#include "Kodgen/CodeGen/GeneratedCodeTemplate.h"
#include "Kodgen/Misc/Filesystem.h"

namespace kodgen
{
	struct FileGenerationSettings
	{
		//FileGenerator and FileGenerationUnit can use private members
		friend class FileGenerator;
		friend class FileGenerationUnit;

		private:
			/** All generated code templates usable by this generator. */
			std::unordered_map<std::string,	GeneratedCodeTemplate*>	_generatedCodeTemplates;

			/** Default generated code templates to use when none is specified in entity property parameters. */
			std::unordered_map<EEntityType, GeneratedCodeTemplate*>	_defaultGeneratedCodeTemplates;

		public:
			/** Name of the internally generated header containing empty definitions for entity macros. */
			std::string								entityMacrosFilename	= "EntityMacros.h";

			/** Extension used for generated files. */
			std::string								generatedFilesExtension	= ".kodgen.h";

			/**
			*	Path to the directory all files should be generated (and where existing ones are).
			*	If the existed directory doesn't exist, it will be created if possible.
			*/
			fs::path								outputDirectory;

			/**
			*	Collection of files to parse.
			*	These files will be parsed without any further check if they exist.
			*	/!\ Make sure all added paths use the os preferred syntax (you should call path.make_preferred() before).
			*/
			std::unordered_set<fs::path, PathHash>	toParseFiles;

			/**
			*	Collection of directories containing files to parse.
			*	All directories contained in the given directories will be recursively inspected, except if they are ignored.
			*	All files contained in any parsed directory will be parsed, except if they are ignored or if their extension is not contained in the supportedExtensions.
			*	/!\ Make sure all added paths use the os preferred syntax (you should call path.make_preferred() before).
			*/
			std::unordered_set<fs::path, PathHash>	toParseDirectories;

			/**
			*	Collection of ignored files.
			*	These files will never be parsed (except if they are also part of the includedFiles collection).
			*	/!\ Make sure all added paths use the os preferred syntax (you should call path.make_preferred() before).
			*/
			std::unordered_set<fs::path, PathHash>	ignoredFiles;

			/**
			*	Collection of ignored directories.
			*	All directories contained in the given directories will be ignored, except if they are included.
			*	All files contained in any ignored directory will be ignored, except if they are included.
			*	/!\ Make sure all added paths use the os preferred syntax (you should call path.make_preferred() before).
			*/
			std::unordered_set<fs::path, PathHash>	ignoredDirectories;

			/** Extensions of files which should be considered for parsing. */
			std::unordered_set<std::string>			supportedExtensions;
	};
}