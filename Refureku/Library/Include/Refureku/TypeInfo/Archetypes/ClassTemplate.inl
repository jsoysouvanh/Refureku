/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

template <typename... Types>
ClassTemplateInstance const* ClassTemplate::getInstance() const noexcept
{
	for (ClassTemplateInstance const* instance : instances)
	{
		if (instance->hasSameTemplateArguments<Types...>())
		{
			return instance;
		}
	}

	return nullptr;
}

template <size_t ArraySize>
ClassTemplateInstance const* ClassTemplate::getInstance(std::array<Archetype const*, ArraySize> const& archetypes) const noexcept
{
	for (ClassTemplateInstance const* instance : instances)
	{
		if (instance->hasSameTemplateArguments<ArraySize>(archetypes))
		{
			return instance;
		}
	}

	return nullptr;
}