/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

inline NonTypeTemplateArgument::NonTypeTemplateArgumentImpl::NonTypeTemplateArgumentImpl(Archetype const* valueArchetype, void const* valuePtr) noexcept:
	TemplateArgumentImpl(ETemplateParameterKind::NonTypeTemplateParameter),
	_valueArchetype{valueArchetype},
	_valuePtr{valuePtr}
{
}

inline Archetype const* NonTypeTemplateArgument::NonTypeTemplateArgumentImpl::getArchetype() const noexcept
{
	return _valueArchetype;
}

inline void const* NonTypeTemplateArgument::NonTypeTemplateArgumentImpl::getValuePtr() const noexcept
{
	return _valuePtr;
}