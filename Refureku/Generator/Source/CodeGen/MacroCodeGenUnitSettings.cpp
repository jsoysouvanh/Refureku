#include "RefurekuGenerator/CodeGen/MacroCodeGenUnitSettings.h"

using namespace rfk;

MacroCodeGenUnitSettings::MacroCodeGenUnitSettings() noexcept:
	kodgen::MacroCodeGenUnitSettings()
{
	setGeneratedHeaderFileNamePattern("##FILENAME##.rfkh.h");
	setGeneratedSourceFileNamePattern("##FILENAME##.rfks.h");
}