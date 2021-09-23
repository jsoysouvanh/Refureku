/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

template <typename... Types>
ClassTemplateInstantiation const* ClassTemplate::getInstantiation() const noexcept
{
	for (std::size_t i = 0; i < getInstantiationsCount(); i++)
	{
		ClassTemplateInstantiation const& instantiation = getInstantiation(i);

		if (instantiation.hasSameTemplateArguments<Types...>())
		{
			return &instantiation;
		}
	}

	return nullptr;
}

template <size_t ArraySize>
ClassTemplateInstantiation const* ClassTemplate::getInstantiation(std::array<Archetype const*, ArraySize> const& archetypes) const noexcept
{
	for (std::size_t i = 0; i < getInstantiationsCount(); i++)
	{
		ClassTemplateInstantiation const& instantiation = getInstantiation(i);

		if (instantiation.hasSameTemplateArguments<ArraySize>(archetypes))
		{
			return &instantiation;
		}
	}

	return nullptr;
}