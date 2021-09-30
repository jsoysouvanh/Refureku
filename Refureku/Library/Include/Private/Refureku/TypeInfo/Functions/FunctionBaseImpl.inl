/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

inline FunctionBaseAPI::FunctionBaseImpl::FunctionBaseImpl(char const* name, std::size_t id, EEntityKind kind,
														   TypeAPI const& returnType, ICallable* internalFunction, EntityAPI const* outerEntity) noexcept:
	EntityImpl(name, id, kind, outerEntity),
	_returnType{returnType},
	_internalFunction{internalFunction}
{
}

inline FunctionParameterAPI& FunctionBaseAPI::FunctionBaseImpl::addParameter(char const* name, std::size_t id, TypeAPI const& type, FunctionBaseAPI const* outerEntity) noexcept
{
	return _parameters.emplace_back(name, id, type, outerEntity);
}

inline TypeAPI const& FunctionBaseAPI::FunctionBaseImpl::getReturnType() const noexcept
{
	return _returnType;
}

inline ICallable* FunctionBaseAPI::FunctionBaseImpl::getInternalFunction() const noexcept
{
	return _internalFunction.get();
}

inline std::vector<FunctionParameterAPI> const& FunctionBaseAPI::FunctionBaseImpl::getParameters() const noexcept
{
	return _parameters;
}

inline void FunctionBaseAPI::FunctionBaseImpl::setParametersCapacity(std::size_t capacity) noexcept
{
	_parameters.reserve(capacity);
}