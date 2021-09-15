#include "RefurekuGenerator/CodeGen/CodeGenManager.h"

using namespace rfk;

CodeGenManager::CodeGenManager(kodgen::uint32 threadCount) noexcept:
	kodgen::CodeGenManager(threadCount)
{
	//Only parse .h and .hpp files
	settings.addSupportedFileExtension(".h");
	settings.addSupportedFileExtension(".hpp");
}