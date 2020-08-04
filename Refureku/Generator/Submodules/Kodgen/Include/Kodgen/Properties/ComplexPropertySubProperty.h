/**
*	Copyright (c) 2020 Julien SOYSOUVANH - All Rights Reserved
*
*	This file is part of the Kodgen library project which is released under the MIT License.
*	See the README.md file for full license details.
*/

#pragma once

#include <string>

#include "Kodgen/Misc/FundamentalTypes.h"

namespace kodgen
{
	class ComplexPropertySubProperty
	{
		public:
			/** Supported types for a complex property subproperty. */
			enum class EType : uint8
			{
				/** int32 */
				Integer = 0,

				/** uint32 */
				UnsignedInteger,

				/** float */
				Float,

				/** std::string / char* */
				String
			};

		private:
			/** Type of this subproperty. */
			EType		_type;

			/** Name of this subproperty. */
			std::string	_name;

			/** Description of this subproperty. */
			std::string	_description;

		public:
			ComplexPropertySubProperty()									= delete;
			ComplexPropertySubProperty(EType		type,
									   std::string	name,
									   std::string	description)			noexcept;
			ComplexPropertySubProperty(ComplexPropertySubProperty const&)	= default;
			ComplexPropertySubProperty(ComplexPropertySubProperty&&)		= default;
			~ComplexPropertySubProperty()									= default;

			/**
			*	@brief Check that a subproperty string representation is valid for this subproperty.
			*	
			*	@param subpropertyAsString	String representation for this subproperty.
			*	@param out_errorDescription	Details why the subproperty is invalid.
			*
			*	@return true if the passed string is valid for this subproperty, else false.
			*			If false, out_errorDescription must be non-empty and contain the reason of non-validity.
			*/
			bool isValid(std::string const& subpropertyAsString,
						 std::string&		out_errorDescription)	const noexcept;

			/**
			*	@brief Getter for _type field.
			*	
			*	@return _type.
			*/
			EType				getType()			const noexcept;

			/**
			*	@brief Getter for _name field.
			*	
			*	@return _name.
			*/
			std::string const&	getName()			const noexcept;

			/**
			*	@brief Getter for _description field.
			*	
			*	@return _description.
			*/
			std::string const&	getDescription()	const noexcept;
	};

	std::string toString(ComplexPropertySubProperty::EType type) noexcept;
}