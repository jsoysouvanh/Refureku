/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Functions/MethodBase.h"
#include "Refureku/TypeInfo/Functions/NonMemberFunction.h"

namespace rfk
{
	class StaticMethod final : public MethodBase
	{
		public:
			REFUREKU_API	  StaticMethod(char const*		name,
										   std::size_t		id,
										   Type const&		returnType,
										   ICallable*		internalMethod,
										   EMethodFlags		flags,
										   Entity const*	outerEntity)	noexcept;
			REFUREKU_INTERNAL StaticMethod(StaticMethod&&)					noexcept;
			REFUREKU_API	  ~StaticMethod()								noexcept;

			/**
			*	@brief	Call the function with the forwarded argument(s) if any, and return the result.
			*			Providing bad return type / parameters is undefined behaviour.
			*			**WARNING**: Template type deduction might forward wrong types to the function
			*			(int instead of int8_t or char* instead of std::string for example), so it is recommended
			*			to explicitly specify all template types when calling the function.
			*
			*	@tparam ReturnType	Return type of the function.
			*	@tparam... ArgTypes	Type of all arguments. This can in some cases be omitted thanks to template deduction.
			*
			*	@param args Arguments forwarded to the function call.
			* 
			*	@return The result of the function call.
			* 
			*	@exception Any exception potentially thrown from the underlying function.
			*/
			template <typename ReturnType = void, typename... ArgTypes>
			ReturnType	invoke(ArgTypes&&... args)			const;

			/**
			*	@brief	Call the function with the forwarded argument(s) if any, and return the result.
			*			The return type and arguments types will be strictly checked before calling the function.
			*			If there is any mismatch, ArgCountMismatch, ArgTypeMismatch or ReturnTypeMismatch will be thrown.
			*			**WARNING 1**: Unreflected archetypes can't be compared, so they will pass through the type checks.
			*			**WARNING 2**: Template type deduction might forward wrong types to the function
			*			(int instead of int8_t or char* instead of std::string for example), so it is recommended
			*			to explicitly specify all template types when calling the function.
			*
			*	@tparam ReturnType	Return type of the function.
			*	@tparam... ArgTypes	Type of all arguments. This can in some cases be omitted thanks to template deduction.
			*
			*	@param args Arguments forwarded to the function call.
			*
			*	@return The result of the function call.
			* 
			*	@exception	ArgCountMismatch if sizeof...(ArgTypes) is not the same as the value returned by getParametersCount().
			*	@exception	ArgTypeMismatch if ArgTypes... are not strictly the same as this function parameter types.
			*				**WARNING**: Be careful to template deduction.
			*	@exception	ReturnTypeMismatch if ReturnType is not strictly the same as this function return type.
			*	@exception	Any exception potentially thrown from the underlying function.
			*/
			template <typename ReturnType = void, typename... ArgTypes>
			ReturnType	checkedInvoke(ArgTypes&&... args)	const;

		private:
			//Forward declaration
			class StaticMethodImpl;

			/**
			*	@brief Call the underlying static method with the forwarded args.
			* 
			*	@tparam ReturnType	Return type of the static method.
			*	@tparam... ArgTypes	Type of all arguments.
			*
			*	@param args Arguments forwarded to the underlying static method call.
			*
			*	@return The result of the underlying static method call.
			*/
			template <typename ReturnType, typename... ArgTypes>
			ReturnType	internalInvoke(ArgTypes&&... args) const;
	};

	REFUREKU_TEMPLATE_API(rfk::Allocator<StaticMethod const*>);
	REFUREKU_TEMPLATE_API(rfk::Vector<StaticMethod const*, rfk::Allocator<StaticMethod const*>>);

	#include "Refureku/TypeInfo/Functions/StaticMethod.inl"
}