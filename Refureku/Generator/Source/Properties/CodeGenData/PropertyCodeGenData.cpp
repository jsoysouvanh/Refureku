#include "RefurekuGenerator/Properties/CodeGenData/PropertyCodeGenData.h"

using namespace rfk;

PropertyCodeGenData::PropertyCodeGenData(ECodeGenLocation codeGenLocation) noexcept:
	_codeGenLocation{codeGenLocation}
{
}

ECodeGenLocation PropertyCodeGenData::getCodeGenLocation() const noexcept
{
	return _codeGenLocation;
}