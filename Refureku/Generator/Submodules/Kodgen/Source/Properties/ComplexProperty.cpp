#include "Properties/ComplexProperty.h"

using namespace kodgen;

ComplexProperty::ComplexProperty(std::string mainProperty, ComplexPropertyRule const* matchingPropertyRule) noexcept:
	mainProperty{std::move(mainProperty)},
	boundPropertyRule{matchingPropertyRule}
{
}