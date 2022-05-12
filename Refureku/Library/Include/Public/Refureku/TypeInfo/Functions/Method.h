/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include <type_traits>	//std::enable_if_v, std::is_const_v
#include <cassert>

#include "Refureku/TypeInfo/Cast.h"
#include "Refureku/TypeInfo/MethodFieldHelpers.h"
#include "Refureku/TypeInfo/Archetypes/Struct.h"
#include "Refureku/TypeInfo/Functions/MethodBase.h"
#include "Refureku/TypeInfo/Functions/MemberFunction.h"
#include "Refureku/Misc/CopyConstness.h"
#include "Refureku/Exceptions/InvalidArchetype.h"

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
			*	@param caller	Object instance calling the method. Caller is not required to implement the getArchetype method, but the invoke method will
			*					likely crash if the memory offset between the CallerType static archetype and its actual dynamic archetype is different from 0.
			*					If CallerType implements the getArchetype method (rfk::Object), no such error will ever happen.
			*	@param args		Arguments forwarded to the function call.
			* 
			*	@return The result of the function call.
			* 
			*	@exception Any exception potentially thrown from the underlying function.
			*	@exception ConstViolation if the caller is const but the method is non-const.
			*/
			template <typename ReturnType = void, typename CallerType, typename... ArgTypes, typename = internal::IsAdjustableInstance<CallerType>>
			ReturnType			invoke(CallerType& caller, ArgTypes&&... args)				const;

			/**
			*	@brief	Call the function with the forwarded argument(s) if any, and return the result.
			*			Providing bad return type / parameters is undefined behaviour.
			*			This method DOES NOT perform any pointer adjustment on the provided caller so it has an undefined behaviour if caller
			*			is not a valid pointer to an object of the method's owner archetype.
			*			Prefer using Method::invoke for safety if you know the static type of your caller in the calling context.
			*			**WARNING**: Template type deduction might forward wrong types to the function
			*			(int instead of int8_t or char* instead of std::string for example), so it is recommended
			*			to explicitly specify all template types when calling the function.
			*
			*	@note Since this method doesn't perform any pointer adjustment, it is slightly faster than Method::invoke.
			* 
			*	@tparam ReturnType	Return type of the function.
			*	@tparam... ArgTypes	Type of all arguments. This can in some cases be omitted thanks to template deduction.
			*
			*	@param caller	Object instance calling the method.
			*	@param args		Arguments forwarded to the function call.
			* 
			*	@return The result of the function call.
			* 
			*	@exception Any exception potentially thrown from the underlying function.
			*	@exception ConstViolation if the caller is const but the method is non-const.
			*/
			template <typename ReturnType = void, typename... ArgTypes>
			ReturnType			invokeUnsafe(void* caller, ArgTypes&&... args)				const;

			/**
			*	@brief	Call the function with the forwarded argument(s) if any, and return the result.
			*			Providing bad return type / parameters is undefined behaviour.
			*			This method DOES NOT perform any pointer adjustment on the provided caller so it has an undefined behaviour if caller
			*			is not a valid pointer to an object of the method's owner archetype.
			*			Prefer using Method::invoke for safety if you know the static type of your caller in the calling context.
			*			**WARNING**: Template type deduction might forward wrong types to the function
			*			(int instead of int8_t or char* instead of std::string for example), so it is recommended
			*			to explicitly specify all template types when calling the function.
			* 
			*	@note This is only an overload of the same method with a const caller.
			*		  Since this method doesn't perform any pointer adjustment, it is slightly faster than Method::invoke.
			*
			*	@tparam ReturnType	Return type of the function.
			*	@tparam... ArgTypes	Type of all arguments. This can in some cases be omitted thanks to template deduction.
			*
			*	@param caller	Object instance calling the method.
			*	@param args		Arguments forwarded to the function call.
			* 
			*	@return The result of the function call.
			* 
			*	@exception Any exception potentially thrown from the underlying function.
			*/
			template <typename ReturnType = void, typename... ArgTypes>
			ReturnType			invokeUnsafe(void const* caller, ArgTypes&&... args)		const;

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
			*	@param caller	Object instance calling the method. It MUST implement the getArchetype method (rfk::Object) for all safety checks to be performed properly.
			*	@param args		Arguments forwarded to the function call.
			*
			*	@return The result of the function call.
			* 
			*	@exception	ArgCountMismatch	if sizeof...(ArgTypes) is not the same as the value returned by getParametersCount().
			*	@exception	ArgTypeMismatch		if ArgTypes... are not strictly the same as this function parameter types.
			*				**WARNING**: Be careful to template deduction.
			*	@exception	ReturnTypeMismatch	if ReturnType is not strictly the same as this function return type.
			*	@exception	ConstViolation if the caller is const but the method is non-const.
			*	@exception	InvalidCaller		if the caller struct can't call the method (struct that introduced this method is not in the caller parent's hierarchy).
			*	@exception	Any exception potentially thrown from the underlying function.
			*/
			template <typename ReturnType = void, typename CallerType, typename... ArgTypes, typename = internal::IsAdjustableInstance<CallerType>>
			ReturnType			checkedInvoke(CallerType& caller, ArgTypes&&... args)		const;

			/**
			*	@brief	Call the function with the forwarded argument(s) if any, and return the result.
			*			The return type and arguments types will be strictly checked before calling the function.
			*			If there is any mismatch, ArgCountMismatch, ArgTypeMismatch or ReturnTypeMismatch will be thrown.
			*			This method DOES NOT perform any pointer adjustment on the provided caller so it has an undefined behaviour if caller
			*			is not a valid pointer to an object of the method's owner archetype.
			*			Prefer using Method::checkedInvoke for safety if you know the static type of your caller in the calling context.
			*			**WARNING 1**: Unreflected archetypes can't be compared, so they will pass through the type checks.
			*			**WARNING 2**: Template type deduction might forward wrong types to the function
			*			(int instead of int8_t or char* instead of std::string for example), so it is recommended
			*			to explicitly specify all template types when calling the function.
			*
			*	@note Since this method doesn't perform any pointer adjustment, it is slightly faster than Method::checkedInvoke.
			* 
			*	@tparam ReturnType	Return type of the function.
			*	@tparam... ArgTypes	Type of all arguments. This can in some cases be omitted thanks to template deduction.
			*
			*	@param caller	Object instance calling the method.
			*	@param args		Arguments forwarded to the function call.
			*
			*	@return The result of the function call.
			* 
			*	@exception	ArgCountMismatch	if sizeof...(ArgTypes) is not the same as the value returned by getParametersCount().
			*	@exception	ArgTypeMismatch		if ArgTypes... are not strictly the same as this function parameter types.
			*				**WARNING**: Be careful to template deduction.
			*	@exception	ReturnTypeMismatch	if ReturnType is not strictly the same as this function return type.
			*	@exception	ConstViolation if the caller is const but the method is non-const.
			*	@exception	InvalidCaller		if the caller struct can't call the method (struct that introduced this method is not in the caller parent's hierarchy).
			*	@exception	Any exception potentially thrown from the underlying function.
			*/
			template <typename ReturnType = void, typename... ArgTypes>
			ReturnType			checkedInvokeUnsafe(void* caller, ArgTypes&&... args)		const;

			/**
			*	@brief	Call the function with the forwarded argument(s) if any, and return the result.
			*			The return type and arguments types will be strictly checked before calling the function.
			*			If there is any mismatch, ArgCountMismatch, ArgTypeMismatch or ReturnTypeMismatch will be thrown.
			*			This method DOES NOT perform any pointer adjustment on the provided caller so it has an undefined behaviour if caller
			*			is not a valid pointer to an object of the method's owner archetype.
			*			Prefer using Method::checkedInvoke for safety if you know the static type of your caller in the calling context.
			*			**WARNING 1**: Unreflected archetypes can't be compared, so they will pass through the type checks.
			*			**WARNING 2**: Template type deduction might forward wrong types to the function
			*			(int instead of int8_t or char* instead of std::string for example), so it is recommended
			*			to explicitly specify all template types when calling the function.
			*
			*	@note This is only an overload of the same method with a const caller.
			*		  Since this method doesn't perform any pointer adjustment, it is slightly faster than Method::checkedInvoke.
			* 
			*	@tparam ReturnType	Return type of the function.
			*	@tparam... ArgTypes	Type of all arguments. This can in some cases be omitted thanks to template deduction.
			*
			*	@param caller	Object instance calling the method.
			*	@param args		Arguments forwarded to the function call.
			*
			*	@return The result of the function call.
			* 
			*	@exception	ArgCountMismatch	if sizeof...(ArgTypes) is not the same as the value returned by getParametersCount().
			*	@exception	ArgTypeMismatch		if ArgTypes... are not strictly the same as this function parameter types.
			*				**WARNING**: Be careful to template deduction.
			*	@exception	ReturnTypeMismatch	if ReturnType is not strictly the same as this function return type.
			*	@exception	InvalidCaller		if the caller struct can't call the method (struct that introduced this method is not in the caller parent's hierarchy).
			*	@exception	Any exception potentially thrown from the underlying function.
			*/
			template <typename ReturnType = void, typename... ArgTypes>
			ReturnType			checkedInvokeUnsafe(void const* caller, ArgTypes&&... args)	const;

			/**
			*	@brief	Inherit from the properties this method overrides.
			*			If the method is not an override, this method does nothing.
			*/
			REFUREKU_API void	inheritBaseMethodProperties()										noexcept;

		private:
			//Forward declaration
			class MethodImpl;

			template <typename FunctionPrototype>
			class MemberFunctionSafeCallWrapper;

			template <typename ReturnType, typename... ArgTypes>
			class MemberFunctionSafeCallWrapper<ReturnType(ArgTypes...)>
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
					*	@param memberFunction	MemberFunction to call.
					*	@param caller			Instance calling the member function (void* or void const*).
					*	@param args...			Arguments forwarded to the function call.
					* 
					*	@return The result of the function call.
					* 
					*	@exception Any exception thrown by the underlying member function call.
					*/
					template <typename T, typename = std::enable_if_t<std::is_same_v<T, void> || std::is_same_v<T, void const>>>
					static ReturnType invoke(ICallable const&	memberFunction,
											 T*					caller,
											 ArgTypes&&...		args);
			};

			/**
			*	@brief Call the underlying method with the forwarded args.
			* 
			*	@tparam ReturnType	Return type of the method.
			*	@tparam... ArgTypes	Type of all arguments.
			*
			*	@param caller	Pointer to the caller struct/class.
			*	@param args		Arguments forwarded to the underlying method call.
			*
			*	@return The result of the underlying method call.
			*/
			template <typename ReturnType, typename... ArgTypes>
			ReturnType						internalInvoke(void*		 caller,
														   ArgTypes&&... args)									const;
			template <typename ReturnType, typename... ArgTypes>
			ReturnType						internalInvoke(void const*	 caller,
														   ArgTypes&&... args)									const;

			/**
			*	@brief Adjust the caller pointer to a pointer to this method's outer struct.
			* 
			*	@tparam CallerType The static type of the provided caller.
			* 
			*	@param caller The caller pointer to adjust.
			* 
			*	@return The adjusted caller pointer.
			* 
			*	@exception InvalidArchetype if the caller dynamic archetype couldn't be casted to the method outer struct's archetype.
			*/
			template <typename CallerType>
			RFK_NODISCARD CallerType*		adjustCallerPointerAddress(CallerType* caller)						const;

			/**
			*	@brief Throw a ConstViolation exception with the provided message.
			* 
			*	@param message Message forwarded to the exception.
			*/
			RFK_NORETURN REFUREKU_API void	throwConstViolationException()										const;
	};

	REFUREKU_TEMPLATE_API(rfk::Allocator<Method const*>);
	REFUREKU_TEMPLATE_API(rfk::Vector<Method const*, rfk::Allocator<Method const*>>);

	#include "Refureku/TypeInfo/Functions/Method.inl"
}