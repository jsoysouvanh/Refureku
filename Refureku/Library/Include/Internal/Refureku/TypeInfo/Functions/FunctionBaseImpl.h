/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Functions/FunctionBase.h"
#include "Refureku/TypeInfo/Entity/EntityImpl.h"
#include "Refureku/Misc/UniquePtr.h"

namespace rfk
{
	class FunctionBase::FunctionBaseImpl : public Entity::EntityImpl
	{
		private:
			/** Type returned by this function. */
			Type const&						_returnType;

			/** Handle pointing to the actual function in memory. */
			UniquePtr<ICallable>			_internalFunction;

			/** Parameters of this function. */
			std::vector<FunctionParameter>	_parameters;

		public:
			inline FunctionBaseImpl(char const*		name, 
									std::size_t		id,
									EEntityKind		kind,
									Type const&		returnType,
									ICallable*		internalFunction,
									Entity const*	outerEntity)		noexcept;

			/**
			*	@brief Add a parameter to this function.
			* 
			*	@param name			Name of the parameter, can be empty.
			*	@param id			Id of the parameter entity.
			*	@param type			Type of the parameter.
			*	@param outerEntity	Function owning the parameter.
			*	
			*	@return The added function parameter.
			*/
			inline FunctionParameter&									addParameter(char const*				name,
																						 std::size_t			id,
																						 Type const&			type,
																						 FunctionBase const*	outerEntity)	noexcept;

			/**
			*	@brief Getter for the field _returnType.
			* 
			*	@return _returnType.
			*/
			RFK_NODISCARD inline Type const&							getReturnType()									const	noexcept;

			/**
			*	@brief Getter for the field _internalFunction.
			* 
			*	@return _internalFunction.
			*/
			RFK_NODISCARD inline ICallable*								getInternalFunction()							const	noexcept;

			/**
			*	@brief Getter for the field _parameters.
			* 
			*	@return _parameters.
			*/
			RFK_NODISCARD inline std::vector<FunctionParameter> const&	getParameters()									const	noexcept;

			/**
			*	@brief Set the _parameters vector capacity.
			* 
			*	@param capacity New capacity.
			*/
			inline void													setParametersCapacity(std::size_t capacity)				noexcept;
	};

	#include "Refureku/TypeInfo/Functions/FunctionBaseImpl.inl"
}