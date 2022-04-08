/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include <type_traits>	//std::enable_if_v, std::is_const_v

#include "Refureku/TypeInfo/Functions/MethodBase.h"
#include "Refureku/TypeInfo/Functions/MemberFunction.h"
#include "Refureku/TypeInfo/Cast.h"
#include "Refureku/Misc/CopyConstness.h"

namespace rfk
{
	class Method final : public MethodBase
	{
		public:
			REFUREKU_INTERNAL Method(char const*		name,
										std::size_t		id,
										Type const&		returnType,
										ICallable*		internalMethod,
										EMethodFlags	flags,
										Entity const*	outerEntity)	noexcept;
			REFUREKU_INTERNAL Method(Method&&)							noexcept;
			REFUREKU_INTERNAL ~Method()									noexcept;

			/**
			*	@brief	Call the function with the forwarded argument(s) if any, and return the result.
			*			Providing bad return type / parameters is undefined behaviour.
			*			**WARNING**: Template type deduction might forward wrong types to the function
			*			(int instead of int8_t or char* instead of std::string for example), so it is recommended
			*			to explicitly specify all template types when calling the function.
			*
			*	@tparam ReturnType	Return type of the function.
			*	@tparam CallerType	Type of the calling struct/class.
			*	@tparam... ArgTypes	Type of all arguments. This can in some cases be omitted thanks to template deduction.
			*
			*	@param args Arguments forwarded to the function call.
			* 
			*	@return The result of the function call.
			* 
			*	@exception Any exception potentially thrown from the underlying function.
			*	@exception ConstViolation if the caller is const but the method is non-const.
			*/
			template <typename ReturnType = void, typename CallerType, typename... ArgTypes, typename = std::enable_if_t<!std::is_const_v<CallerType>>>
			ReturnType			invoke(CallerType& caller, ArgTypes&&... args)				const;
			template <typename ReturnType = void, typename CallerType, typename... ArgTypes>
			ReturnType			invoke(CallerType const& caller, ArgTypes&&... args)		const;

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
			*	@tparam CallerType	Type of the calling struct/class.
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
			template <typename ReturnType = void, typename CallerType, typename... ArgTypes, typename = std::enable_if_t<!std::is_const_v<CallerType>>>
			ReturnType			checkedInvoke(CallerType& caller, ArgTypes&&... args)		const;
			template <typename ReturnType = void, typename CallerType, typename... ArgTypes>
			ReturnType			checkedInvoke(CallerType const& caller, ArgTypes&&... args)	const;

			/**
			*	@brief	Inherit from the properties this method overrides.
			*			If the method is not an override, this method does nothing.
			*/
			REFUREKU_API void	inheritBaseMethodProperties()										noexcept;

		private:
			//Forward declaration
			class MethodImpl;

			template <typename CallerType, typename FunctionPrototype>
			class MemberFunctionSafeCallWrapper;

			template <typename CallerType, typename ReturnType, typename... ArgTypes>
			class MemberFunctionSafeCallWrapper<CallerType, ReturnType(ArgTypes...)>
			{
				private:
					template <typename T>
					using PointerToMemberMethod = ReturnType (T::*)(ArgTypes...);

				public:
					MemberFunctionSafeCallWrapper() = delete;

					/**
					*	@brief	Invoke the provided member function.
					*			This wrapper method performs intermediate compiler-dependant checks to safely cast the provided function.
					* 
					*	@param function MemberFunction to call.
					*	@param caller	Instance calling the member function.
					*	@param args...	Arguments forwarded to the function call.
					* 
					*	@return The result of the function call.
					* 
					*	@exception Any exception thrown by the underlying member function call.
					*/
					static ReturnType invoke(MemberFunction<std::remove_const_t<CallerType>, ReturnType(ArgTypes...)> const& function, CallerType& caller, ArgTypes&&... args);
			};

			/**
			*	@brief Call the underlying method with the forwarded args.
			* 
			*	@tparam ReturnType	Return type of the method.
			*	@tparam CallerType	Type of the calling struct/class.
			*	@tparam... ArgTypes	Type of all arguments.
			*
			*	@param caller	Reference to the caller struct/class.
			*	@param args		Arguments forwarded to the underlying method call.
			*
			*	@return The result of the underlying method call.
			*/
			template <typename ReturnType, typename CallerType, typename... ArgTypes>
			ReturnType						internalInvoke(CallerType& caller, ArgTypes&&... args)			const;

			/**
			*	@brief	Adjust the memory address of the caller so that the right method is called.
			*			In most cases no adjustment is required, but it is necessary when the called method is virtual
			*			and the virtual table containing the method is not at a 0 offset of the caller address.
			*			If the address could not be adjusted (because of unreflected types for example),
			the provided caller is returned as is and no error is thrown.
			* 
			*	@tparam CallerType Type of the calling struct/class.
			* 
			*	@param caller A pointer to the caller.
			* 
			*	@return The adjusted caller address.
			*/
			template <typename CallerType>
			RFK_NODISCARD CallerType&		adjustCallerAddress(CallerType& caller)							const	noexcept;

			/**
			*	@brief	Adjust the memory address of the caller so that the right method is called.
			*			In most cases no adjustment is required, but it is necessary when the called method is virtual
			*			and the virtual table containing the method is not at a 0 offset of the caller address.
			* 
			*	@tparam CallerType Type of the calling struct/class.
			* 
			*	@param caller A pointer to the caller.
			* 
			*	@return The adjusted caller address.
			* 
			*	@exception	*TODO CREATE EXCEPTION* if the caller struct is not reflected.
			*	@exception	*TODO CREATE EXCEPTION* if the caller struct can't call the method (struct that introduced this method is not in the caller parent's hierarchy).
			*/
			template <typename CallerType>
			RFK_NODISCARD CallerType&		checkedAdjustCallerAddress(CallerType& caller)					const;

			/**
			*	@brief Throw a const violation exception with the provided message.
			* 
			*	@param message Message forwarded to the exception.
			*/
			RFK_NORETURN REFUREKU_API void	throwConstViolationException(char const* message)				const;
	};

	REFUREKU_TEMPLATE_API(rfk::Allocator<Method const*>);
	REFUREKU_TEMPLATE_API(rfk::Vector<Method const*, rfk::Allocator<Method const*>>);

	#include "Refureku/TypeInfo/Functions/Method.inl"
}