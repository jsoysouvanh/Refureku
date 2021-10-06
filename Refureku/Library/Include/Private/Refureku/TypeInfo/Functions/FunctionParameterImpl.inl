/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

FunctionParameterAPI::FunctionParameterImpl::FunctionParameterImpl(char const* name, std::size_t id, TypeAPI const& type, Entity const* outerEntity) noexcept:
	EntityImpl(name, id, EEntityKind::Undefined /* TODO: Add new entity kind for parameters */, outerEntity),
	_type{type}
{
}

TypeAPI const& FunctionParameterAPI::FunctionParameterImpl::getType() const noexcept
{
	return _type;
}