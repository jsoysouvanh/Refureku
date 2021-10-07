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

namespace rfk
{
	class FunctionBaseAPI : public Entity
	{
		public:
			/**
			*	@tparam		ReturnType	Return type to compare with.
			*	@tparam...	ArgTypes	Argument types to compare with.
			*
			*	@return true if this function has the same return type as ReturnType and the same
			*			parameter types as ArgTypes, else false.
			*/
			template <typename ReturnType, typename... ArgTypes>
			RFK_NODISCARD bool										hasSamePrototype()								const	noexcept;

			/**
			*	@brief Check that another function has the same prototype as this function.
			*	
			*	@param other Function to compare the prototype with.
			* 
			*	@return true if the provided function has the same prototype as this function, else false.
			*/
			RFK_NODISCARD REFUREKU_API bool							hasSamePrototype(FunctionBaseAPI const& other)	const	noexcept;

			/**
			*	@tparam... ArgTypes Argument types to compare with.
			*
			*	@return true if this function has the same parameter types as ArgTypes, else false.
			*/
			template <typename... ArgTypes>
			RFK_NODISCARD bool										hasSameParameters()								const	noexcept;

			/**
			*	@brief Get the return type of this function.
			* 
			*	@return The return type of this function.
			*/
			RFK_NODISCARD REFUREKU_API Type const&				getReturnType()									const	noexcept;

			/**
			*	@brief	Retrieve the parameter at the given index.
			*			If index is greater or equal to the parameters count, the behaviour is undefined.
			* 
			*	@param index Index of the parameter.
			* 
			*	@return The parameter at the given index.
			*/
			RFK_NODISCARD REFUREKU_API FunctionParameterAPI const&	getParameterAt(std::size_t index)				const	noexcept;	

			/**
			*	@brief Get the number of parameters of this function.
			* 
			*	@return The number of parameters of this function.
			*/
			RFK_NODISCARD REFUREKU_API std::size_t					getParametersCount()							const	noexcept;

			/**
			*	@brief Get the internal function handled by this object.
			*	
			*	@return The function handle.
			*/
			RFK_NODISCARD REFUREKU_API ICallable*					getInternalFunction()							const	noexcept;

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
																				 Type const&	type)						noexcept;

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
			REFUREKU_INTERNAL FunctionBaseAPI(FunctionBaseAPI&&)				noexcept;
			REFUREKU_INTERNAL ~FunctionBaseAPI()								noexcept;

			/**
			*	@brief Check that the provided argument count is the same as this function's.
			*
			*	@exception ArgCountMismatch if the argument count is different from this function arg count.
			*/
			template <typename... ArgTypes>
			void									checkParametersCount()	const;

			/**
			*	@brief Check that the provided types are the same as this function parameter types.
			*
			*	@exception ArgCountMismatch if the argument count is different from this function arg count.
			*	@exception ArgTypeMismatch if one the argument has a different type from the expected one.
			*/
			template <typename... ArgTypes>
			void									checkParameterTypes()	const;

			/**
			*	@brief Check that the provided type is the same as this function return type.
			*	
			*	@exception ReturnTypeMismatch if the provided return type is different from this function's return type.
			*/
			template <typename ReturnType>
			void									checkReturnType()		const;

		private:
			/**
			*	@brief Check that the provided type is the same as this function's.
			* 
			*	@return true if the provided type is the same as this function's, else false.
			*/
			template <typename ReturnType>
			RFK_NODISCARD bool						hasSameReturnType()										const	noexcept;

			/**
			*	@brief Check that the number of provided parameters is the same as this method's.
			* 
			*	@return true if provided types count is the same as this method's, else false.
			*/
			template <typename... ArgTypes>
			RFK_NODISCARD bool						hasSameParametersCount()								const	noexcept;

			/**
			*	@brief Check that the provided parameters are the same as this method's.
			* 
			*	@return true if provided types are the same as this method parameters, else false.
			*/
			template <std::size_t Rank, typename FirstArgType, typename SecondArgType, typename... OtherArgTypes>
			RFK_NODISCARD bool						hasSameParameterTypes()									const	noexcept;
			template <std::size_t Rank, typename LastArgType>
			RFK_NODISCARD bool						hasSameParameterTypes()									const	noexcept;
			template <typename... ArgTypes>
			RFK_NODISCARD bool						hasSameParameterTypes()									const	noexcept;

			/**
			*	@brief Check that the parameter types match, and throw an ArgTypeMismatch exception if it is not the case.
			*/
			template <std::size_t Rank, typename FirstArgType, typename SecondArgType, typename... OtherArgTypes>
			void									checkParameterTypes()									const;
			template <std::size_t Rank, typename LastArgType>
			void									checkParameterTypes()									const;

			/**
			*	@brief	Throw an ArgCountMismatch exception with an descriptive message.
			*			/!\ This method is called from template methods so it must be exported.
			* 
			*	@param received Number of received parameters.
			*/
			RFK_NORETURN REFUREKU_API void			throwArgCountMismatchException(std::size_t received)	const;

			/**
			*	@brief	Throw an ArgTypeMismatch exception with a descriptive message.
			*			/!\ This method is called from template methods so it must be exported.
			* 
			*	@param paramIndex Index of the mismatching parameter.
			*/
			RFK_NORETURN REFUREKU_API void			throwArgTypeMismatchException(std::size_t paramIndex)	const;

			/**
			*	@brief	Throw a ReturnTypeMismatch exception with a descriptive message.
			*			/!\ This method is called from template methods so it must be exported.
			*/
			RFK_NORETURN REFUREKU_API void			throwReturnTypeMismatchException()						const;
	};

	#include "Refureku/TypeInfo/Functions/FunctionBaseAPI.inl"
}