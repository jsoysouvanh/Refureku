/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

inline FunctionBase::FunctionBaseImpl::FunctionBaseImpl(char const* name, std::size_t id, EEntityKind kind,
														   Type const& returnType, ICallable* internalFunction, Entity const* outerEntity) noexcept:
	EntityImpl(name, id, kind, outerEntity),
	_returnType{returnType},
	_internalFunction{internalFunction}
{
}

inline FunctionParameter& FunctionBase::FunctionBaseImpl::addParameter(char const* name, std::size_t id, Type const& type, FunctionBase const* outerEntity) noexcept
{
	return _parameters.emplace_back(name, id, type, outerEntity);
}

inline Type const& FunctionBase::FunctionBaseImpl::getReturnType() const noexcept
{
	return _returnType;
}

inline ICallable* FunctionBase::FunctionBaseImpl::getInternalFunction() const noexcept
{
	return _internalFunction.get();
}

inline std::vector<FunctionParameter> const& FunctionBase::FunctionBaseImpl::getParameters() const noexcept
{
	return _parameters;
}

inline void FunctionBase::FunctionBaseImpl::setParametersCapacity(std::size_t capacity) noexcept
{
	_parameters.reserve(capacity);
}