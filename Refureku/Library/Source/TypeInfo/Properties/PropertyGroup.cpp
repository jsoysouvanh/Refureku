#include "TypeInfo/Properties/PropertyGroup.h"

#include <algorithm>

using namespace rfk;

SimpleProperty const* PropertyGroup::getSimpleProperty(std::string const& mainProperty) const noexcept
{
	decltype(simpleProperties)::const_iterator it = std::find_if(simpleProperties.cbegin(), simpleProperties.cend(),
																 [&](SimpleProperty const& sp) { return sp.mainProperty == mainProperty; });

	return (it != simpleProperties.cend()) ? &*it : nullptr;
}

ComplexProperty const* PropertyGroup::getComplexProperty(std::string const& mainProperty) const noexcept
{
	decltype(complexProperties)::const_iterator it = std::find_if(complexProperties.cbegin(), complexProperties.cend(),
																 [&](ComplexProperty const& cp) { return cp.mainProperty == mainProperty; });

	return (it != complexProperties.cend()) ? &*it : nullptr;
}