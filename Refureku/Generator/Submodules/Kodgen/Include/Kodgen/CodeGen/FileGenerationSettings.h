/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>

#include "Kodgen/CodeGen/GeneratedCodeTemplate.h"
#include "Kodgen/Misc/Filesystem.h"

namespace kodgen
{
	class FileGenerationSettings
	{
		//FileGenerator and FileGenerationUnit can use private members
		friend class FileGenerator;
		friend class FileGenerationUnit;

		private:
			/** All generated code templates usable by this generator. */
			std::unordered_map<std::string,	GeneratedCodeTemplate*>	_generatedCodeTemplates;

			/** Default generated code templates to use when none is specified in entity property parameters. */
			std::unordered_map<EEntityType, GeneratedCodeTemplate*>	_defaultGeneratedCodeTemplates;

			/**
			*	Collection of files to parse.
			*	These files will be parsed without any further check if they exist.
			*	/!\ Make sure all added paths use the os preferred syntax (you should call path.make_preferred() before).
			*/
			std::unordered_set<fs::path, PathHash>					_toParseFiles;

			/**
			*	Collection of directories containing files to parse.
			*	All directories contained in the given directories will be recursively inspected, except if they are ignored.
			*	All files contained in any parsed directory will be parsed, except if they are ignored or if their extension is not contained in the supportedExtensions.
			*	/!\ Make sure all added paths use the os preferred syntax (you should call path.make_preferred() before).
			*/
			std::unordered_set<fs::path, PathHash>					_toParseDirectories;

			/**
			*	Collection of ignored files.
			*	These files will never be parsed (except if they are also part of the includedFiles collection).
			*	/!\ Make sure all added paths use the os preferred syntax (you should call path.make_preferred() before).
			*/
			std::unordered_set<fs::path, PathHash>					_ignoredFiles;

			/**
			*	Collection of ignored directories.
			*	All directories contained in the given directories will be ignored, except if they are included.
			*	All files contained in any ignored directory will be ignored, except if they are included.
			*	/!\ Make sure all added paths use the os preferred syntax (you should call path.make_preferred() before).
			*/
			std::unordered_set<fs::path, PathHash>					_ignoredDirectories;

			/**
			*	Path to the directory in which all files should be generated (and where existing ones are).
			*	If the output directory doesn't exist, it will be created if possible.
			*/
			fs::path												_outputDirectory;

		public:
			/** Name of the internally generated header containing empty definitions for entity macros. */
			std::string								entityMacrosFilename	= "EntityMacros.h";

			/** Extension used for generated files. */
			std::string								generatedFilesExtension	= ".kodgen.h";

			/** Extensions of files which should be considered for parsing. */
			std::unordered_set<std::string>			supportedExtensions;

			FileGenerationSettings()								= default;
			FileGenerationSettings(FileGenerationSettings const&)	= default;
			FileGenerationSettings(FileGenerationSettings&&)		= default;
			~FileGenerationSettings()								= default;

			/**
			*	@brief	Setter for _outputDirectory.
			*			If the path exists check that it is a directory.
			*			Sanitize the provided path before setting.
			*	
			*	@param outputDirectory New output directory path.
			*
			*	@return true if the outputDirectory has been updated, else false.
			*/
			bool setOutputDirectory(fs::path outputDirectory)										noexcept;

			/**
			*	@brief	Add a file to the list of parsed files.
			*			If the path is invalid, doesn't exist, is not a file, or is already in the list, abort the operation.
			*	
			*	@param path Path to the file to add.
			*	
			*	@return true if the path has been added successfuly, else false.
			*/
			bool addToParseFile(fs::path const& path)												noexcept;

			/**
			*	@brief	Add a directory to the list of parsed directories.
			*			If the path is invalid, doesn't exist, is not a directory, or is already in the list, abort the operation.
			*	
			*	@param path Path to the directory to add.
			*	
			*	@return true if the path has been added successfuly, else false.
			*/
			bool addToParseDirectory(fs::path const& path)											noexcept;

			/**
			*	@brief	Add a file to the list of ignored files.
			*			If the path is invalid, doesn't exist, is not a file, or is already in the list, abort the operation.
			*	
			*	@param path Path to the file to add.
			*	
			*	@return true if the path has been added successfuly, else false.
			*/
			bool addIgnoredFile(fs::path const& path)												noexcept;

			/**
			*	@brief	Add a directory to the list of ignored directories.
			*			If the path is invalid, doesn't exist, is not a directory, or is already in the list, abort the operation.
			*	
			*	@param path Path to the directory to add.
			*	
			*	@return true if the path has been added successfuly, else false.
			*/
			bool addIgnoredDirectory(fs::path const& path)											noexcept;

			/**
			*	@brief Remove a file from the list of parsed files.
			*	
			*	@param path Path to the file to remove.
			*/
			void removeToParseFile(fs::path const& path)											noexcept;

			/**
			*	@brief Remove a directory from the list of parsed directories.
			*	
			*	@param path Path to the directory to remove.
			*/
			void removeToParseDirectory(fs::path const& path)										noexcept;

			/**
			*	@brief Remove a file from the list of ignored files.
			*	
			*	@param path Path to the file to remove.
			*/
			void removeIgnoredFile(fs::path const& path)											noexcept;
			
			/**
			*	@brief Remove a directory from the list of ignored directories.
			*	
			*	@param path Path to the directory to remove.
			*/
			void removeIgnoredDirectory(fs::path const& path)										noexcept;

			/**
			*	@brief Clear the list of files to parse.
			*/
			void clearToParseFiles()																noexcept;

			/**
			*	@brief Clear the list of directories to parse.
			*/
			void clearToParseDirectories()															noexcept;

			/**
			*	@brief Clear the list of ignored files.
			*/
			void clearIgnoredFiles()																noexcept;

			/**
			*	@brief Clear the list of ignored directories.
			*/
			void clearIgnoredDirectories()															noexcept;

			/**
			*	@brief Getter for _outputDirectory.
			*
			*	@return _outputDirectory.
			*/
			inline fs::path const&									getOutputDirectory()	const	noexcept;

			/**
			*	@brief Getter for _toParseFiles.
			*	
			*	@return _toParseFiles.
			*/
			inline std::unordered_set<fs::path, PathHash> const&	getToParseFiles()		const	noexcept;

			/**
			*	@brief Getter for _toParseDirectories.
			*	
			*	@return _toParseDirectories.
			*/
			inline std::unordered_set<fs::path, PathHash> const&	getToParseDirectories() const	noexcept;

			/**
			*	@brief Getter for _ignoredFiles.
			*	
			*	@return _ignoredFiles.
			*/
			inline std::unordered_set<fs::path, PathHash> const&	getIgnoredFiles()		const	noexcept;

			/**
			*	@brief Getter for _ignoredDirectories.
			*	
			*	@return _ignoredDirectories.
			*/
			inline std::unordered_set<fs::path, PathHash> const&	getIgnoredDirectories()	const	noexcept;
	};

	#include "Kodgen/CodeGen/FileGenerationSettings.inl"
}