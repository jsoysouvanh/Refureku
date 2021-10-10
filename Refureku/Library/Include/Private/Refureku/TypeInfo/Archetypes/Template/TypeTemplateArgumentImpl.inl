/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

inline TypeTemplateArgument::TypeTemplateArgumentImpl::TypeTemplateArgumentImpl(TemplateParameter const& boundParameter, Archetype const* archetype) noexcept:
	TemplateArgumentImpl(boundParameter),
	_archetype{archetype}
{
}

inline Archetype const* TypeTemplateArgument::TypeTemplateArgumentImpl::getArchetype() const noexcept
{
	return _archetype;
}