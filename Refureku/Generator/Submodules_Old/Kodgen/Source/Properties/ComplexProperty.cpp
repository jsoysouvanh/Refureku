#include "Kodgen/Properties/ComplexProperty.h"

using namespace kodgen;

ComplexProperty::ComplexProperty(std::string mainProperty, ComplexPropertyRule const* matchingPropertyRule) noexcept:
	Property(std::move(mainProperty)),
	boundPropertyRule{matchingPropertyRule}
{
}