/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "TypeInfo/Methods/MethodBase.h"
#include "Utility/NonMemberFunction.h"

namespace rfk
{
	class StaticMethod : public MethodBase
	{
		public:
			StaticMethod()																			= delete;
			StaticMethod(std::string&&					name,
						 uint64							id				= 0u,
						 EMethodFlags					flags			= EMethodFlags::Static,
						 std::shared_ptr<ICallable>&&	internalMethod	= nullptr)					noexcept;
			StaticMethod(StaticMethod const&)														= default;
			StaticMethod(StaticMethod&&)															= default;
			~StaticMethod()																			= default;

			/**
			*	@brief Call the static method with the provided argument(s) if any.
			*
			*	In debug mode (NDEBUG macro not defined), checks that the correct number of
			*	arguments is passed to the method call before actually invoking the underlying method.
			*	If it is incorrect, a MethodError exception is thrown.
			*	Type checks are not performed so calling this method with bad parameters might lead to a crash.
			*
			*	\tparam ReturnType Return type of the method
			*	\tparam... ArgTypes Type of all arguments
			*
			*	@param arguments Arguments provided to the method call. This can in some cases be omitted thanks to template deduction.
			*
			*	@return The result of the method call.
			*/
			template <typename ReturnType, typename... ArgTypes>
			ReturnType	invoke(ArgTypes&&... arguments)			const	noexcept(REFUREKU_RELEASE);

			/**
			*	@brief Call the static method with the provided argument(s) if any.
			*
			*	In debug mode (NDEBUG macro not defined), checks that the correct number of
			*	arguments is passed to the method call before actually invoking the underlying method.
			*	If it is incorrect, a MethodError exception is thrown.
			*	Type checks are not performed so calling this method with bad parameters might lead to a crash.
			*
			*	\note This is only an overload of the other invoke method.
			*		  This allows to conveniently call static methods when we don't care about the returned value.
			*
			*	\tparam... ArgTypes Type of all arguments. This can in some cases be omitted thanks to template deduction.
			*
			*	@param caller Pointer to the instance of the class the method will be called.
			*	@param arguments Arguments provided to the method call.
			*/
			template <typename... ArgTypes>
			void		invoke(ArgTypes&&... arguments)			const	noexcept(REFUREKU_RELEASE);

			/**
			*	@brief Call the static method with the provided argument(s) if any.
			*
			*	Checks the argument count and the type of each argument before actually invoking the underlying method.
			*	If any of those is incorrect, a MethodError exception is thrown.
			*
			*	\tparam ReturnType Return type of the method
			*	\tparam... ArgTypes Type of all arguments. This can in some cases be omitted thanks to template deduction,
			*		but it is always safer to explicitly specify each template type to avoid type mismatches (a char* could
			*		be template deducted as a char[], and as they are different types a MethodError exception will be thrown).
			*
			*	@param arguments Arguments provided to the method call.
			*
			*	@return The result of the static method call.
			*/
			template <typename ReturnType, typename... ArgTypes>
			ReturnType	checkedInvoke(ArgTypes&&... arguments)	const;

			/**
			*	@brief Call the static method with the provided argument(s) if any.
			*
			*	Checks the argument count and the type of each argument before actually invoking the underlying method.
			*	If any of those is incorrect, a MethodError exception is thrown.
			*
			*	\note This is only an overload of the other checkedInvoke method.
			*		  This allows to conveniently call static methods when we don't care about the returned value.
			*
			*	\tparam... ArgTypes Type of all arguments. This can in some cases be omitted thanks to template deduction,
			*		but it is always safer to explicitly specify each template type to avoid type mismatches (a char* could
			*		be template deducted as a char[], and as they are different types a MethodError exception will be thrown).
			*
			*	@param arguments Arguments provided to the method call.
			*/
			template <typename... ArgTypes>
			void		checkedInvoke(ArgTypes&&... arguments)	const;
	};

	#include "TypeInfo/Methods/StaticMethod.inl"
}