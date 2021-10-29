/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Functions/FunctionBase.h"
#include "Refureku/TypeInfo/Functions/EFunctionFlags.h"
#include "Refureku/TypeInfo/Functions/NonMemberFunction.h"

namespace rfk
{
	class Function final : public FunctionBase
	{
		public:
			REFUREKU_API Function(char const*		name, 
								  std::size_t		id,
								  Type const&		returnType,
								  ICallable*		internalFunction,
								  EFunctionFlags	flags)			noexcept;
			Function(Function&&)									= delete;
			REFUREKU_API ~Function()								noexcept;

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
			ReturnType									invoke(ArgTypes&&... args)			const;

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
			ReturnType									checkedInvoke(ArgTypes&&... args)	const;

			/**
			*	@brief Check whether this function is inline or not.
			*
			*	@return true if this function is inline, else false.
			*/
			RFK_NODISCARD REFUREKU_API bool				isInline()							const	noexcept;

			/**
			*	@brief Check whether this function is static or not.
			*
			*	@return true if this function is static, else false.
			*/
			RFK_NODISCARD REFUREKU_API bool				isStatic()							const	noexcept;

			/**
			*	@brief Get the flags qualifying this function.
			* 
			*	@return The flags qualifying this function.
			*/
			RFK_NODISCARD REFUREKU_API EFunctionFlags	getFlags()							const	noexcept;

		private:
			//Forward declaration
			class FunctionImpl;

			RFK_GEN_GET_PIMPL(FunctionImpl, Entity::getPimpl())

			/**
			*	@brief Call the underlying function with the forwarded args.
			* 
			*	@tparam ReturnType	Return type of the function.
			*	@tparam... ArgTypes	Type of all arguments.
			*
			*	@param args Arguments forwarded to the underlying function call.
			*
			*	@return The result of the underlying function call.
			*/
			template <typename ReturnType, typename... ArgTypes>
			ReturnType	internalInvoke(ArgTypes&&... args)	const;
	};

	/** Base implementation of getFunction, specialized for each reflected function. */
	template <auto FuncPtr>
	Function const* getFunction() noexcept;

	REFUREKU_TEMPLATE_API(rfk::Allocator<Function const*>);
	REFUREKU_TEMPLATE_API(rfk::Vector<Function const*, rfk::Allocator<Function const*>>);

	#include "Refureku/TypeInfo/Functions/Function.inl"
}