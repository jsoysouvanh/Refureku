/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

template <typename... Types>
bool ClassTemplateInstantiation::hasSameTemplateArguments() const noexcept
{
	//TODO: Remove the std::array dependency
	static Archetype const* archetypes[] = { rfk::getArchetype<Types>()... };

	return hasSameTemplateArguments<sizeof...(Types)>(archetypes);
}

template <size_t ArraySize>
bool ClassTemplateInstantiation::hasSameTemplateArguments(Archetype const* (&archetypes)[ArraySize]) const noexcept
{
	std::size_t templateArgumentsCount = getTemplateArgumentsCount();

	//TODO: Remove the std::array dependency
	if (templateArgumentsCount != ArraySize)
	{
		return false;
	}

	for (std::size_t i = 0; i < templateArgumentsCount; i++)
	{
		//Can't assert equality when archetype is nullptr since it represents all non-reflected types
		if (archetypes[i] == nullptr || archetypes[i] != getTemplateArgument(i).getArchetype())
		{
			return false;
		}
	}

	return true;
}