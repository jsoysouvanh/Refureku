/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <string>

#include "Refureku/Misc/FundamentalTypes.h"
#include "Refureku/TypeInfo/Methods/MethodBase.h"
#include "Refureku/Utility/MemberFunction.h"

namespace rfk
{
	class Struct;	//Forward declaration

	class Method final : public MethodBase
	{
		private:
			class DummyClass {};

			template <typename ReturnType, typename... ArgTypes>
			ReturnType	internalInvoke(void* caller, ArgTypes&&... arguments)		const	noexcept;

			template <typename ReturnType, typename... ArgTypes>
			ReturnType	internalInvoke(void const* caller, ArgTypes&&... arguments)	const	noexcept;

		public:
			/** Class containing the declaration of this method */
			Struct const*	ownerType	= nullptr;

			Method()												= delete;
			Method(std::string&&				methodName,
				   uint64						methodId,
				   EMethodFlags					flags,
				   std::shared_ptr<ICallable>&&	internalMethod,
				   Struct const*				methodOwnerType)	noexcept;
			Method(Method const&)									= default;
			Method(Method&&)										= default;
			~Method()												= default;

			/**
			*	@brief Call the method on an instance with the provided argument(s) if any.
			*
			*	In debug mode (NDEBUG macro not defined), checks that the correct number of
			*	arguments is passed to the method call before actually invoking the underlying method.
			*	If it is incorrect, a MethodError exception is thrown.
			*	Type checks are not performed so calling this method with bad parameters might lead to a crash.
			*
			*	\tparam ReturnType Return type of the method
			*	\tparam... ArgTypes Type of all arguments
			*
			*	@param caller Pointer to the instance of the class the method will be called.
			*	@param arguments Arguments provided to the method call. This can in some cases be omitted thanks to template deduction.
			*
			*	@return The result of the method call.
			*/
			template <typename ReturnType, typename... ArgTypes>
			ReturnType	invoke(void const* caller, ArgTypes&&... arguments)			const noexcept(REFUREKU_RELEASE);

			/**
			*	@brief Call the method on an instance with the provided argument(s) if any.
			*
			*	In debug mode (NDEBUG macro not defined), checks that the correct number of
			*	arguments is passed to the method call before actually invoking the underlying method.
			*	If it is incorrect, a MethodError exception is thrown.
			*	Type checks are not performed so calling this method with bad parameters might lead to a crash.
			*
			*	\note This is only an overload of the other invoke method.
			*		  This allows to conveniently call methods when we don't care about the returned value.
			*
			*	\tparam... ArgTypes Type of all arguments. This can in some cases be omitted thanks to template deduction.
			*
			*	@param caller Pointer to the instance of the class the method will be called.
			*	@param arguments Arguments provided to the method call.
			*/
			template <typename... ArgTypes>
			void		invoke(void const* caller, ArgTypes&&... arguments)			const noexcept(REFUREKU_RELEASE);

			/**
			*	@brief Call the method on an instance with the provided argument(s) if any.
			*
			*	Checks the argument count and the type of each argument before actually invoking the underlying method.
			*	If any of those is incorrect, a MethodError exception is thrown.
			*
			*	\tparam ReturnType Return type of the method
			*	\tparam... ArgTypes Type of all arguments. This can in some cases be omitted thanks to template deduction,
			*		but it is always safer to explicitly specify each template type to avoid type mismatches (a char* could
			*		be template deducted as a char[], and as they are different types a MethodError exception will be thrown).
			*
			*	@param caller Pointer to the instance of the class the method will be called.
			*	@param arguments Arguments provided to the method call.
			*
			*	@return The result of the method call.
			*/
			template <typename ReturnType, typename... ArgTypes>
			ReturnType	checkedInvoke(void const* caller, ArgTypes&&... arguments)	const;

			/**
			*	@brief Call the method on an instance with the provided argument(s) if any.
			*
			*	Checks the argument count and the type of each argument before actually invoking the underlying method.
			*	If any of those is incorrect, a MethodError exception is thrown.
			*
			*	\note This is only an overload of the other checkedInvoke method.
			*		  This allows to conveniently call methods when we don't care about the returned value.
			*
			*	\tparam... ArgTypes Type of all arguments. This can in some cases be omitted thanks to template deduction,
			*		but it is always safer to explicitly specify each template type to avoid type mismatches (a char* could
			*		be template deducted as a char[], and as they are different types a MethodError exception will be thrown).
			*
			*	@param caller Pointer to the instance of the class the method will be called.
			*	@param arguments Arguments provided to the method call.
			*/
			template <typename... ArgTypes>
			void		checkedInvoke(void const* caller, ArgTypes&&... arguments)	const;
	};

	#include "Refureku/TypeInfo/Methods/Method.inl"
}