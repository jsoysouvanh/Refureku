/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <utility>	//std::forward
#include <cassert>

#include "Refureku/TypeInfo/Functions/ICallable.h"

namespace rfk
{
	template <typename CallerType, typename FunctionPrototype>
	class MemberFunction;

	template <typename CallerType, typename ReturnType, typename... ArgTypes>
	class MemberFunction<CallerType, ReturnType(ArgTypes...)> : public ICallable
	{
		private:
			using FunctionPrototype			= ReturnType (CallerType::*)(ArgTypes...);
			using ConstFunctionPrototype	= ReturnType (CallerType::*)(ArgTypes...) const;

			/** Pointer to the underlying method. */
			union
			{
				FunctionPrototype		_function		= nullptr;
				ConstFunctionPrototype	_constFunction;
			};

			/** Is the internal method const-qualified or not. */
			bool	_isConst;

		public:
			MemberFunction(FunctionPrototype function)		noexcept;
			MemberFunction(ConstFunctionPrototype function)	noexcept;

			/**
			*	@brief Call the underlying function with on the provided caller forwarding the provided arguments.
			* 
			*	@param		caller	Instance the underlying method is called on.
			*	@param...	args	Arguments forwarded to the method call.
			* 
			*	@return The result forwarded from the method call.
			*/
			ReturnType operator()(CallerType& caller, ArgTypes&&... args)		const;

			/**
			*	@brief Call the underlying function with on the provided caller forwarding the provided arguments.
			* 
			*	@param		caller	Instance the underlying method is called on.
			*	@param...	args	Arguments forwarded to the method call.
			* 
			*	@return The result forwarded from the method call.
			*/
			ReturnType operator()(CallerType const& caller, ArgTypes&&... args)	const;
	};

	#include "Refureku/TypeInfo/Functions/MemberFunction.inl"
}