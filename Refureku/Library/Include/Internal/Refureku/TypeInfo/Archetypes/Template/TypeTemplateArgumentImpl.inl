/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

inline TypeTemplateArgument::TypeTemplateArgumentImpl::TypeTemplateArgumentImpl(Archetype const* archetype) noexcept:
	TemplateArgumentImpl(ETemplateParameterKind::TypeTemplateParameter),
	_archetype{archetype}
{
}

inline Archetype const* TypeTemplateArgument::TypeTemplateArgumentImpl::getArchetype() const noexcept
{
	return _archetype;
}