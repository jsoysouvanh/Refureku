/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

inline NonTypeTemplateParameter::NonTypeTemplateParameterImpl::NonTypeTemplateParameterImpl(char const* name, Archetype const* archetype) noexcept:
	TemplateParameterImpl(name, ETemplateParameterKind::NonTypeTemplateParameter),
	_archetype{archetype}
{
}

inline Archetype const* NonTypeTemplateParameter::NonTypeTemplateParameterImpl::getArchetype() const noexcept
{
	return _archetype;
}