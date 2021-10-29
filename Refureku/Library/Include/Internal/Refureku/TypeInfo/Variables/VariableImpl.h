/**
*	Copyright (c) 2021 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the LICENSE.md file for full license details.
*/

#pragma once

#include "Refureku/TypeInfo/Variables/Variable.h"
#include "Refureku/TypeInfo/Variables/VariableBaseImpl.h"

namespace rfk
{
	class Variable::VariableImpl : public VariableBase::VariableBaseImpl
	{
		private:
			/** Flags describing this variable. */
			EVarFlags		_flags			= EVarFlags::Default;

			/** Pointer to the variable. */
			union
			{
				void*		_ptr		= nullptr;
				void const*	_constPtr;
			};

		public:
			inline VariableImpl(char const*		name,
								std::size_t		id,
								Type const&	type,
								void*			ptr,
								EVarFlags		flags)		noexcept;
			inline VariableImpl(char const*		name,
								std::size_t		id,
								Type const&	type,
								void const*		constPtr,
								EVarFlags		flags)		noexcept;

			/**
			*	@brief Getter for the field _flags.
			* 
			*	@return _flags.
			*/
			RFK_NODISCARD inline EVarFlags		getFlags()		const	noexcept;

			/**
			*	@brief Getter for the field _ptr.
			* 
			*	@return _ptr.
			*/
			RFK_NODISCARD inline void*			getPtr()		const	noexcept;

			/**
			*	@brief Getter for the field _constPtr.
			* 
			*	@return _constPtr.
			*/
			RFK_NODISCARD inline void const*	getConstPtr()	const	noexcept;
	};

	#include "Refureku/TypeInfo/Variables/VariableImpl.inl"
}