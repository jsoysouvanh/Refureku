/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <string>

#include "Refureku/Config.h"
#include "Refureku/Misc/FundamentalTypes.h"
#include "Refureku/TypeInfo/Functions/MethodBase.h"
#include "Refureku/TypeInfo/Functions/MemberFunction.h"
#include "Refureku/Exceptions/ConstViolation.h"

namespace rfk
{
	class Method final : public MethodBase
	{
		private:
			/**
			*	@brief Invoke the internal method using passed arguments.
			*	
			*	@tparam		ReturnType Return type of the internal method.
			*	@tparam...	ArgTypes Passed argument types.
			*
			*	@param		caller Pointer to the object the internal method should be called on.
			*	@param...	arguments Arguments to forward to the internal method.
			*
			*	@exception ConstViolation if a non-const method is called on a const caller.
			* 
			*	@return The result of the internal method call.
			*/
			template <typename ReturnType, typename CallerType, typename... ArgTypes>
			ReturnType	internalInvoke(CallerType& caller, ArgTypes&&... arguments)		const noexcept;

			template <typename ReturnType, typename CallerType, typename... ArgTypes>
			ReturnType	internalInvoke(CallerType const& caller, ArgTypes&&... arguments)	const;

		public:
			Method(std::string&&				methodName,
				   std::size_t					id,
				   Type const&					returnType,
				   std::unique_ptr<ICallable>&&	internalMethod,
				   EMethodFlags					flags,
				   Entity const*				outerEntity = nullptr)	noexcept;
			Method(Method const&)										= delete;
			Method(Method&&)											= delete;

			/**
			*	@brief Call the method on an instance with the provided argument(s) if any, and return the result.
			*
			*	In debug mode (NDEBUG macro not defined), checks that the correct number of
			*	arguments is passed to the method call before actually invoking the underlying method.
			*	If it is incorrect, a MethodError exception is thrown.
			*	Type checks are not performed so calling this method with bad parameters might lead to a crash.
			*
			*	@tparam ReturnType Return type of the method
			*	@tparam... ArgTypes Type of all arguments
			*
			*	@param caller Pointer to the instance of the class the method will be called.
			*	@param arguments Arguments provided to the method call. This can in some cases be omitted thanks to template deduction.
			*
			*	@exception ConstViolation if a non-const method is called on a const caller.
			* 
			*	@return The result of the method call.
			*/
			template <typename ReturnType, typename CallerType, typename... ArgTypes>
			ReturnType			rInvoke(CallerType& caller, ArgTypes&&... arguments)				const	noexcept(RFK_RELEASE);

			template <typename ReturnType, typename CallerType, typename... ArgTypes>
			ReturnType			rInvoke(CallerType const& caller, ArgTypes&&... arguments)		const;

			/**
			*	@brief Call the method on an instance with the provided argument(s) if any.
			*
			*	In debug mode (NDEBUG macro not defined), checks that the correct number of
			*	arguments is passed to the method call before actually invoking the underlying method.
			*	If it is incorrect, a MethodError exception is thrown.
			*	Type checks are not performed so calling this method with bad parameters might lead to a crash.
			*
			*	@note This is only an overload of the other invoke method.
			*		  This allows to conveniently call methods when we don't care about the returned value.
			*
			*	@tparam... ArgTypes Type of all arguments. This can in some cases be omitted thanks to template deduction.
			*
			*	@param caller Pointer to the instance of the class the method will be called.
			*	@param arguments Arguments provided to the method call.
			* 
			*	@exception ConstViolation if a non-const method is called on a const caller.
			*/
			template <typename CallerType, typename... ArgTypes>
			void				invoke(CallerType& caller, ArgTypes&&... arguments)				const	noexcept(RFK_RELEASE);

			template <typename CallerType, typename... ArgTypes>
			void				invoke(CallerType const& caller, ArgTypes&&... arguments)			const;

			/**
			*	@brief Call the method on an instance with the provided argument(s) if any, and return the result.
			*
			*	Checks the argument count and the type of each argument before actually invoking the underlying method.
			*	If any of those is incorrect, a MethodError exception is thrown.
			*
			*	@tparam ReturnType Return type of the method
			*	@tparam... ArgTypes Type of all arguments. This can in some cases be omitted thanks to template deduction,
			*		but it is always safer to explicitly specify each template type to avoid type mismatches (a char* could
			*		be template deducted as a char[], and as they are different types a MethodError exception will be thrown).
			*
			*	@param caller Pointer to the instance of the class the method will be called.
			*	@param arguments Arguments provided to the method call.
			* 
			*	@exception ConstViolation if a non-const method is called on a const caller.
			*
			*	@return The result of the method call.
			*/
			template <typename ReturnType, typename CallerType, typename... ArgTypes>
			ReturnType			checkedRInvoke(CallerType& caller, ArgTypes&&... arguments)		const;

			template <typename ReturnType, typename CallerType, typename... ArgTypes>
			ReturnType			checkedRInvoke(CallerType const& caller, ArgTypes&&... arguments)	const;

			/**
			*	@brief Call the method on an instance with the provided argument(s) if any.
			*
			*	Checks the argument count and the type of each argument before actually invoking the underlying method.
			*	If any of those is incorrect, a MethodError exception is thrown.
			*
			*	@note This is only an overload of the other checkedInvoke method.
			*		  This allows to conveniently call methods when we don't care about the returned value.
			*
			*	@tparam... ArgTypes Type of all arguments. This can in some cases be omitted thanks to template deduction,
			*		but it is always safer to explicitly specify each template type to avoid type mismatches (a char* could
			*		be template deducted as a char[], and as they are different types a MethodError exception will be thrown).
			*
			*	@param caller Pointer to the instance of the class the method will be called.
			*	@param arguments Arguments provided to the method call.
			* 
			*	@exception ConstViolation if a non-const method is called on a const caller.
			*/
			template <typename CallerType, typename... ArgTypes>
			void				checkedInvoke(CallerType& caller, ArgTypes&&... arguments)		const;

			template <typename CallerType, typename... ArgTypes>
			void				checkedInvoke(CallerType const& caller, ArgTypes&&... arguments)	const;

			/**
			*	@brief Inherit from the properties this method overrides (if it has the override method flag).
			*/
			REFUREKU_API void	inheritBaseMethodProperties()										noexcept;


			Method& operator=(Method const&)	= delete;
			Method& operator=(Method&&)			= delete;
	};

	#include "Refureku/TypeInfo/Functions/Method.inl"
}