/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Refureku library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <string>

#include "Refureku/Config.h"
#include "Refureku/TypeInfo/Type.h"

namespace rfk
{
	class FunctionParameter
	{
		private:
			/** Name of this parameter. Can be unspecified (empty). */
			std::string		_name;

			/** Type of this parameter */
			Type const&		_type;

		public:
			FunctionParameter(std::string&&	name,
							  Type const&	type)		noexcept;
			FunctionParameter(FunctionParameter const&)	= delete;
			FunctionParameter(FunctionParameter&&)		= default;

			/**
			*	@brief Getter for the field _name.
			* 
			*	@return _name;
			*/
			REFUREKU_API std::string const&	getName()	const	noexcept;

			/**
			*	@brief Getter for the field _type.
			* 
			*	@return _type;
			*/
			inline Type const&				getType()	const	noexcept;
	};

	#include "Refureku/TypeInfo/Functions/FunctionParameter.inl"
}