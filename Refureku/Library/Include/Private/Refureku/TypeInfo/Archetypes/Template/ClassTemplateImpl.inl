/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

inline ClassTemplateAPI::ClassTemplateImpl::ClassTemplateImpl(char const* name, std::size_t id, bool isClass) noexcept:
	StructImpl(name, id, 0u, isClass, EClassKind::Template)
{
}

inline std::vector<TemplateParameterAPI const*> const& ClassTemplateAPI::ClassTemplateImpl::getTemplateParameters() const noexcept
{
	return _templateParameters;
}