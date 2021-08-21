#include "RefurekuGenerator/CodeGen/CodeGenManager.h"

using namespace rfk;

CodeGenManager::CodeGenManager() noexcept
{
	//Only parse .h and .hpp files
	settings.addSupportedExtension(".h");
	settings.addSupportedExtension(".hpp");
}