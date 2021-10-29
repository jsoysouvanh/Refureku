/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

inline TypeTemplateParameter::TypeTemplateParameterImpl::TypeTemplateParameterImpl(char const* name) noexcept:
	TemplateParameterImpl(name, ETemplateParameterKind::TypeTemplateParameter)
{
}