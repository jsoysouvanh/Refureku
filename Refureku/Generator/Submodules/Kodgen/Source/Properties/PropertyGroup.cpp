#include "Kodgen/Properties/PropertyGroup.h"

using namespace kodgen;

void PropertyGroup::removeStartAndTrailSpaces(std::string& string) noexcept
{
	//Remove start spaces
	size_t index = string.find_first_not_of(' ');

	//if index is 0, there is no start space
	if (index != 0u && index != std::string::npos)
	{
		string = string.substr(index);
	}

	//Remove trail spaces
	index = string.find_last_not_of(' ');

	//If index is string.size() - 1, there is no trail space
	if (index != string.size() - 1 && index != std::string::npos)
	{
		string.erase(index + 1);
	}
}

void PropertyGroup::removeStartAndTrailSpaces() noexcept
{
	//Simple prop
	for (SimpleProperty& property : simpleProperties)
	{
		removeStartAndTrailSpaces(property.mainProperty);
	}

	//Complex prop
	for (ComplexProperty& property : complexProperties)
	{
		//Main prop
		removeStartAndTrailSpaces(property.mainProperty);

		//Sub props
		for (std::string& subproperty : property.subProperties)
		{
			removeStartAndTrailSpaces(subproperty);
		}
	}
}