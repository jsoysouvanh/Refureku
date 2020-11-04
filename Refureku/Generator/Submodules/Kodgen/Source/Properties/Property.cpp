#include "Kodgen/Properties/Property.h"

#include <utility>	//std::move

using namespace kodgen;

Property::Property(std::string mainProperty) noexcept:
	mainProperty{std::move(mainProperty)}
{
}