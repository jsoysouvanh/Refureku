/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

template <typename T>
NonTypeTemplateArgument::NonTypeTemplateArgument(T const& value) noexcept:
	NonTypeTemplateArgument(rfk::getArchetype<T>(), &value)
{
}

template <typename T>
T const& NonTypeTemplateArgument::getValue() const noexcept
{
	return *reinterpret_cast<T const*>(getValuePtr());
}