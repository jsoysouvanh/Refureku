/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <memory>
#include <vector>

#include "Refureku/Config.h"
#include "Refureku/Utility/ICallable.h"
#include "Refureku/TypeInfo/Type.h"
#include "Refureku/TypeInfo/Entity.h"
#include "Refureku/TypeInfo/EAccessSpecifier.h"
#include "Refureku/TypeInfo/Methods/EMethodFlags.h"
#include "Refureku/TypeInfo/Methods/MethodParameter.h"
#include "Refureku/Exceptions/ArgCountMismatch.h"
#include "Refureku/Exceptions/ReturnTypeMismatch.h"
#include "Refureku/Exceptions/ArgTypeMismatch.h"

namespace rfk
{
	class MethodBase : public Entity
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
			/** Handle pointing to the actual method in memory. */
			std::shared_ptr<ICallable>	_internalMethod;

			MethodBase()											= delete;
			MethodBase(std::string&&				name, 
					   uint64						id,
					   EMethodFlags					flags,
					   std::shared_ptr<ICallable>&&	internalMethod)	noexcept;
			MethodBase(MethodBase const&)							= default;
			MethodBase(MethodBase&&)								= default;

			/**
			*	@brief Check that the provided argument count is the same as this method's.
			*
			*	@exception ArgCountMismatch if the argument count is different from this method arg count.
			*/
			template <typename... ArgTypes>
			void checkArgumentsCount()	const;

			/**
			*	@brief Check that the provided argument types are the same as this method arguments.
			*
			*	@exception ArgCountMismatch if the argument count is different from this method arg count.
			*	@exception ArgTypeMismatch if one the argument has a different type from the expected one.
			*/
			template <typename... ArgTypes>
			void checkArguments()		const;

			/**
			*	@brief Check that the provided type is the same as this method return type.
			*	
			*	@exception ReturnTypeMismatch if the provided return type is different from this method's return type.
			*/
			template <typename ReturnType>
			void checkReturnType()		const;

		public:
			/** Flags describing this method. */
			EMethodFlags					flags	= EMethodFlags::Default;

			/** Type returned by this method. */
			Type							returnType;

			/** Parameters of this method. */
			std::vector<MethodParameter>	parameters;

			~MethodBase() = default;

			/**
			*	@tparam ReturnType Return type to compare with.
			*	@tparam... ArgTypes Argument types to compare with.
			*
			*	@return true if this method has the same return type as ReturnType and the same
						parameter types as ArgTypes, else false.
			*/
			template <typename ReturnType, typename... ArgTypes>
			bool				hasSamePrototype()	const	noexcept;

			/**
			*	@tparam... ArgTypes Argument types to compare with.
			*
			*	@return true if this method has the same parameter types as ArgTypes, else false.
			*/
			template <typename... ArgTypes>
			bool				hasSameArguments()	const	noexcept;

			/**
			*	@return Access specifier of this method in its owner struct/class.
			*/
			EAccessSpecifier	getAccess()			const	noexcept;

			/**
			*	@return true if this method is static, else false.
			*/
			inline bool			isStatic()			const	noexcept;

			/**
			*	@return true if this method is declared as inline, else false.
			*/
			inline bool			isInline()			const	noexcept;

			/**
			*	@return true if this method is virtual, else false.
			*/
			inline bool			isVirtual()			const	noexcept;

			/**
			*	@return true if this method is virtual pure, else false.
			*/
			inline bool			isPureVirtual()		const	noexcept;

			/**
			*	@return true if this method overrides a previous definition, else false.
			*/
			inline bool			isOverride()		const	noexcept;

			/**
			*	@return true if this method is marked as final, else false.
			*/
			inline bool			isFinal()			const	noexcept;

			/**
			*	@return true if this method is marked as const, else false.
			*/
			inline bool			isConst()			const	noexcept;
	};

	#include "Refureku/TypeInfo/Methods/MethodBase.inl"
}