#include "Kodgen/CodeGen/FileGenerationResult.h"

using namespace kodgen;

void FileGenerationResult::mergeResult(FileGenerationResult&& otherResult) noexcept
{
	parsedFiles.insert(parsedFiles.cend(), std::make_move_iterator(otherResult.parsedFiles.cbegin()), std::make_move_iterator(otherResult.parsedFiles.cend()));
	upToDateFiles.insert(upToDateFiles.cend(), std::make_move_iterator(otherResult.upToDateFiles.cbegin()), std::make_move_iterator(otherResult.upToDateFiles.cend()));

	mergeResultErrors(std::forward<FileGenerationResult>(otherResult));
}

void FileGenerationResult::mergeResultErrors(FileGenerationResult&& otherResult) noexcept
{
	parsingErrors.insert(parsingErrors.cend(), std::make_move_iterator(otherResult.parsingErrors.cbegin()), std::make_move_iterator(otherResult.parsingErrors.cend()));
	fileGenerationErrors.insert(fileGenerationErrors.cend(), std::make_move_iterator(otherResult.fileGenerationErrors.cbegin()), std::make_move_iterator(otherResult.fileGenerationErrors.cend()));
}