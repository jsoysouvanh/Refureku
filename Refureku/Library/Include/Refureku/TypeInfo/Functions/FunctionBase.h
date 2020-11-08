/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <memory>	//unique_ptr
#include <vector>

#include "Refureku/TypeInfo/Entity/Entity.h"
#include "Refureku/TypeInfo/Functions/FunctionParameter.h"
#include "Refureku/TypeInfo/Functions/ICallable.h"
#include "Refureku/Exceptions/ArgCountMismatch.h"
#include "Refureku/Exceptions/ReturnTypeMismatch.h"
#include "Refureku/Exceptions/ArgTypeMismatch.h"

namespace rfk
{
	class FunctionBase : public Entity
	{
		private:
			template <size_t Rank, typename FirstArgType, typename SecondArgType, typename... OtherArgTypes>
			void	checkArguments()		const;

			template <size_t Rank, typename LastArgType>
			void	checkArguments()		const;

			template <typename... ArgTypes>
			bool	hasSameArgumentsCount()	const	noexcept;

			template <typename ReturnType>
			bool	hasSameReturnType()		const	noexcept;

			template <size_t Rank, typename FirstArgType, typename SecondArgType, typename... OtherArgTypes>
			bool	hasSameArgumentTypes()	const	noexcept;

			template <size_t Rank, typename LastArgType>
			bool	hasSameArgumentTypes()	const	noexcept;

			template <typename... ArgTypes>
			bool	hasSameArgumentTypes()	const	noexcept;

		protected:
			/** Handle pointing to the actual function in memory. */
			std::unique_ptr<ICallable>	internalMethod;

			FunctionBase()												= delete;
			FunctionBase(std::string&&					name, 
						 uint64							id,
						 EEntityKind					kind,
						 Type const&					returnType,
						 std::unique_ptr<ICallable>&&	internalMethod)	noexcept;
			FunctionBase(FunctionBase const&)							= delete;
			FunctionBase(FunctionBase&&)								= delete;
			~FunctionBase()												= default;

			/**
			*	@brief Check that the provided argument count is the same as this function's.
			*
			*	@exception ArgCountMismatch if the argument count is different from this function arg count.
			*/
			template <typename... ArgTypes>
			void checkArgumentsCount()	const;

			/**
			*	@brief Check that the provided argument types are the same as this function's arguments.
			*
			*	@exception ArgCountMismatch if the argument count is different from this function arg count.
			*	@exception ArgTypeMismatch if one the argument has a different type from the expected one.
			*/
			template <typename... ArgTypes>
			void checkArguments()		const;

			/**
			*	@brief Check that the provided type is the same as this function return type.
			*	
			*	@exception ReturnTypeMismatch if the provided return type is different from this function's return type.
			*/
			template <typename ReturnType>
			void checkReturnType()		const;
			
		public:
			/** Type returned by this function. */
			Type const&						returnType;

			/** Parameters of this function. */
			std::vector<FunctionParameter>	parameters;

			/**
			*	@tparam		ReturnType	Return type to compare with.
			*	@tparam...	ArgTypes	Argument types to compare with.
			*
			*	@return true if this function has the same return type as ReturnType and the same
			*			parameter types as ArgTypes, else false.
			*/
			template <typename ReturnType, typename... ArgTypes>
			bool				hasSamePrototype()	const	noexcept;

			/**
			*	@tparam... ArgTypes Argument types to compare with.
			*
			*	@return true if this function has the same parameter types as ArgTypes, else false.
			*/
			template <typename... ArgTypes>
			bool				hasSameArguments()	const	noexcept;

			/**
			*	@brief Check that another function has the same prototype as this function.
			*	
			*	@param other Function to compare the prototype with.
			*/
			bool	hasSamePrototype(FunctionBase const* other)	const	noexcept;
	};

	#include "Refureku/TypeInfo/Functions/FunctionBase.inl"
}