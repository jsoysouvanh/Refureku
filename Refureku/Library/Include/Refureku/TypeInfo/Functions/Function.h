/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Functions/FunctionBase.h"
#include "Refureku/TypeInfo/Functions/EFunctionFlags.h"
#include "Refureku/TypeInfo/Functions/NonMemberFunction.h"

namespace rfk
{
	class Function : public FunctionBase
	{
		private:
			/**
			*	@brief Invoke the internal function using passed arguments.
			*	
			*	@tparam		ReturnType Return type of the internal function.
			*	@tparam...	ArgTypes Passed argument types.
			*
			*	@param... arguments Arguments to forward to the internal function.
			*	
			*	@return The result of the internal function call.
			*/
			template <typename ReturnType, typename... ArgTypes>
			ReturnType	internalInvoke(ArgTypes&&... arguments) const noexcept;

		public:
			/** Flags describing this function. */
			EFunctionFlags	flags = EFunctionFlags::Default;

			Function()												= delete;
			Function(std::string&&					name, 
					 uint64							id,
					 Type const&					returnType,
					 std::unique_ptr<ICallable>&&	internalMethod,
					 EFunctionFlags					flags)			noexcept;
			Function(Function const&)								= delete;
			Function(Function&&)									= delete;
			~Function()												= default;

			/**
			*	@brief Call the function with the provided argument(s) if any, and return the result.
			*
			*	In debug mode (NDEBUG macro not defined), checks that the correct number of
			*	arguments is passed before actually invoking the underlying function.
			*	If it is incorrect, a MethodError exception is thrown.
			*	Type checks are not performed so calling this function with bad parameters might lead to a crash.
			*
			*	\tparam ReturnType Return type of the function
			*	\tparam... ArgTypes Type of all arguments. This can in some cases be omitted thanks to template deduction.
			*
			*	@param arguments Arguments provided to the function call. 
			*
			*	@return The result of the function call.
			*/
			template <typename ReturnType, typename... ArgTypes>
			ReturnType	rInvoke(ArgTypes&&... arguments)		const noexcept(REFUREKU_RELEASE);

			/**
			*	@brief Call the function with the provided argument(s) if any.
			*
			*	In debug mode (NDEBUG macro not defined), checks that the correct number of
			*	arguments is passed to the function call before actually invoking the underlying function.
			*	If it is incorrect, a MethodError exception is thrown.
			*	Type checks are not performed so calling this function with bad parameters might lead to a crash.
			*
			*	@tparam ArgTypes... Type of all arguments. This can in some cases be omitted thanks to template deduction.
			*
			*	@param arguments... Arguments provided to the function call.
			*/
			template <typename... ArgTypes>
			void		invoke(ArgTypes&&... arguments)			const noexcept(REFUREKU_RELEASE);

			/**
			*	@brief Call the function with the provided argument(s) if any, and return the result.
			*
			*	Checks the argument count and the type of each argument before actually invoking the underlying function.
			*	If any of those is incorrect, a MethodError exception is thrown.
			*
			*	@tparam		ReturnType	Return type of the function
			*	@tparam...	ArgTypes	Type of all arguments. This can in some cases be omitted thanks to template deduction,
			*							but it is always safer to explicitly specify each template type to avoid type mismatches (a char* could
			*							be template deducted as a char[], and as they are different types a MethodError exception will be thrown).
			*
			*	@param arguments... Arguments provided to the function call.
			*
			*	@return The result of the function call.
			*/
			template <typename ReturnType, typename... ArgTypes>
			ReturnType	checkedRInvoke(ArgTypes&&... arguments)	const;

			/**
			*	@brief Call the function with the provided argument(s) if any.
			*
			*	Checks the argument count and the type of each argument before actually invoking the underlying function.
			*	If any of those is incorrect, a MethodError exception is thrown.
			*
			*	@tparam... ArgTypes Type of all arguments. This can in some cases be omitted thanks to template deduction,
			*		but it is always safer to explicitly specify each template type to avoid type mismatches (a char* could
			*		be template deducted as a char[], and as they are different types a MethodError exception will be thrown).
			*
			*	@param arguments... Arguments provided to the function call.
			*/
			template <typename... ArgTypes>
			void		checkedInvoke(ArgTypes&&... arguments)	const;

			/**
			*	@brief Check if this function is inline.
			*
			*	@return true if the function is inline, else false.
			*/
			bool	isInline()									const noexcept;

			/**
			*	@brief Check if this function is static.
			*
			*	@return true if the function is static, else false.
			*/
			bool	isStatic()									const noexcept;
	};

	#include "Refureku/TypeInfo/Functions/Function.inl"
}