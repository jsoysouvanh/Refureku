#include "RefurekuGenerator/Properties/TestPropertyRule.h"

#include "RefurekuGenerator/Properties/CodeGenData/PropertyCodeGenData.h"
#include "RefurekuGenerator/Properties/CodeGenData/PropertyCodeGenPropertyAddData.h"

using namespace rfk;

TestPropertyRule::TestPropertyRule() noexcept:
	kodgen::DefaultComplexPropertyRule("TestProperty", (kodgen::EEntityType)~0)
{
}

std::string	TestPropertyRule::generateCode(kodgen::EntityInfo const& /* entity */, kodgen::Property const& /* property */, void* userData) const noexcept
{
	PropertyCodeGenData* data = reinterpret_cast<PropertyCodeGenData*>(userData);

	switch (data->getCodeGenLocation())
	{
		case ECodeGenLocation::FileHeader:
			return "/* FileHeader */";

		case ECodeGenLocation::PrePropertyAdd:
			return "/* PrePropertyAdd  " + reinterpret_cast<PropertyCodeGenPropertyAddData*>(userData)->accessEntityVariable() + " : " + reinterpret_cast<PropertyCodeGenPropertyAddData*>(userData)->accessPropertyVariable() + " */";

		case ECodeGenLocation::PostPropertyAdd:
			return "/* PostPropertyAdd " + reinterpret_cast<PropertyCodeGenPropertyAddData*>(userData)->accessEntityVariable() + " : " + reinterpret_cast<PropertyCodeGenPropertyAddData*>(userData)->accessPropertyVariable() + " */";

		case ECodeGenLocation::ClassFooter:
			return "/* ClassFooter */";

		case ECodeGenLocation::FileFooter:
			return "/* FileFooter */";
	}

	return "/* WHAT???? */";
}