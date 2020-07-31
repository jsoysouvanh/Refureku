#include "TypeInfo/Properties/SimpleProperty.h"

using namespace rfk;

SimpleProperty::SimpleProperty(std::string mainProperty) noexcept:
	mainProperty{std::move(mainProperty)}
{
}