/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

template <typename... Types>
bool ClassTemplateInstance::hasSameTemplateArguments() const noexcept
{
	static std::array<Archetype const*, sizeof...(Types)> archetypes = { { rfk::getArchetype<Types>()... } };

	return hasSameTemplateArguments<sizeof...(Types)>(archetypes);
}

template <size_t ArraySize>
bool ClassTemplateInstance::hasSameTemplateArguments(std::array<Archetype const*, ArraySize> const& archetypes) const noexcept
{
	if (templateArguments.size() != archetypes.size())
	{
		return false;
	}

	for (size_t i = 0; i < templateArguments.size(); i++)
	{
		//Can't assert equality when archetype is nullptr since it represents all non-reflected types
		if (archetypes[i] == nullptr || archetypes[i] != templateArguments[i].archetype)
		{
			return false;
		}
	}

	return true;
}