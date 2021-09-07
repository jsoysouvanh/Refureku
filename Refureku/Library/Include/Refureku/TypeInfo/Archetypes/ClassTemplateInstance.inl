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

	if (templateArguments.size() != archetypes.size())
	{
		return false;
	}

	for (int i = 0; i < templateArguments.size(); i++)
	{
		if (archetypes[i] != templateArguments[i].archetype)
		{
			return false;
		}
	}

	return true;
}