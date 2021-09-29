/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Entity/Entity.h"
#include "Refureku/TypeInfo/Functions/FunctionParameterAPI.h"
#include "Refureku/TypeInfo/Functions/ICallable.h"

#include "Refureku/Exceptions/ArgCountMismatch.h"	//TODO: Want to remove exceptions from API header...
#include "Refureku/Exceptions/ReturnTypeMismatch.h"
#include "Refureku/Exceptions/ArgTypeMismatch.h"

namespace rfk
{
	class FunctionBaseAPI : public EntityAPI
	{
		public:
			/**
			*	@brief Add a parameter to the function.
			*	
			*	@param name	Name of the parameter, can be empty.
			*	@param id	Id of the parameter entity.
			*	@param type	Type of the parameter.
			*	
			*	@return The added function parameter.
			*/
			REFUREKU_API FunctionParameterAPI&						addParameter(char const*	name,
																				 std::size_t	id,
																				 TypeAPI const&	type)						noexcept;

			/**
			*	@tparam		ReturnType	Return type to compare with.
			*	@tparam...	ArgTypes	Argument types to compare with.
			*
			*	@return true if this function has the same return type as ReturnType and the same
			*			parameter types as ArgTypes, else false.
			*/
			template <typename ReturnType, typename... ArgTypes>
			[[nodiscard]] bool										hasSamePrototype()								const	noexcept;

			/**
			*	@brief Check that another function has the same prototype as this function.
			*	
			*	@param other Function to compare the prototype with.
			* 
			*	@return true if the provided function has the same prototype as this function, else false.
			*/
			[[nodiscard]] REFUREKU_API bool							hasSamePrototype(FunctionBaseAPI const& other)	const	noexcept;

			/**
			*	@tparam... ArgTypes Argument types to compare with.
			*
			*	@return true if this function has the same parameter types as ArgTypes, else false.
			*/
			template <typename... ArgTypes>
			[[nodiscard]] bool										hasSameParameters()								const	noexcept;

			/**
			*	@brief Get the return type of this function.
			* 
			*	@return The return type of this function.
			*/
			[[nodiscard]] REFUREKU_API TypeAPI const&				getReturnType()									const	noexcept;

			/**
			*	@brief	Retrieve the parameter at the given index.
			*			If index is greater or equal to the parameters count, the behaviour is undefined.
			* 
			*	@param index Index of the parameter.
			* 
			*	@return The parameter at the given index.
			*/
			[[nodiscard]] REFUREKU_API FunctionParameterAPI const&	getParameterAt(std::size_t index)				const	noexcept;	

			/**
			*	@brief Get the number of parameters of this function.
			* 
			*	@return The number of parameters of this function.
			*/
			[[nodiscard]] REFUREKU_API std::size_t					getParametersCount()							const	noexcept;

			/**
			*	@brief	Set the number of parameters for this function.
			*			Useful to avoid reallocations when adding a lot of parameters.
			*			If the number of parameters is already >= to the provided count, this method has no effect.
			* 
			*	@param paramCapacity The number of parameters of this function.
			*/
			REFUREKU_API void										setParametersCapacity(std::size_t capacity)				noexcept;

		protected:
			//Forward declaration
			class FunctionBaseImpl;

			REFUREKU_INTERNAL FunctionBaseAPI(FunctionBaseImpl* implementation)	noexcept;
			REFUREKU_INTERNAL ~FunctionBaseAPI()								noexcept;

			/**
			*	@brief Check that the provided argument count is the same as this function's.
			*
			*	@exception ArgCountMismatch if the argument count is different from this function arg count.
			*/
			template <typename... ArgTypes>
			void									checkParametersCount()	const;

			/**
			*	@brief Check that the provided argument types are the same as this function's arguments.
			*
			*	@exception ArgCountMismatch if the argument count is different from this function arg count.
			*	@exception ArgTypeMismatch if one the argument has a different type from the expected one.
			*/
			template <typename... ArgTypes>
			void									checkParameters()		const;

			/**
			*	@brief Check that the provided type is the same as this function return type.
			*	
			*	@exception ReturnTypeMismatch if the provided return type is different from this function's return type.
			*/
			template <typename ReturnType>
			void									checkReturnType()		const;

			/**
			*	@brief Get the internal function handled by this object.
			*	
			*	@return The function handle.
			*/
			[[nodiscard]] REFUREKU_API ICallable*	getInternalFunction()	const	noexcept;

		private:
			/**
			*	@brief Check that the provided type is the same as this function's.
			* 
			*	@return true if the provided type is the same as this function's, else false.
			*/
			template <typename ReturnType>
			[[nodiscard]] bool						hasSameReturnType()			const	noexcept;

			/**
			*	@brief Check that the number of provided parameters is the same as this method's.
			* 
			*	@return true if provided types count is the same as this method's, else false.
			*/
			template <typename... ArgTypes>
			[[nodiscard]] bool						hasSameParametersCount()	const	noexcept;

			/**
			*	@brief Check that the provided parameters are the same as this method's.
			* 
			*	@return true if provided types are the same as this method parameters, else false.
			*/
			template <size_t Rank, typename FirstArgType, typename SecondArgType, typename... OtherArgTypes>
			[[nodiscard]] bool						hasSameParameterTypes()		const	noexcept;
			template <size_t Rank, typename LastArgType>
			[[nodiscard]] bool						hasSameParameterTypes()		const	noexcept;
			template <typename... ArgTypes>
			[[nodiscard]] bool						hasSameParameterTypes()		const	noexcept;
	};

	#include "Refureku/TypeInfo/Functions/FunctionBaseAPI.inl"
}