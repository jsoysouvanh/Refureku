#include "Properties/SimpleProperty.h"

using namespace kodgen;

SimpleProperty::SimpleProperty(std::string mainProperty, SimplePropertyRule const* matchingPropertyRule) noexcept:
	mainProperty{mainProperty},
	boundPropertyRule{matchingPropertyRule}
{
}