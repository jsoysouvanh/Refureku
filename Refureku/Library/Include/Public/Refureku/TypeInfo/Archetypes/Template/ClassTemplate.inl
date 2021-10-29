/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

template <std::size_t ArgsCount>
ClassTemplateInstantiation const* ClassTemplate::getTemplateInstantiation(TemplateArgument const* (&args)[ArgsCount]) const noexcept
{
	if constexpr (ArgsCount > 0)
	{
		return getTemplateInstantiation(&args[0], ArgsCount);
	}
	else
	{
		return nullptr;
	}
}