#include "Kodgen/Properties/SimpleProperty.h"

using namespace kodgen;

SimpleProperty::SimpleProperty(std::string mainProperty, SimplePropertyRule const* matchingPropertyRule) noexcept:
	Property(std::move(mainProperty)),
	boundPropertyRule{matchingPropertyRule}
{
}