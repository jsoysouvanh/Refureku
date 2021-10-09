/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

inline NonTypeTemplateArgument::NonTypeTemplateArgumentImpl::NonTypeTemplateArgumentImpl(TemplateParameter const& boundParameter, void const* valuePtr) noexcept:
	TemplateArgumentImpl(boundParameter),
	_valuePtr{valuePtr}
{
}

inline void const* NonTypeTemplateArgument::NonTypeTemplateArgumentImpl::getValuePtr() const noexcept
{
	return _valuePtr;
}