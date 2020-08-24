/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

template <template <typename> typename FileParserFactoryType, typename FileParserType, typename FileGenerationUnitType>
void FileGenerator::processFilesMultithread(FileParserFactoryType<FileParserType>& fileParserFactory, FileGenerationUnitType& fileGenerationUnit, std::set<fs::path> const& toProcessFiles, FileGenerationResult& out_genResult, uint32 threadCount) noexcept
{
	ThreadPool								threadPool(threadCount, ETerminationMode::FinishAll);
	std::vector<std::shared_ptr<TaskBase>>	generationTasks;

	//Reserve enough space for all tasks
	generationTasks.reserve(toProcessFiles.size());

	//Launch all parsing -> generation processes
	for (fs::path const& file : toProcessFiles)
	{
		//Add file to the list of parsed files before starting the task to avoid having to synchronize threads
		out_genResult.parsedFiles.push_back(file);

		auto parsingTask = threadPool.submitTask([&](TaskBase*) -> FileParsingResult
												  {
													 //Generate a parser for this task
													 FileParserType		fileParser = fileParserFactory.generateFileParser();
													 FileParsingResult	parsingResult;

													 fileParser.parse(file, fileParserFactory.getCompilationArguments(), parsingResult);

													 return parsingResult;
												  });

		generationTasks.emplace_back(threadPool.submitTask([&](TaskBase* parsingTask) -> FileGenerationResult
									 {
										FileGenerationResult	out_generationResult;
										
										//Copy the generation unit model to have a fresh one for this generation unit
										FileGenerationUnitType	generationUnit = fileGenerationUnit;

										//Get the result of the parsing task
										FileParsingResult		parsingResult = TaskHelper::getDependencyResult<FileParsingResult>(parsingTask, 0u);

										//Generate the file if no errors occured during parsing
										if (parsingResult.errors.empty())
										{
											generationUnit.generateFile(parsingResult, out_generationResult);
										}
										else
										{
											//Transfer parsing errors into the file generation result
											out_generationResult.parsingErrors.insert(out_generationResult.parsingErrors.cend(), std::make_move_iterator(parsingResult.errors.cbegin()), std::make_move_iterator(parsingResult.errors.cend()));
										}
										
										return out_generationResult;
									 
									 }, { parsingTask }));
	}

	//Merge all generation results together
	for (std::shared_ptr<TaskBase>& generationTask : generationTasks)
	{
		out_genResult.mergeResultErrors(TaskHelper::getResult<FileGenerationResult>(generationTask.get()));
	}
}

template <template <typename> typename FileParserFactoryType, typename FileParserType, typename FileGenerationUnitType>
void FileGenerator::processFilesMonothread(FileParserFactoryType<FileParserType>& fileParserFactory, FileGenerationUnitType& fileGenerationUnit, std::set<fs::path> const& toProcessFiles, FileGenerationResult& out_genResult) noexcept
{
	FileParserType fileParser = fileParserFactory.generateFileParser();

	for (fs::path const& file : toProcessFiles)
	{
		FileParsingResult parsingResult;

		out_genResult.parsedFiles.push_back(file);

		//Parse file
		if (fileParser.parse(file, fileParserFactory.getCompilationArguments(), parsingResult))
		{
			//Generate file according to parsing result
			fileGenerationUnit.generateFile(parsingResult, out_genResult);
		}
		else
		{
			//Transfer parsing errors into the file generation result
			out_genResult.parsingErrors.insert(out_genResult.parsingErrors.cend(), std::make_move_iterator(parsingResult.errors.cbegin()), std::make_move_iterator(parsingResult.errors.cend()));
		}
	}
}

template <template <typename> typename FileParserFactoryType, typename FileParserType, typename FileGenerationUnitType>
FileGenerationResult FileGenerator::generateFiles(FileParserFactoryType<FileParserType>& fileParserFactory, FileGenerationUnitType& fileGenerationUnit, bool forceRegenerateAll, uint32 threadCount) noexcept
{
	//Check FileParserFactory validity
	static_assert(std::is_base_of_v<FileParserFactoryBase, FileParserFactoryType<FileParserType>>, "fileParserFactory type must be a derived class of kodgen::FileParserFactory");

	//Check FileGenerationUnit validity
	static_assert(std::is_base_of_v<FileGenerationUnit, FileGenerationUnitType>, "fileGenerationUnit type must be a derived class of kodgen::FileGenerationUnit.");
	static_assert(std::is_copy_constructible_v<FileGenerationUnitType>, "The FileGenerationUnit you provide must be copy-constructible.");

	FileGenerationResult genResult;

	if (settings.outputDirectory.empty())
	{
		//Generator can't run without outputDirectory
		genResult.fileGenerationErrors.emplace_back("", "", "Output directory is empty, it must be specified for the files to be generated.");
		
		if (logger != nullptr)
		{
			logger->log("Output directory is empty, it must be specified for the files to be generated.", ILogger::ELogSeverity::Error);
		}
	}
	else
	{
		//Before doing anything, make sure destination folder exists
		if (!fs::exists(settings.outputDirectory))
		{
			//Try to create them is it doesn't exist
			try
			{
				genResult.completed = fs::create_directories(settings.outputDirectory);
			}
			catch (fs::filesystem_error const& exception)
			{
				if (logger != nullptr)
				{
					genResult.fileGenerationErrors.emplace_back("", "", "Output directory is invalid: " + std::string(exception.what()));

					logger->log("Output directory is invalid: " + std::string(exception.what()), ILogger::ELogSeverity::Error);
				}
			}
		}

		if (fs::is_directory(settings.outputDirectory))
		{
			//Start timer here
			std::chrono::time_point	start			= std::chrono::high_resolution_clock::now();
			std::set<fs::path>		filesToProcess	= identifyFilesToProcess(genResult, forceRegenerateAll);

			//Don't setup anything if there are no files to generate
			if (filesToProcess.size() > 0u)
			{
				//Forward FileGenerator necessary data to the file generation unit
				setupFileGenerationUnit(fileGenerationUnit);

				addNativePropertyRules(fileParserFactory.parsingSettings.propertyParsingSettings);

				//Initialize the file parser factory compilation arguments
				fileParserFactory._init();

				generateMacrosFile(fileParserFactory);

				if (threadCount == 0u)
				{
					processFilesMonothread(fileParserFactory, fileGenerationUnit, filesToProcess, genResult);
				}
				else
				{
					processFilesMultithread(fileParserFactory, fileGenerationUnit, filesToProcess, genResult, threadCount);
				}

				clearNativePropertyRules(fileParserFactory.parsingSettings.propertyParsingSettings);
			}

			genResult.duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count() / 1000.0f;

			genResult.completed = true;
		}
	}
	
	return genResult;
}